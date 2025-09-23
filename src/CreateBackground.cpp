#include "ZombieArena.h"
#include <SFML/Graphics.hpp>
#include <random>

int createBackground(VertexArray& rVA, const IntRect arena) {
    constexpr int TILE_SIZE     = 50;
    constexpr int TILE_TYPES    = 3;   // number of non-border tile variants
    constexpr int VERTS_PER_TILE = 6;  // two triangles

    const int worldWidth  = arena.size.x / TILE_SIZE;
    const int worldHeight = arena.size.y / TILE_SIZE;

    // Build triangles instead of quads
    rVA.clear();
    rVA.setPrimitiveType(PrimitiveType::Triangles);
    rVA.resize(static_cast<std::size_t>(worldWidth) * worldHeight * VERTS_PER_TILE);

    // RNG once (don’t re-seed per tile)
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution dist(0, TILE_TYPES - 1);

    // Offset if arena doesn’t start at (0,0)
    const auto baseX = static_cast<float>(arena.position.x);
    const auto baseY = static_cast<float>(arena.position.y);

    std::size_t currentVertex = 0;
    for (int w = 0; w < worldWidth; ++w) {
        for (int h = 0; h < worldHeight; ++h) {
            // World-space corners
            const float left   = baseX + w * TILE_SIZE;
            const float top    = baseY + h * TILE_SIZE;
            const float right  = left + TILE_SIZE;
            const float bottom = top  + TILE_SIZE;

            // Texture-space corners (choose row)
            int verticalOffset;
            if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1) {
                // Border row lives at TILE_TYPES * TILE_SIZE
                verticalOffset = TILE_TYPES * TILE_SIZE;
            } else {
                verticalOffset = dist(rng) * TILE_SIZE; // random inner variant
            }

            const Vector2f tlTex(0.f,                 static_cast<float>(verticalOffset));
            const Vector2f trTex(static_cast<float>(TILE_SIZE), static_cast<float>(verticalOffset));
            const Vector2f brTex(static_cast<float>(TILE_SIZE), static_cast<float>(verticalOffset + TILE_SIZE));
            const Vector2f blTex(0.f,                 static_cast<float>(verticalOffset + TILE_SIZE));

            // Two triangles per tile: (TL, TR, BR) and (TL, BR, BL)
            // Positions
            rVA[currentVertex + 0].position = { left,  top    }; // TL
            rVA[currentVertex + 1].position = { right, top    }; // TR
            rVA[currentVertex + 2].position = { right, bottom }; // BR

            rVA[currentVertex + 3].position = { left,  top    }; // TL
            rVA[currentVertex + 4].position = { right, bottom }; // BR
            rVA[currentVertex + 5].position = { left,  bottom }; // BL

            // TexCoords
            rVA[currentVertex + 0].texCoords = tlTex;
            rVA[currentVertex + 1].texCoords = trTex;
            rVA[currentVertex + 2].texCoords = brTex;

            rVA[currentVertex + 3].texCoords = tlTex;
            rVA[currentVertex + 4].texCoords = brTex;
            rVA[currentVertex + 5].texCoords = blTex;

            currentVertex += VERTS_PER_TILE;
        }
    }

    return TILE_SIZE;
}