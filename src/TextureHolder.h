#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <mutex>

class TextureHolder {
public:
    static TextureHolder& instance() {
        static auto* inst = new TextureHolder();
        return *inst;
    }

    const sf::Texture& get(const std::string& relPath);

    static const sf::Texture& GetTexture(const std::string& relPath) {
        return instance().get(relPath);
    }

private:
    TextureHolder() = default;
    TextureHolder(const TextureHolder&) = delete;
    TextureHolder& operator=(const TextureHolder&) = delete;

    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_cache;
    std::mutex m_mutex;
};