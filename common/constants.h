#pragma once

#include <vector>
#include <map>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../raygui/raygui.h"

#include "../function/function.h"


#define FPS 20

// environment
#define ENV_SCALE 1.25
#define MONITOR_WIDTH 2560
#define MONITOR_HEIGHT 1400

// dimensions
#define BOARD_PADDING 50
#define AXIS_THICK 1
#define LINE_TICK 2
#define NOTCH_SIZE 3
#define DEF_SCALE 100
#define FONT_SIZE 16
#define PANEL_FONT_SIZE 24

// colors
#define AXIS_COLOR      CLITERAL(Color){ 128, 128, 128, 255 }
#define LINE_COLOR      ORANGE
#define TEXT_COLOR      RAYWHITE
#define WARNING_COLOR   CLITERAL(Color){ 255, 60, 60, 255 }
#define BG_COLOR        CLITERAL(Color){ 31, 31, 31, 255 }
#define BG_COLOR_TRASP  CLITERAL(Color){ 31, 31, 31, 200 }

// numbers
#define MAX_FLOAT   (float)pow(10.0, 9)



// functions
#define Y_EQUAL             "y = "
#define NO_FUNCTION         "no function"
#define STARTING_FUNCTION   "y = sin(x) * cos(x/3)"
#define GAUSSIAN_FUNCTION   "y = _e^(-x^2 / 2)"

inline const std::vector LINE_COLORS = {
    ORANGE,
    SKYBLUE,
    RAYWHITE,
    LIME,
    GOLD,
    GREEN,
    RED,
    PURPLE,
    VIOLET,
    BEIGE
};

// menu
#define MENU "menu;new board;add function;reset view;built-in stuff;shortcuts;quit"

// special functions
inline const std::vector<Function> SPECIAL_FUNCTIONS = {
    {
        "square wave",
        "y = (4/_pi)*(sin(x)+(1/3)*sin(3*x)+(1/5)*sin(5*x)+(1/7)*sin(7*x)+(1/9)*sin(9*x)+(1/11)*sin(11*x)+(1/13)*sin(13*x)+(1/15)*sin(15*x)+(1/17)*sin(17*x)+(1/19)*sin(19*x))",
        nullptr
    },
    {
        "collatz step",
        "y = collatzSteps(x)",
        &FunctionProvider::collatzSteps
    },
    {
        "leibniz pi approx",
        "y = leibnizPi(x)",
        &FunctionProvider::leibnizPi
    },
    {
        "e approx",
        "y = eApprox(x)",
        &FunctionProvider::eApprox
    },
    {
        "weierstrass",
        "y = weierstrass(x)",
        &FunctionProvider::weierstrass
    },
    {
        "sieve of eratosthenes",
        "y = sievePrimes(x)",
        &FunctionProvider::sievePrimes
    }
};

// help
inline const std::vector<std::string> HELP_LINES = {
    "H         show/hide shortcuts",
    "N         reset board",
    "F         enter function",
    "R         real/natural plane",
    "L         line/point",
    "B         show/hide built-in stuff",
    "+/-       zoom in/out",
    "keypad 4  zoom out axis X",
    "keypad 6  zoom in axis X",
    "keypad 2  zoom out axis Y",
    "keypad 8  zoom in axis Y",
    "arrows    quadrant selection",
    "O         reset view",
    "Q         quit"
};

inline const std::vector<std::string> BUILTIN_FUNCTIONS = {
    "*** built-in functions ***",
    "rnd()      generate a random number between 0 and 1",
    "sin(x)     sine function",
    "cos(x)     cosine function",
    "tan(x)     tangens function",
    "asin(x)    arcus sine function",
    "acos(x)    arcus cosine function",
    "atan(x)    arcus tangens function",
    "sinh(x)    hyperbolic sine function",
    "cosh(x)    hyperbolic cosine",
    "tanh(x)    hyperbolic tangens function",
    "asinh(x)   hyperbolic arcus sine function",
    "acosh(x)   hyperbolic arcus tangens function",
    "atanh(x)   hyperbolic arcus tangens function",
    "log2(x)    logarithm to the base 2",
    "log10(x)   logarithm to the base 10",
    "log(x)     logarithm to base e (2.71828...)",
    "ln(x)      logarithm to base e (2.71828...)",
    "exp(x)     e raised to the power of x",
    "sqrt(x)    square root of a value",
    "sign(x)    sign function -1 if x<0; 1 if x>0",
    "rint(x)    round to nearest integer",
    "abs(x)     absolute value",
    "min(x...)  min of all arguments",
    "max(x...)  max of all arguments",
    "sum(x...)  sum of all arguments",
    "avg(x...)  mean value of all arguments"
};

inline const std::vector<std::string> BUILTIN_OPERATORS = {
    "*** built-in operators (with priority) ***",
    "||   logical or        (1)",
    "&&   logical and       (2)",
    "|    bitwise or        (3)",
    "&    bitwise and       (4)",
    "<=   less or equal     (5)",
    ">=   greater or equal  (5)",
    "!=   not equal         (5)",
    "==   equal             (5)",
    ">    greater than      (5)",
    "<    less than         (5)",
    "+    addition          (6)",
    "-    subtraction       (6)",
    "*    multiplication    (7)",
    "/    division          (7)",
    "^    power raising     (8)",
};

inline const std::vector<std::string> TERNARY_OPERATORS = {
    "*** ternary operators ***",
    "?:  if then else operator  C++ style syntax"
};

inline const std::vector<std::string> BUILTIN_CONSTANTS = {
    "*** built-in constants ***",
    "_pi  The one and only pi.  3.141592653589793238462643",
    "_e   Euler's number.       2.718281828459045235360287"
};

