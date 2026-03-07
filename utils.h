#pragma once

#include <format>
#include <raylib.h>


static std::string toString(const double value) {
    return std::format("{:.4g}", value);
}

static std::string toString(const Vector2 point) {
    return std::format("{:.4g} : {:.4g}", point.x, point.y);
}

