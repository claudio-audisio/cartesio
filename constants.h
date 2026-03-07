#pragma once

#include <vector>

#include "raylib.h"

#define FPS 10

// dimensions
#define BOARD_PADDING 50
#define AXIS_THICK 1
#define LINE_TICK 2
#define NOTCH_SIZE 3
#define DEF_SCALE 100
#define FONT_SIZE 16
#define FUNCTION_FONT_SIZE 20
#define HELP_FONT_SIZE 30

// colors
#define AXIS_COLOR CLITERAL(Color){ 128, 128, 128, 255 }
#define LINE_COLOR RAYWHITE
#define BG_COLOR CLITERAL(Color){ 31, 31, 31, 255 }
#define BG_COLOR_TRASP CLITERAL(Color){ 31, 31, 31, 200 }

// numbers
#define MAX_FLOAT   (float)pow(10.0, 9)

// help
inline const std::vector<std::string> HELP_LINES = {
    "H\t\tshow/hide help",
    "F\t\tenter function",
    "+/-\t\tzoom in/out",
    "O\t\treset view",
    "Q\t\tquit"
};