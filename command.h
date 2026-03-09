#pragma once

#include "constants.h"
#include "type.h"


double getStepZoom(const double scale) {
    return scale * 0.1;
}

void keyPressionManager(Board& board) {
    if (board.panelType != Ingestion) {
        if (IsKeyDown(KEY_KP_ADD)) {
            board.scale += getStepZoom(board.scale);
            return;
        }

        if (IsKeyDown(KEY_KP_SUBTRACT)) {
            board.scale -= getStepZoom(board.scale);
            return;
        }

        int key = GetKeyPressed();

        while (key != 0) {
            switch (key) {
            case KEY_H: board.showShortcuts(); break;
            case KEY_N: board.reset(); break;
            case KEY_F: board.startEnteringFunction(); return;
            case KEY_L: board.setLinePoint(); break;
            case KEY_B: board.showBuiltinStuff(); break;
            case KEY_KP_ADD: board.scale += getStepZoom(board.scale);; break;
            case KEY_KP_SUBTRACT: board.scale -= getStepZoom(board.scale); break;
            case KEY_UP:
            case KEY_DOWN:
            case KEY_RIGHT:
            case KEY_LEFT: board.changeQuadrant(key); break;
            case KEY_O: board.resetView(); break;
            case KEY_Q: exit(0);
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

void mouseClickManagement(Board& board) {

}