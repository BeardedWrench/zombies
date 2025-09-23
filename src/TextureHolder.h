#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <mutex>
using namespace sf;
class TextureHolder {
public:
    static TextureHolder& instance() {
        static auto* inst = new TextureHolder();
        return *inst;
    }

    const Texture& get(const std::string& relPath);

    static const Texture& GetTexture(const std::string& relPath) {
        return instance().get(relPath);
    }

private:
    TextureHolder() = default;
    TextureHolder(const TextureHolder&) = delete;
    TextureHolder& operator=(const TextureHolder&) = delete;

    std::unordered_map<std::string, std::unique_ptr<Texture>> m_cache;
    std::mutex m_mutex;
};