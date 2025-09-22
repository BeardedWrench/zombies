#include "TextureHolder.h"
#include "utils/Assets.h"

const sf::Texture& TextureHolder::get(const std::string& relPath) {
    std::scoped_lock lock(m_mutex);

    if (auto it = m_cache.find(relPath); it != m_cache.end()) {
        return *it->second;
    }

    auto tex = std::make_unique<sf::Texture>();
    loadAsset(*tex, relPath);
    tex->setRepeated(false);
    tex->setSmooth(false);

    const sf::Texture& ref = *tex;
    m_cache.emplace(relPath, std::move(tex));
    return ref;
}