#pragma once

#include "../common/constants.h"
#include "../common/type.h"
#include "board.h"


void keyPressionManager(Board& board) {
    if (board.panelType != Ingestion) {
        /*if (IsKeyDown(KEY_KP_ADD)) {
            board.upScaleX();
            board.upScaleY();
            return;
        }

        if (IsKeyDown(KEY_KP_SUBTRACT)) {
            board.downScaleX();
            board.downScaleY();
            return;
        }*/

        int key = GetKeyPressed();

        while (key != 0) {
            switch (key) {
            case KEY_H: board.showShortcuts(); break;
            case KEY_N: board.reset(); break;
            case KEY_F: board.startEnteringFunction(); return;
            case KEY_R: board.realNatural(); break;
            case KEY_L: board.setLinePoint(); break;
            case KEY_B: board.showBuiltinStuff(); break;
            case KEY_KP_4: board.downScaleX(); break;
            case KEY_KP_6: board.upScaleX(); break;
            case KEY_KP_2: board.downScaleY(); break;
            case KEY_KP_8: board.upScaleY(); break;
            case KEY_KP_ADD: board.upScaleX(); board.upScaleY(); break;
            case KEY_KP_SUBTRACT: board.downScaleX(); board.downScaleY(); break;
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

    if (wheel > 0) {
        board.upScaleX();
        board.upScaleY();
    }
    else if (wheel < 0) {
        board.downScaleX();
        board.downScaleY();
    }
}

void mouseClickManagement(Board& board) {
    // TODO valorizzare le coordinate ?
    // tracciare le linee tratteggiate fino agli assi ?
}