#include "TextureHolder.h"
#include "utils/Assets.h"

const Texture& TextureHolder::get(const std::string& relPath) {
    std::scoped_lock lock(m_mutex);

    if (const auto it = m_cache.find(relPath); it != m_cache.end()) {
        return *it->second;
    }

    auto tex = std::make_unique<Texture>();
    loadAsset(*tex, relPath);
    tex->setRepeated(false);
    tex->setSmooth(false);

    const Texture& ref = *tex;
    m_cache.emplace(relPath, std::move(tex));

    return ref;
}