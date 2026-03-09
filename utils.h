#pragma once

#include <format>
#include <raylib.h>


static void drawList(const std::vector<std::string>& list, const Vector2 position, const Font& font, const float fontSize, const Color textcolor) {
    for (int i = 0; i < list.size(); i++) {
        DrawTextEx(font, list.at(i).c_str(), {position.x, (position.y + static_cast<float>(fontSize * 1.2 * i))}, fontSize, 1, textcolor);
    }
}

static void drawList(const std::vector<std::string>& list, const Vector2 position, const Font& font, const float fontSize, const std::vector<Color>& textcolors) {
    for (int i = 0; i < list.size(); i++) {
        DrawTextEx(font, list.at(i).c_str(), {position.x, (position.y + static_cast<float>(fontSize * 1.2 * i))}, fontSize, 1, textcolors.at(i));
    }
}

static std::string toString(const double value) {
    return std::format("{:.4g}", value);
}

static std::string toString(const Vector2 point) {
    return std::format("{:.4g} : {:.4g}", point.x, point.y);
}

