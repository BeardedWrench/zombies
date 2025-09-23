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
                     const unsigned int charSize = 14) {
        return instance().init(fontPath, charSize);
    }

    inline void toggle() { instance().toggle(); }
    inline bool visible() { return instance().visible(); }
    inline void clear() { instance().clear(); }

    inline void info(const std::string_view msg)  { instance().info(msg); }
    inline void warn(const std::string_view msg)  { instance().warn(msg); }
    inline void error(const std::string_view msg) { instance().error(msg); }
    inline void log(const std::string_view msg) { instance().log(msg); }
    inline void success(const std::string_view msg) { instance().success(msg); }

    template <class... Ts>
    void info(Ts&&... parts)  { std::ostringstream os; (os << ... << parts); instance().info(os.str()); }
    template <class... Ts>
    void warn(Ts&&... parts)  { std::ostringstream os; (os << ... << parts); instance().warn(os.str()); }
    template <class... Ts>
    void error(Ts&&... parts) { std::ostringstream os; (os << ... << parts); instance().error(os.str()); }
    template <class... Ts>
    void log(Ts&&... parts) { std::ostringstream os; (os << ... << parts); instance().log(os.str()); }
    template <class... Ts>
    void success(Ts&&... parts) { std::ostringstream os; (os << ... << parts); instance().success(os.str()); }

    inline bool handleEvent(const Event& e) { return instance().handleEvent(e); }
    inline void draw(RenderWindow& window)  { instance().draw(window); }

    inline void setHeightRatio(const float r) { instance().setHeightRatio(r); }
    inline void setMaxLines(const std::size_t n) { instance().setMaxLines(n); }

}