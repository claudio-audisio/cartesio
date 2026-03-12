#pragma once
#include <unordered_map>

using namespace std;


class CacheN {

    unordered_map<int, double> values;

public:
    void addValue(const int n, const double value) {
        values[n] = value;
    }

    bool contains(const int n) const {
        return values.contains(n);
    }

    double getValue(const int n) const {
        return values.at(n);
    }

};