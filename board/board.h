#pragma once

#include <chrono>
#include <format>
#include <functional>
#include "cl_numbers.h"
#include "cl_time.h"
#include "../common/constants.h"
#include "../function/function.h"
#include "../utils/utils.h"
#include "../common/type.h"
#include "../function/cache.h"
#include "raygui/style_jungle.h"

using namespace std;


class Board {
public:
    float width, height, scaleX, scaleY;
    int scaleFactorX, scaleFactorY;
    bool natural, zoomOutBlocked;
    Vector2 center;
    Font font;
    PanelType panelType;
    bool linePoint, ready;
    vector<Function> functions;
    int quadrant;
    mu::Parser *parser;
    vector<bool> editMenu;
    char *inputText;
    string warning;

    void init(const float w, const float h) {
        width = w;
        height = h;
        scaleX = scaleY = DEF_SCALE;
        scaleFactorX = scaleFactorY = 2;
        quadrant = 5;
        ready = true;
        natural = false;
        linePoint = true;
        editMenu = {false, false, false};
        setReferences();
        parser = nullptr;
        panelType = None;
        inputText = static_cast<char*>(calloc(sizeof(char), 1024));
        addFunction({STARTING_FUNCTION, STARTING_FUNCTION, nullptr});
        setStyle();
    }

    void setStyle() {
        GuiLoadStyleJungle();
        loadFonts();
        GuiSetFont(font);
        GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);
        GuiSetStyle(DROPDOWNBOX, DROPDOWN_ARROW_HIDDEN, true);
        GuiSetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING, 0);
    }

    void addFunction(const Function& function) {
        functions.push_back(function);
    }

    void removeFunction(const int index) {
        functions.erase(functions.begin() + index);
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
        font = LoadFontEx("/home/claudio/Projects/cartesio/asset/SourceCodePro-Regular.ttf", PANEL_FONT_SIZE, nullptr, 0);
        SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
    }
    
    void drawBoard() {
        setReferences();
        drawAxes();
        drawNotch();
        drawMousePos();
    }

    void drawAxes() const {
        DrawLineEx({center.x, 0}, {center.x, height}, AXIS_THICK, AXIS_COLOR);
        DrawLineEx({0, center.y}, {width, center.y}, AXIS_THICK, AXIS_COLOR);
    }

    void drawNotch() const {
        int axisLength = max(width - center.x, center.x);

        for (int i = DEF_SCALE; i < axisLength; i += DEF_SCALE) {
            DrawLineEx({center.x + i, center.y - NOTCH_SIZE}, {center.x + i, center.y + NOTCH_SIZE}, AXIS_THICK, AXIS_COLOR);
            DrawLineEx({center.x - i, center.y - NOTCH_SIZE}, {center.x - i, center.y + NOTCH_SIZE}, AXIS_THICK, AXIS_COLOR);

            DrawTextEx(font, toString(i / scaleX).c_str(), { center.x + i + 5, center.y}, FONT_SIZE, 1, AXIS_COLOR);
            DrawTextEx(font, toString(-i / scaleX).c_str(), { center.x - i, center.y}, FONT_SIZE, 1, AXIS_COLOR);
        }

        axisLength = max(height - center.y, center.y);

        for (int i = DEF_SCALE; i < axisLength; i += DEF_SCALE) {
            DrawLineEx({center.x - NOTCH_SIZE, center.y + i}, {center.x + NOTCH_SIZE, center.y + i}, AXIS_THICK, AXIS_COLOR);
            DrawLineEx({center.x - NOTCH_SIZE, center.y - i}, {center.x + NOTCH_SIZE, center.y - i}, AXIS_THICK, AXIS_COLOR);

            DrawTextEx(font, toString(i / scaleY).c_str(), { center.x + 5, center.y - i}, FONT_SIZE, 1, AXIS_COLOR);
            DrawTextEx(font, toString(-i / scaleY).c_str(), { center.x + 5, center.y + i}, FONT_SIZE, 1, AXIS_COLOR);
        }
    }

    void drawMousePos() const {
        const auto mousePos = toCartesianCoord(GetMousePosition());

        if (warning.length() > 0) {
            DrawTextEx(font, warning.c_str(), {450, 8}, FONT_SIZE, 1, WARNING_COLOR);
        }

        DrawTextEx(font, natural ? "natural" : "real", {width - 500, height -25}, FONT_SIZE, 1, TEXT_COLOR);
        DrawTextEx(font, linePoint ? "line" : "point", {width - 400, height -25}, FONT_SIZE, 1, TEXT_COLOR);
        DrawTextEx(font, format("{} : {}", toString(scaleX), toString(scaleY)).c_str(), { width - 300, height - 25}, FONT_SIZE, 1, TEXT_COLOR);
        DrawTextEx(font, toString(mousePos).c_str(), { width - 200, height - 25}, FONT_SIZE, 1, TEXT_COLOR);
    }

    void drawPanel() {
        if (panelType == Ingestion) {
            GuiSetStyle(DEFAULT, TEXT_SIZE, PANEL_FONT_SIZE);
            DrawRectangleRec({0, 0, width, height}, BG_COLOR_TRASP);
            const auto rect = getCenteredRectangle(400, 30);
            memcpy(inputText, &Y_EQUAL, 4);

            if (GuiTextBox(rect, inputText, 1024, true)) {
                addFunction({"", string(inputText), nullptr});
                memset(inputText, 0, 1024);
                functionReady();
            }

            GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);
        }

        if (panelType == Shortcuts) {
            DrawRectangleRec({0, 0, width, height}, BG_COLOR_TRASP);
            const auto rect = getCenteredRectangle(300, 300);

            if (GuiWindowBox(rect, "shortcuts") == 1) {
                panelType = None;
            } else {
                drawList(HELP_LINES, {rect.x + 10, rect.y + 30}, font, FONT_SIZE, RAYWHITE);
            }
        }

        if (panelType == Builtin) {
            DrawRectangleRec({0, 0, width, height}, BG_COLOR_TRASP);
            const auto rect = getCenteredRectangle(500, 1000);

            if (GuiWindowBox(rect, "built-in stuff") == 1) {
                panelType = None;
            } else {
                drawList(BUILTIN_FUNCTIONS, {rect.x + 10, rect.y + 30}, font, FONT_SIZE, RAYWHITE);
                drawList(BUILTIN_OPERATORS, {rect.x + 10, rect.y + 560}, font, FONT_SIZE, RAYWHITE);
                drawList(TERNARY_OPERATORS, {rect.x + 10, rect.y + 880}, font, FONT_SIZE, RAYWHITE);
                drawList(BUILTIN_CONSTANTS, {rect.x + 10, rect.y + 930}, font, FONT_SIZE, RAYWHITE);
            }
        }
    }

    void drawFunction() {
        if (ready) {
            vector<int> invalidFunctions;

            for (int i = 0; i < functions.size(); i++) {
                auto start = chrono::steady_clock::now();
                double varX = 0;
                parser = FunctionProvider::parseFunction(functions[i], &varX);

                if (!parser) {
                    const Rectangle rect = getCenteredRectangle(400, 100);

                    if (GuiMessageBox(rect, "wrong function", functions[i].definition.c_str(), "ok") != -1) {
                        invalidFunctions.push_back(i);
                    }

                    continue;
                }

                Vector2 prevPoint, point;
                bool inScreen = false;
                const Vector2 xAxis = getXAxis();

                for (int x = xAxis.x; x < xAxis.y; x++) {
                    varX = static_cast<double>(x) / scaleX;

                    if (natural && !cl::isWholeNumber(varX)) {
                        continue;
                    }

                    point = {static_cast<float>(x), static_cast<float>(parser->Eval()) * scaleY};
                    point = toScreenCoord(point, xAxis.x);

                    if (linePoint) {
                        // TODO in caso di infinito bisogna tracciare una linea veriticale che va dal bordo fino al primo punto buono
                        // oppure dell'ultimo punto buono fino al bordo
                        if (inScreen) {
                            DrawLineBezier(prevPoint, point, LINE_TICK, LINE_COLORS.at(i));
                        }
                    } else {
                        if (isInScreen(point)) {
                            DrawCircleV(point, LINE_TICK, LINE_COLORS.at(i));
                        }
                    }

                    inScreen = isInScreen(point);
                    prevPoint = point;
                }

                auto time = cl::getElapsedMillis(start);

                if (time > 1000 / FPS) {
                    cout << format("{} {} ms", functions[i].name, time) << endl;
                    warning = "PERFORMANCE WARNING";
                } else {
                    warning = "";
                }
            }

            for (const int index : invalidFunctions) {
                removeFunction(index);
            }
        }
    }

    void clearFunctions() {
        functions.clear();
    }

    void reset() {
        clearFunctions();
        startEnteringFunction();
    }

    void startEnteringFunction() {
        ready = false;
        panelType = Ingestion;
        textBoxCursorIndex = 4;
        consumeKeyInput();
    }

    void functionReady() {
        panelType = None;
        ready = true;
    }

    void showBuiltinStuff() {
        panelType = panelType == Builtin ? None : Builtin;
    }

    void showShortcuts() {
        panelType = panelType == Shortcuts ? None : Shortcuts;
    }

    void changeEditMenu(const int index) {
        for (int i = 0; i < editMenu.size(); i++) {
            if (i == index) {
                editMenu[i] = !editMenu[i];
            } else {
                editMenu[i] = false;
            }
        }
    }

    void drawMenu() {
        Vector2 menuPosition = {0, 0};
        int selection = 0;

        if (GuiDropdownBox({menuPosition.x, menuPosition.y, 200, 30}, MENU, &selection, editMenu[0])) {
            changeEditMenu(0);
            switch (selection) {
            case 1: reset(); break;
            case 2: startEnteringFunction(); break;
            case 3: resetView(); break;
            case 4: showBuiltinStuff(); break;
            case 5: showShortcuts(); break;
            case 6: exit(0);
            default: break;
            }
        }
    }

    void drawSpecials() {
        Vector2 specialsPosition = {200, 0};
        int selection = 0;
        string specials = "specials";

        for (const auto & func : SPECIAL_FUNCTIONS) {
            specials += ";" + func.name;
        }

        if (GuiDropdownBox({specialsPosition.x, specialsPosition.y, 200, 30}, specials.c_str(), &selection, editMenu[2])) {
            changeEditMenu(2);

            if (selection != 0) {
                addFunction(SPECIAL_FUNCTIONS[selection - 1]);
            }
        }
    }

    void drawFunctionList() {
        Vector2 menuPosition = {width - 400, 0};
        int selection = 0;
        string functionList = "functions";

        for (const Function& function : functions) {
            functionList += ";" + function.definition;
        }

        if (functionList == "functions") {
            functionList = "no functions";
        }

        if (GuiDropdownBox({menuPosition.x, menuPosition.y, 400, 30}, functionList.c_str(), &selection, editMenu[1])) {
            changeEditMenu(1);

            if (selection != 0) {
                removeFunction(selection - 1);
            }
        }
    }

    void realNatural() {
        natural = !natural;
    }

    void setLinePoint() {
        linePoint = !linePoint;
    }

    void changeQuadrant(int key) {
        switch (key) {
            case KEY_UP: {
                    if (quadrant < 7) quadrant += 3;
                    break;
                }
            case KEY_DOWN: {
                    if (quadrant > 3) quadrant -= 3;
                    break;
                }
            case KEY_LEFT: {
                    if (quadrant % 3 != 1) quadrant -= 1;
                    break;
                }
            case KEY_RIGHT: {
                    if (quadrant % 3 != 0) quadrant += 1;
                    break;
                }
            default: break;
        }
    }

    void resetView() {
        panelType = None;
        scaleX = scaleY = DEF_SCALE;
        quadrant = 5;
    }

    Vector2 getXAxis() const {
        switch (quadrant % 3) {
        case 1: return {-width + BOARD_PADDING, BOARD_PADDING};
        case 2: return {-width / 2, width / 2};
        case 0: return {-BOARD_PADDING, width - BOARD_PADDING};
        default: return {0, 0};
        }
    }

    bool isInScreen(const Vector2 point) const {
        return point.y > 0 && point.y < height;
    }

    Vector2 toScreenCoord(Vector2 point, const int xOffset) const {
        if (point.y == numeric_limits<double>::infinity()) {
            point.y = MAX_FLOAT;
        }

        if (point.y == -numeric_limits<double>::infinity()) {
            point.y = -MAX_FLOAT;
        }

        return {point.x + abs(xOffset), -point.y + getYOffset()};
    }

    Vector2 toCartesianCoord(const Vector2 point) const {
        return {(point.x + getXAxis().x) / scaleX, (-point.y + getYOffset()) / scaleY};
    }

    float getYOffset() const {
        float yOffset = height / 2;

        if (quadrant > 6) yOffset = height - BOARD_PADDING;
        else if (quadrant < 4) yOffset = BOARD_PADDING;

        return yOffset;
    }

    static void consumeKeyInput() {
        while (GetCharPressed());
    }

    Rectangle getCenteredRectangle(const float rectW, const float rectH) const {
        return {width / 2  - rectW / 2, height / 2 - rectH / 2, rectW, rectH};
    }

    void upScaleX() {
        zoomOutBlocked = false;

        if (scaleFactorX < 12) {
            scaleFactorX++;
        }

        scaleX = powl(10, scaleFactorX);
    }

    void downScaleX() {
        if (!zoomOutBlocked) {
            if (scaleFactorX > -12) {
                scaleFactorX--;
            }

            scaleX = powl(10, scaleFactorX);
        }
    }

    void upScaleY() {
        if (scaleFactorY < 12) {
            scaleFactorY++;
        }

        scaleY = powl(10, scaleFactorY);
    }

    void downScaleY() {
        if (scaleFactorY > -12) {
            scaleFactorY--;
        }

        scaleY = powl(10, scaleFactorY);
    }

};

