#include <iostream>

#include "board/board.h"
#include "board/command.h"

Board board;
float width, height;

void init() {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED);
    InitWindow(0, 0, "cartesio");
    SetTargetFPS(FPS);

    const int monitor = GetCurrentMonitor();
    width = static_cast<float>(GetMonitorWidth(monitor));
    height = static_cast<float>(GetMonitorHeight(monitor));
    board.init(width, height);
}

int main() {
    init();

    while (!WindowShouldClose()) {
        keyPressionManager(board);
        mouseWheelManagement(board);

        BeginDrawing();
        ClearBackground(BG_COLOR);

        board.drawBoard();
        board.drawFunction();
        board.drawPanel();
        board.drawMenu();
        board.drawSpecials();
        board.drawFunctionList();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}