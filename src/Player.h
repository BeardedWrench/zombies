#pragma once
#include <SFML/Graphics.hpp>
#ifndef ZOMBIES_PLAYER_H
#define ZOMBIES_PLAYER_H
using namespace sf;

class Player {
public:
    Player();

    void spawn(const sf::IntRect& arena, const sf::Vector2f& resolution, int tileSize);
    void resetPlayerStats();

    bool            hit(sf::Time timeHit);
    sf::Time        getLastHitTime() const;

    sf::FloatRect   getPosition() const;
    sf::Vector2f    getCenter()   const;
    float           getRotation() const;
    const sf::Sprite& getSprite() const;

    int             getHealth()   const;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    void update(float elapsedTime, sf::Vector2i mousePosition);

    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);

private:
    static constexpr float START_SPEED  = 200.f;
    static constexpr float START_HEALTH = 100.f;

    sf::Vector2f  m_Position{0.f, 0.f};
    sf::Texture   m_Texture;
    sf::Sprite    m_Sprite;

    sf::Vector2f  m_Resolution{0.f, 0.f};
    sf::IntRect   m_Arena{{0, 0}, {0, 0}};
    int           m_TileSize{0};

    bool m_UpPressed{false};
    bool m_DownPressed{false};
    bool m_LeftPressed{false};
    bool m_RightPressed{false};

    int       m_Health{static_cast<int>(START_HEALTH)};
    int       m_MaxHealth{static_cast<int>(START_HEALTH)};
    sf::Time  m_LastHit{};
    float     m_Speed{START_SPEED};
};

#endif