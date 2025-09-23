#include "Bullet.h"

#include "utils/Console.h"


Bullet::Bullet() { m_BulletShape.setSize(Vector2f(2,2)); }

void Bullet::shoot(const Vector2f origin, const Vector2f destination) {
    m_InFlight = true;
    m_Position = origin;
    float gradient = (origin.x - destination.x) / (origin.y - destination.y);

    if (gradient < 0) gradient *= -1;

    const float ratioXY = m_BulletSpeed / (1 + gradient);

    m_BulletDistanceX = ratioXY * gradient;
    m_BulletDistanceY = ratioXY;

    if (destination.x < origin.x) m_BulletDistanceX *= -1;
    if (destination.y < origin.y) m_BulletDistanceY *= -1;

    constexpr float range = 1000;
    m_MinX = origin.x - range;
    m_MaxX = origin.x + range;
    m_MinY = origin.y - range;
    m_MaxY = origin.y + range;

    m_BulletShape.setPosition(origin);
}

void Bullet::stop() { m_InFlight = false; }

bool Bullet::isInFlight() const { return m_InFlight; }

FloatRect Bullet::getPosition() const { return m_BulletShape.getGlobalBounds(); }

RectangleShape Bullet::getShape() { return m_BulletShape; }

void Bullet::update(const float elapsedTime) {
    m_Position += {m_BulletDistanceX * elapsedTime, m_BulletDistanceY * elapsedTime};
    m_BulletShape.setPosition(m_Position);

    if (m_Position.x < m_MinX || m_Position.x > m_MaxX || m_Position.y < m_MinY || m_Position.y > m_MaxY) {
        m_InFlight = false;
    }
}


