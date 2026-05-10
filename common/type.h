#pragma once

using namespace std;

enum PanelType {
    None,
    Shortcuts,
    Ingestion,
    Builtin
};

struct Function {
    string name;
    string definition;
    double(*implementation)(double);
};