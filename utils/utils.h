#pragma once

#include <format>
#include <raylib.h>

#include "../common/type.h"

using namespace std;

static void drawList(const vector<string>& list, const Vector2 position, const Font& font, const float fontSize, const Color textcolor) {
    for (int i = 0; i < list.size(); i++) {
        DrawTextEx(font, list.at(i).c_str(), {position.x, (position.y + static_cast<float>(fontSize * 1.2 * i))}, fontSize, 1, textcolor);
    }
}

static void drawList(const vector<string>& list, const Vector2 position, const Font& font, const float fontSize, const vector<Color>& textcolors) {
    for (int i = 0; i < list.size(); i++) {
        DrawTextEx(font, list.at(i).c_str(), {position.x, (position.y + static_cast<float>(fontSize * 1.2 * i))}, fontSize, 1, textcolors.at(i));
    }
}

static string toString(const double value) {
    return format("{:.4g}", value);
}

static string toString(const Vector2 point) {
    return format("{:.4g} : {:.4g}", point.x, point.y);
}

inline unsLL getElapsedNanos(const chrono::time_point<chrono::steady_clock> start) {
    return chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - start).count();
}

inline unsLL getElapsedMicros(const chrono::time_point<chrono::steady_clock> start) {
    return chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start).count();
}

inline unsLL getElapsedMillis(const chrono::time_point<chrono::steady_clock> start) {
    return chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count();
}

inline unsLL getElapsedSeconds(const chrono::time_point<chrono::steady_clock> start) {
    return chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count();
}

