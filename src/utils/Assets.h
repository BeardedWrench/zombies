#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <string>
#include <stdexcept>
#include <iostream>

inline std::string assetPath(const std::string& rel) {
#ifdef RESOURCE_DIR
    return std::string(RESOURCE_DIR) + "/" + rel;
#else
    return rel;
#endif
}

inline void loadAsset(sf::Texture& tex, const std::string& relPath) {
    const auto full = assetPath(relPath);
    if (!tex.loadFromFile(full)) {
        std::cerr << "Failed to load texture: " << full << "\n";
        throw std::runtime_error("Missing texture: " + full);
    }
}

inline void loadAsset(sf::SoundBuffer& buf, const std::string& relPath) {
    const auto full = assetPath(relPath);
    if (!buf.loadFromFile(full)) {
        std::cerr << "Failed to load sound: " << full << "\n";
        throw std::runtime_error("Missing sound: " + full);
    }
}

inline void loadAsset(sf::Font& font, const std::string& relPath) {
    const auto full = assetPath(relPath);
    if (!font.openFromFile(full)) {
        std::cerr << "Failed to load font: " << full << "\n";
        throw std::runtime_error("Missing font: " + full);
    }
}

inline void loadAsset(sf::Shader& shader,
                      const std::string& vertRel,
                      const std::string& fragRel) {
    const auto v = vertRel.empty() ? std::string{} : assetPath(vertRel);
    const auto f = fragRel.empty() ? std::string{} : assetPath(fragRel);

    bool ok = false;
    if (!v.empty() && !f.empty()) {
        ok = shader.loadFromFile(v, f);
    } else if (!v.empty()) {
        ok = shader.loadFromFile(v, sf::Shader::Type::Vertex);
    } else if (!f.empty()) {
        ok = shader.loadFromFile(f, sf::Shader::Type::Fragment);
    }

    if (!ok) {
        std::cerr << "Failed to load shader: vert=\"" << (v.empty()?"<none>":v)
                  << "\" frag=\"" << (f.empty()?"<none>":f) << "\"\n";
        throw std::runtime_error("Missing/invalid shader");
    }
}

inline bool tryLoad(sf::Texture& tex, const std::string& relPath) {
    const auto full = assetPath(relPath);
    if (!tex.loadFromFile(full)) {
        std::cerr << "tryLoad(texture) failed: " << full << "\n";
        return false;
    }
    return true;
}
inline bool tryLoad(sf::SoundBuffer& buf, const std::string& relPath) {
    const auto full = assetPath(relPath);
    if (!buf.loadFromFile(full)) {
        std::cerr << "tryLoad(sound) failed: " << full << "\n";
        return false;
    }
    return true;
}
inline bool tryLoad(sf::Font& font, const std::string& relPath) {
    const auto full = assetPath(relPath);
    if (!font.openFromFile(full)) {
        std::cerr << "tryLoad(font) failed: " << full << "\n";
        return false;
    }
    return true;
}