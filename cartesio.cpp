#include <iostream>

#include "board/board.h"
#include "board/command.h"

Board board;

void init() {
	const float width = MONITOR_WIDTH / ENV_SCALE;
	const float height = MONITOR_HEIGHT / ENV_SCALE;
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_HIGHDPI);
    InitWindow(width, height, "cartesio");
    SetTargetFPS(FPS);
	const Vector2 dpi   = GetWindowScaleDPI();

    SetWindowSize(width * dpi.x, height * dpi.y);

    board.init(width, height);
}

int main(int argc, char** argv) {
    init();

    if (argc == 2) {
        board.clearFunctions();
        board.addFunction({argv[1], argv[1], nullptr});
    }

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