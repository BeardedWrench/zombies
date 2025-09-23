#include "DebugConsole.h"
#include <algorithm>
#include <sstream>
#include "Assets.h"

static Color levelColor(const DebugConsole::Level lvl) {
    switch (lvl) {
        case DebugConsole::Level::Log: return {255, 255, 255};;
        case DebugConsole::Level::Success: return {0, 255, 75};;
        case DebugConsole::Level::Info:  return {200, 200, 200};
        case DebugConsole::Level::Warn:  return {255, 210, 130};
        case DebugConsole::Level::Error: return {255, 120, 120};
    }
    return Color::White;
}

bool DebugConsole::init(const std::string& fontPath, const unsigned int charSize) {
    m_charSize = (charSize == 0 ? 14 : charSize);

    try {
        loadAsset(m_font, fontPath);
    } catch (...) {
        m_visible = false;
        std::cerr << "DebugConsole: failed to load font: " << fontPath << "\n";
        return false;
    }

    m_bg.setFillColor(Color(0, 0, 0, 170));
    m_bg.setOutlineThickness(1.f);
    m_bg.setOutlineColor(Color(255, 255, 255, 60));
    return true;
}

void DebugConsole::log(const std::string_view msg, const Level level) {
    m_lines.push_back({std::string(msg), level});
    if (m_lines.size() > m_maxLines) m_lines.pop_front();
}


void DebugConsole::clear() {
    m_lines.clear();
    m_scroll = 0;
}

bool DebugConsole::handleEvent(const Event& e) {
    if (const auto* kp = e.getIf<Event::KeyPressed>()) {
        if (kp->code == Keyboard::Key::Grave) {
            toggle();
            return true;
        }
        if (!m_visible) return false;

        if (kp->code == Keyboard::Key::PageUp)   { m_scroll += 5; return true; }
        if (kp->code == Keyboard::Key::PageDown) { m_scroll = std::max(0, m_scroll - 5); return true; }
        if (kp->code == Keyboard::Key::Home)     { m_scroll = static_cast<int>(std::max<std::size_t>(0, m_lines.size())); return true; }
        if (kp->code == Keyboard::Key::End)      { m_scroll = 0; return true; }
    }
    return false;
}

void DebugConsole::draw(RenderWindow& window) {
    if (!m_visible) return;

    // Panel geometry
    const Vector2u winSize = window.getSize();
    const auto w = static_cast<float>(winSize.x);
    const float h = static_cast<float>(winSize.y) * m_heightRatio;
    m_bg.setPosition({0.f, 0.f});
    m_bg.setSize(Vector2f{w, h});

    // Line metrics & visible range
    const float lineH = m_charSize * 1.25f;
    const int maxOnScreen = std::max(1, static_cast<int>(h / lineH) - 2);
    const int total = static_cast<int>(m_lines.size());
    const int start = std::max(0, total - maxOnScreen - m_scroll);
    const int end   = std::max(0, std::min(total, start + maxOnScreen));

    // Switch to screen-space
    const View prev = window.getView();
    window.setView(window.getDefaultView());

    // Panel
    window.draw(m_bg);

    // Draw each line with its own color
    float y = 6.f;
    for (int i = start; i < end; ++i) {
        const auto&[text, level] = m_lines[static_cast<std::size_t>(i)];
        Text lineText(m_font, String(text), m_charSize);
        lineText.setFillColor(levelColor(level));
        lineText.setPosition({8.f, y});
        window.draw(lineText);
        y += lineH;
    }

    window.setView(prev);
}