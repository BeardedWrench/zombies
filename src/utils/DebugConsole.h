#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <string>
#include <string_view>

class DebugConsole {
public:
    enum class Level { Info, Warn, Error, Log, Success };

    DebugConsole() = default;


    bool init(const std::string& fontPath = "fonts/lucon.ttf",
              unsigned int charSize = 14);

    void toggle() { m_visible = !m_visible; }
    bool visible() const { return m_visible; }

    void log(std::string_view msg, Level level = Level::Log);
    void info(const std::string_view msg) { log(msg, Level::Info); }
    void warn(const std::string_view msg) { log(msg, Level::Warn); }
    void error(const std::string_view msg) { log(msg, Level::Error); }
    void success(const std::string_view msg) { log(msg, Level::Success); }
    void clear();

    bool handleEvent(const sf::Event& e);
    void draw(sf::RenderWindow& window);

    void setHeightRatio(float r) { m_heightRatio = std::clamp(r, 0.2f, 1.0f); }
    void setMaxLines(std::size_t n) { m_maxLines = n; while (m_lines.size() > m_maxLines) m_lines.pop_front(); }

private:
    struct Line {
        std::string text;
        Level level;
    };

    bool m_visible = false;
    std::deque<Line> m_lines;
    std::size_t m_maxLines = 1000;

    sf::Font           m_font;
    sf::RectangleShape m_bg;

    float        m_heightRatio = 0.6f;
    unsigned int m_charSize    = 14;
    int          m_scroll      = 0;
};