#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"
#include <optional>

#include "Bullet.h"
#include "TextureHolder.h"
#include "utils/Assets.h"
#include "utils/Console.h"

int main() {
    using namespace sf;
    Zombie::initDummyTexture();

    enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

    State state = State::GAME_OVER;

    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().size.x;
    resolution.y = VideoMode::getDesktopMode().size.y;

    RenderWindow window(
        VideoMode(Vector2u(resolution.x, resolution.y)),
        "Zombie Arena",
        sf::State::Windowed
    );
    View mainView(FloatRect({0.f, 0.f}, {resolution.x, resolution.y}));
    Clock clock;
    Time gameTimeTotal;

    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;

    Player player;
    IntRect arena;

    VertexArray background;
    Texture textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

    int numZombies;
    int numZombiesAlive;
    std::vector<Zombie> zombies;

    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1;
    Time lastPressed;


    window.setMouseCursorVisible(false);
    Sprite crosshair = Sprite(TextureHolder::GetTexture("graphics/crosshair.png"));
    crosshair.setOrigin({25, 25});

    Console::init();
    Console::log("Console initialized.");

    while (window.isOpen()) {
        while (std::optional<Event> e = window.pollEvent()) {
            if (e->is<Event::Closed>()) {
                window.close();
            }
            if (Console::handleEvent(*e)) {
                continue;
            }


            if (auto kp = e->getIf<Event::KeyPressed>()) {
                const auto key = kp->code;

                if (key == Keyboard::Key::Enter && state == State::PLAYING) {
                    state = State::PAUSED;
                }
                else if (key == Keyboard::Key::Enter && state == State::PAUSED) {
                    state = State::PLAYING;
                    clock.restart();
                }
                else if (key == Keyboard::Key::Enter && state == State::GAME_OVER) {
                    state = State::LEVELING_UP;
                }
                if (state == State::PLAYING) {
                    if (key == Keyboard::Key::R) {
                        if (bulletsSpare >= clipSize){}
                        bulletsInClip = clipSize;
                        bulletsSpare -= clipSize;
                    }
                    else if (bulletsSpare > 0) {
                        bulletsInClip = bulletsSpare;
                        bulletsSpare = 0;
                    }
                }


                if (state == State::LEVELING_UP) {
                    switch (key) {
                        case Keyboard::Key::Num1:
                        case Keyboard::Key::Num2:
                        case Keyboard::Key::Num3:
                        case Keyboard::Key::Num4:
                        case Keyboard::Key::Num5:
                        case Keyboard::Key::Num6:
                            state = State::PLAYING;
                            arena = IntRect({0, 0}, {500, 500});
                            {
                                int tileSize = createBackground(background, arena);
                                player.spawn(arena, resolution, tileSize);

                                numZombies = 10;
                                zombies = createHorde(numZombies, arena);
                                numZombiesAlive = static_cast<int>(zombies.size());
                            }
                            clock.restart();
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        if (state == State::PLAYING) {
            if (Keyboard::isKeyPressed(Keyboard::Key::W))  player.moveUp();    else player.stopUp();
            if (Keyboard::isKeyPressed(Keyboard::Key::S))  player.moveDown();  else player.stopDown();
            if (Keyboard::isKeyPressed(Keyboard::Key::A))  player.moveLeft();  else player.stopLeft();
            if (Keyboard::isKeyPressed(Keyboard::Key::D))  player.moveRight(); else player.stopRight();

            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0) {
                    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
                    currentBullet++;
                    if (currentBullet > 99) currentBullet = 0;
                    lastPressed = gameTimeTotal;
                    bulletsInClip--;
                }
            }
        }

        if (state == State::PLAYING) {
            Time dt = clock.restart();
            gameTimeTotal += dt;
            float dtAsSeconds = dt.asSeconds();

            mouseScreenPosition = Mouse::getPosition(window);
            mouseWorldPosition  = window.mapPixelToCoords(mouseScreenPosition, mainView);

            crosshair.setPosition(mouseWorldPosition);
            player.update(dtAsSeconds, mouseScreenPosition);

            mainView.setCenter(player.getCenter());

            for (auto& z : zombies) {
                if (z.isAlive()) {
                    z.update(dt.asSeconds(), player.getCenter());
                }
            }
            for (auto & bullet : bullets) {
                if (bullet.isInFlight()) {
                    bullet.update(dtAsSeconds);
                }
            }
        }

        window.clear();
        if (state == State::PLAYING) {
            RenderStates states;
            states.texture = &textureBackground;
            window.setView(mainView);
            window.draw(background, states);
            for (auto& z : zombies) {
                window.draw(z.getSprite());
            }
            for (auto & bullet : bullets) {
                if (bullet.isInFlight()) {
                    window.draw(bullet.getShape());
                }
            }
            window.draw(player.getSprite());
            window.draw(crosshair);
        }


        Console::draw(window);
        window.display();
    }
    return 0;
}
