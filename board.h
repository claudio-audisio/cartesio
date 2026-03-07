#pragma once

#include <format>

#include "constants.h"
#include "function.h"
#include "utils.h"


class Board {
public:
    float width, height, scale;
    Vector2 center;
    Font font;
    bool showHelpPanel, enteringFunction;
    std::string function;
    int quadrant;

    void init(const float w, const float h) {
        width = w;
        height = h;
        scale = DEF_SCALE;
        quadrant = 5;
        function = "";
        showHelpPanel = false;
        enteringFunction = false;
        setReferences();
        loadFonts();
    }

    void setReferences() {
        switch (quadrant) {
        case 1: center = Vector2(width - BOARD_PADDING, BOARD_PADDING); break;
        case 2: center = Vector2(width / 2, BOARD_PADDING); break;
        case 3: center = Vector2(BOARD_PADDING, BOARD_PADDING); break;
        case 4: center = Vector2(width - BOARD_PADDING, height / 2); break;
        case 5: center = Vector2(width / 2, height / 2); break;
        case 6: center = Vector2(BOARD_PADDING, height / 2); break;
        case 7: center = Vector2(width - BOARD_PADDING, height - BOARD_PADDING); break;
        case 8: center = Vector2(width / 2, height - BOARD_PADDING); break;
        case 9: center = Vector2(BOARD_PADDING, height - BOARD_PADDING); break;
        default: break;
        }
    }

    void loadFonts() {
        font = LoadFontEx("/home/claudio/Projects/cartesio/asset/NotoSans-Regular.ttf", HELP_FONT_SIZE, nullptr, 0);
        SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
    }
    
    void drawBoard() {
        setReferences();
        drawAxes();
        drawNotch();
        auto mousePos = toCartesianCoord(GetMousePosition());
        DrawTextEx(font, function.c_str(), { 10, 10}, FONT_SIZE, 1, LINE_COLOR);
        DrawTextEx(font, toString(scale).c_str(), { 10, 30}, FONT_SIZE, 1, LINE_COLOR);
        DrawTextEx(font, toString(mousePos).c_str(), { 10, 50}, FONT_SIZE, 1, LINE_COLOR);
    }

    void drawAxes() {
        DrawLineEx({center.x, 0}, {center.x, height}, AXIS_THICK, AXIS_COLOR);
        DrawLineEx({0, center.y}, {width, center.y}, AXIS_THICK, AXIS_COLOR);
    }

    void drawNotch() {
        // TODO al momento quando si zoomma i notch rimangono fermi e cambiano le etichette
        // dovrebbe essere al contrario, le etichette si spostanno e i notch compaiono o scampaiono a secondo della densita'

        int axisLength = std::max(width - center.x, center.x);

        for (int i = DEF_SCALE; i < axisLength; i += DEF_SCALE) {
            DrawLineEx({center.x + i, center.y - NOTCH_SIZE}, {center.x + i, center.y + NOTCH_SIZE}, AXIS_THICK, AXIS_COLOR);
            DrawLineEx({center.x - i, center.y - NOTCH_SIZE}, {center.x - i, center.y + NOTCH_SIZE}, AXIS_THICK, AXIS_COLOR);

            DrawTextEx(font, toString(i / scale).c_str(), { center.x + i + 5, center.y}, FONT_SIZE, 1, AXIS_COLOR);
            DrawTextEx(font, toString(-i / scale).c_str(), { center.x - i, center.y}, FONT_SIZE, 1, AXIS_COLOR);
        }

        axisLength = std::max(height - center.y, center.y);

        for (int i = DEF_SCALE; i < axisLength; i += DEF_SCALE) {
            DrawLineEx({center.x - NOTCH_SIZE, center.y + i}, {center.x + NOTCH_SIZE, center.y + i}, AXIS_THICK, AXIS_COLOR);
            DrawLineEx({center.x - NOTCH_SIZE, center.y - i}, {center.x + NOTCH_SIZE, center.y - i}, AXIS_THICK, AXIS_COLOR);

            DrawTextEx(font, toString(i / scale).c_str(), { center.x + 5, center.y - i}, FONT_SIZE, 1, AXIS_COLOR);
            DrawTextEx(font, toString(-i / scale).c_str(), { center.x + 5, center.y + i}, FONT_SIZE, 1, AXIS_COLOR);
        }
    }

    void drawPanel() {
        if (showHelpPanel) {
            DrawRectangleRec({0, 0, width, height}, BG_COLOR_TRASP);
            Vector2 startPoint = {width / 2 - 100, height / 3 - (static_cast<float>(HELP_FONT_SIZE * HELP_LINES.size()) / 2)};

            for (int i = 0; i < HELP_LINES.size(); i++) {
                DrawTextEx(font, HELP_LINES.at(i).c_str(), {startPoint.x, (startPoint.y + static_cast<float>(HELP_FONT_SIZE * 1.2 * i))}, HELP_FONT_SIZE, 1, RAYWHITE);
            }

        }

        if (enteringFunction) {
            DrawRectangleRec({0, 0, width, height}, BG_COLOR_TRASP);
            DrawTextEx(font, function.c_str(), {width / 2 - static_cast<float>(function.size() * HELP_FONT_SIZE / 5), height / 3}, HELP_FONT_SIZE, 1, RAYWHITE);
        }
    }

    Vector2 getXAxis() const {
        switch (quadrant % 3) {
        case 1: return {-width + BOARD_PADDING, BOARD_PADDING};
        case 2: return {-width / 2, width / 2};
        case 0: return {-BOARD_PADDING, width - BOARD_PADDING};
        }
    }

    void drawFunction(double (*func)(double)) const {
        Vector2 prevPoint;
        bool inScreen = false;
        Vector2 xAxis = getXAxis();

        for (double x = xAxis.x; x < xAxis.y; x++) {
            Vector2 point = {static_cast<float>(x), static_cast<float>(func(x / scale)) * scale};
            point = toScreenCoord(point, xAxis.x);

            if (inScreen/* || isInScreen(point)*/) {
                DrawLineBezier(prevPoint, point, LINE_TICK, LINE_COLOR);
            }

            inScreen = isInScreen(point);
            prevPoint = point;
        }
    }

    bool isInScreen(const Vector2 point) const {
        return point.y > 0 && point.y < height;
    }

    Vector2 toScreenCoord(Vector2 point, const int xOffset) const {
        if (point.y == std::numeric_limits<double>::infinity()) {
            point.y = MAX_FLOAT;
        }

        if (point.y == -std::numeric_limits<double>::infinity()) {
            point.y = -MAX_FLOAT;
        }

        float yOffset = height / 2;

        if (quadrant > 6) yOffset = height - BOARD_PADDING;
        if (quadrant < 4) yOffset = BOARD_PADDING;

        return {point.x + abs(xOffset), -point.y + yOffset};
    }

    Vector2 toCartesianCoord(const Vector2 point) const {
        return {(point.x - width / 2) / scale, (-point.y + height / 2) / scale};
    }

    void showHelp() {
        showHelpPanel = !showHelpPanel;
    }

    void startEnteringFunction() {
        showHelpPanel = false;
        function = "y = ";
        enteringFunction = true;
    }

};

