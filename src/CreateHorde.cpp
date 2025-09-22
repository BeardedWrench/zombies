#include "ZombieArena.h"
#include <random>

std::vector<Zombie> createHorde(int numZombies, IntRect arena) {
    std::vector<Zombie> zombies;
    zombies.reserve(numZombies);

    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> sideDist(0,3);
    std::uniform_int_distribution<int> typeDist(0,2);

    const int minX = arena.position.x + 20;
    const int minY = arena.position.y + 20;
    const int maxX = arena.position.x + arena.size.x - 20;
    const int maxY = arena.position.y + arena.size.y - 20;

    std::uniform_int_distribution<int> xRange(minX, maxX);
    std::uniform_int_distribution<int> yRange(minY, maxY);

    for (int i = 0; i < numZombies; ++i) {
        int side = sideDist(rng);
        float x, y;
        switch (side) {
            case 0: x = minX;      y = yRange(rng); break;
            case 1: x = maxX;      y = yRange(rng); break;
            case 2: x = xRange(rng); y = minY;      break;
            default:x = xRange(rng); y = maxY;      break;
        }
        int type = typeDist(rng);

        zombies.emplace_back();
        zombies.back().spawn(x, y, type, i);
    }
    return zombies;
}