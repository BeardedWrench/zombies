#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet {
    public:
        Bullet();

        bool isInFlight() const;

        void stop();
        void shoot(Vector2f origin, Vector2f destination);
        void update(float elapsedTime);

        FloatRect getPosition() const;
        RectangleShape getShape();

    private:
        Vector2f m_Position;
        RectangleShape m_BulletShape;

        bool m_InFlight = false;
        float m_BulletSpeed = 1000;

        float m_BulletDistanceX{};
        float m_BulletDistanceY{};

        float m_MaxX{};
        float m_MinX{};
        float m_MaxY{};
        float m_MinY{};
};
