#pragma once

#include "constants.h"


double getStepZoom(const double scale) {
    return scale * 0.1;
    //std::cout << "scale " << scale << " -> " << step << std::endl;
    //return step;
}

void keyPressionManager(Board& board) {
    if (board.enteringFunction) {
        int key = GetCharPressed();

        while (key != 0) {
            switch (key) {
            case KEY_BACKSPACE: board.function.pop_back(); break;
            default: board.function += static_cast<char>(key); break;
            }

            key = GetCharPressed();
        }

        switch (GetKeyPressed()) {
        case KEY_BACKSPACE: {
                if (board.function.size() > 0) {
                    board.function.pop_back();
                }
                break;
            }
        case KEY_ENTER: board.enteringFunction = false;
        default: break;
        }
    } else {
        int key = GetKeyPressed();

        if (IsKeyDown(KEY_KP_ADD)) {
            board.scale += getStepZoom(board.scale);
            return;
        }

        if (IsKeyDown(KEY_KP_SUBTRACT)) {
            board.scale -= getStepZoom(board.scale);
            return;
        }

        while (key != 0) {
            switch (key) {
            case KEY_KP_ADD: board.scale += getStepZoom(board.scale);; break;
            case KEY_KP_SUBTRACT: board.scale -= getStepZoom(board.scale); break;
            case KEY_H: board.showHelp(); break;
            case KEY_F: board.startEnteringFunction(); return;
            case KEY_O: board.scale = DEF_SCALE; board.quadrant = 5; break;
            case KEY_Q: exit(0);
            case KEY_KP_1: board.quadrant = 1; break;
            case KEY_KP_2: board.quadrant = 2; break;
            case KEY_KP_3: board.quadrant = 3; break;
            case KEY_KP_4: board.quadrant = 4; break;
            case KEY_KP_5: board.quadrant = 5; break;
            case KEY_KP_6: board.quadrant = 6; break;
            case KEY_KP_7: board.quadrant = 7; break;
            case KEY_KP_8: board.quadrant = 8; break;
            case KEY_KP_9: board.quadrant = 9; break;
            default: break;
            }

            key = GetKeyPressed();
        }
    }
}

void mouseWheelManagement(Board& board) {
    const float wheel = GetMouseWheelMove();

    if (wheel > 0) board.scale += getStepZoom(board.scale);
    else if (wheel < 0) board.scale -= getStepZoom(board.scale);
}

