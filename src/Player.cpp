#include "Player.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Angle.hpp>
#include <cmath>
#include <string>

#include "utils/Assets.h"
#include "utils/Console.h"

Player::Player()
    : m_Texture()
    , m_Sprite(m_Texture)
{
    m_Sprite = Sprite(TextureHolder::GetTexture("graphics/player.png"));


    m_Sprite.setOrigin(Vector2f{25.f, 25.f});
}

void Player::spawn(const IntRect& arena, const Vector2f& resolution, int tileSize) {
    m_Position.x = static_cast<float>(arena.position.x) + static_cast<float>(arena.size.x) / 2.f;
    m_Position.y = static_cast<float>(arena.position.y) + static_cast<float>(arena.size.y) / 2.f;

    m_Arena.position = arena.position;
    m_Arena.size     = arena.size;

    m_TileSize = tileSize;

    m_Resolution = resolution;

    m_Sprite.setPosition(m_Position);

    Console::success("Player Spawned");
}

void Player::resetPlayerStats() {
    m_Speed     = START_SPEED;
    m_Health    = static_cast<int>(START_HEALTH);
    m_MaxHealth = static_cast<int>(START_HEALTH);
}

Time Player::getLastHitTime() const { return m_LastHit; }

bool Player::hit(sf::Time timeHit) {
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) {
        m_LastHit = timeHit;
        m_Health -= 10;
        return true;
    }
    return false;
}

FloatRect        Player::getPosition() const { return m_Sprite.getGlobalBounds(); }
Vector2f         Player::getCenter()   const { return m_Position; }
float                Player::getRotation() const { return m_Sprite.getRotation().asDegrees(); }
const sf::Sprite&    Player::getSprite()   const { return m_Sprite; }
int                  Player::getHealth()   const { return m_Health; }

void Player::moveLeft()  { m_LeftPressed  = true; }
void Player::moveRight() { m_RightPressed = true; }
void Player::moveUp()    { m_UpPressed    = true; }
void Player::moveDown()  { m_DownPressed  = true; }
void Player::stopLeft()  { m_LeftPressed  = false; }
void Player::stopRight() { m_RightPressed = false; }
void Player::stopUp()    { m_UpPressed    = false; }
void Player::stopDown()  { m_DownPressed  = false; }

void Player::update(float elapsedTime, sf::Vector2i mousePosition) {
    if (m_UpPressed)    m_Position.y -= m_Speed * elapsedTime;
    if (m_DownPressed)  m_Position.y += m_Speed * elapsedTime;
    if (m_RightPressed) m_Position.x += m_Speed * elapsedTime;
    if (m_LeftPressed)  m_Position.x -= m_Speed * elapsedTime;

    const float leftBound   = static_cast<float>(m_Arena.position.x + m_TileSize);
    const float rightBound  = static_cast<float>(m_Arena.position.x + m_Arena.size.x - m_TileSize);
    const float topBound    = static_cast<float>(m_Arena.position.y + m_TileSize);
    const float bottomBound = static_cast<float>(m_Arena.position.y + m_Arena.size.y - m_TileSize);

    if (m_Position.x > rightBound)  m_Position.x = rightBound;
    if (m_Position.x < leftBound)   m_Position.x = leftBound;
    if (m_Position.y > bottomBound) m_Position.y = bottomBound;
    if (m_Position.y < topBound)    m_Position.y = topBound;

    m_Sprite.setPosition(m_Position);

    constexpr float PI = 3.141f;
    float angleDeg = std::atan2f(
        static_cast<float>(mousePosition.y) - m_Resolution.y / 2.f,
        static_cast<float>(mousePosition.x) - m_Resolution.x / 2.f
    ) * 180.f / PI;

    m_Sprite.setRotation(degrees(angleDeg));
}

void Player::upgradeSpeed()       { m_Speed     += (START_SPEED * 0.2f); }
void Player::upgradeHealth()      { m_MaxHealth += (START_HEALTH * 0.2f); }
void Player::increaseHealthLevel(int amount) {
    m_Health += amount;
    if (m_Health > m_MaxHealth) m_Health = m_MaxHealth;
}