#pragma once
#include "DebugConsole.h"
#include <sstream>

// A tiny namespace that owns a single DebugConsole instance.

namespace Console {

    inline DebugConsole& instance() {
        static DebugConsole& s = *new DebugConsole();
        return s;
    }

    inline bool init(const std::string& fontPath = "fonts/lucon.ttf",
                     unsigned int charSize = 14) {
        return instance().init(fontPath, charSize);
    }

    inline void toggle() { instance().toggle(); }
    inline bool visible() { return instance().visible(); }
    inline void clear() { instance().clear(); }

    inline void info(std::string_view msg)  { instance().info(msg); }
    inline void warn(std::string_view msg)  { instance().warn(msg); }
    inline void error(std::string_view msg) { instance().error(msg); }
    inline void log(std::string_view msg) { instance().log(msg); }
    inline void success(std::string_view msg) { instance().success(msg); }

    template <class... Ts>
    inline void info(Ts&&... parts)  { std::ostringstream os; (os << ... << parts); instance().info(os.str()); }
    template <class... Ts>
    inline void warn(Ts&&... parts)  { std::ostringstream os; (os << ... << parts); instance().warn(os.str()); }
    template <class... Ts>
    inline void error(Ts&&... parts) { std::ostringstream os; (os << ... << parts); instance().error(os.str()); }
    template <class... Ts>
    inline void log(Ts&&... parts) { std::ostringstream os; (os << ... << parts); instance().log(os.str()); }
    template <class... Ts>
    inline void success(Ts&&... parts) { std::ostringstream os; (os << ... << parts); instance().success(os.str()); }

    inline bool handleEvent(const sf::Event& e) { return instance().handleEvent(e); }
    inline void draw(sf::RenderWindow& window)  { instance().draw(window); }

    inline void setHeightRatio(float r) { instance().setHeightRatio(r); }
    inline void setMaxLines(std::size_t n) { instance().setMaxLines(n); }

}