#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdint>
using namespace std;
Texture Zombie::s_dummyTexture;

void Zombie::spawn(float startX, float startY, int type, int seed) {
    switch (type) {
        case 0:
            // Bloater
            m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
            m_Speed = BLOATER_SPEED;
            m_Health = BLOATER_HEALTH;
            break;
        case 1:
            // Chaser
            m_Sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
            m_Speed = CHASER_SPEED;
            m_Health = CHASER_HEALTH;
            break;
        case 2:
            // Crawler
            m_Sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
            m_Speed = CRAWLER_SPEED;
            m_Health = CRAWLER_HEALTH;
            break;
    }

    srand((int)time(0) * seed);

    float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
    modifier /= 100;
    m_Speed *= modifier;
    m_Alive = true;

    m_Position = {startX, startY};
    m_Sprite.setOrigin(Vector2f{25.f, 25.f});
    m_Sprite.setPosition(m_Position);
}

bool Zombie::hit() {
    m_Health --;
    if (m_Health <= 0) {
        m_Alive = false;
        m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));
        return true;
    }
    return false;
}

bool Zombie::isAlive() const {
    return m_Alive;
}

FloatRect Zombie::getPosition() {
    return m_Sprite.getGlobalBounds();
}

void Zombie::update(float elaspedTime, Vector2f playerLocation) {
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    if (playerX > m_Position.x) m_Position.x += m_Speed * elaspedTime;
    if (playerY > m_Position.y) m_Position.y += m_Speed * elaspedTime;
    if (playerX < m_Position.x) m_Position.x -= m_Speed * elaspedTime;
    if (playerY < m_Position.y) m_Position.y -= m_Speed * elaspedTime;


    m_Sprite.setPosition(m_Position);

    constexpr float PI = 3.141f;
    float angleDeg = std::atan2f(
        playerY - m_Position.y,
        playerX - m_Position.x
    ) * 180.f / PI;
    m_Sprite.setRotation(sf::degrees(angleDeg));
}
bool Zombie::initDummyTexture() {
    const Image img({1u, 1u}, Color(0, 0, 0, 0));
    return s_dummyTexture.loadFromImage(img);
}