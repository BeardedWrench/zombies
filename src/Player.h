#pragma once
#include <SFML/Graphics.hpp>
#ifndef ZOMBIES_PLAYER_H
#define ZOMBIES_PLAYER_H
using namespace sf;

class Player {
public:
    Player();

    void spawn(const IntRect& arena, const Vector2f& resolution, int tileSize);
    void resetPlayerStats();

    bool hit(Time timeHit);
    Time getLastHitTime() const;

    FloatRect getPosition() const;
    Vector2f getCenter() const;
    float getRotation() const;
    const Sprite& getSprite() const;

    int getHealth() const;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    void update(float elapsedTime, Vector2i mousePosition);

    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);

private:
    static constexpr float START_SPEED  = 200.f;
    static constexpr float START_HEALTH = 100.f;

    Vector2f m_Position{0.f, 0.f};
    Texture m_Texture;
    Sprite m_Sprite;

    Vector2f m_Resolution{0.f, 0.f};
    IntRect m_Arena{{0, 0}, {0, 0}};
    int m_TileSize{0};

    bool m_UpPressed{false};
    bool m_DownPressed{false};
    bool m_LeftPressed{false};
    bool m_RightPressed{false};

    int m_Health{static_cast<int>(START_HEALTH)};
    int m_MaxHealth{static_cast<int>(START_HEALTH)};
    Time m_LastHit{};
    float m_Speed{START_SPEED};
};

#endif