#pragma once

using namespace std;

enum PanelType {
    None,
    Shortcuts,
    Ingestion,
    Builtin
};

typedef long long LL;
typedef unsigned long long unsLL;

struct Function {
    string name;
    string definition;
    double(*implementation)(double);
};