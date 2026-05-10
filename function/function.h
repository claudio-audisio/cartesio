#pragma once

#include <cmath>

#include "cl_types.h"
#include "cache.h"
#include "../muparser/muParser.h"
#include "../common/type.h"


class FunctionProvider {
public:

    static mu::Parser *parseFunction(const Function& function, double* varX) {
        try {
            std::string realDef = function.definition.substr(4);
            mu::Parser *parser = new mu::Parser();
            parser->DefineVar("x", varX);

            if (function.implementation != nullptr) {
                parser->DefineFun(realDef.substr(0, realDef.length() - 3), function.implementation);
            }

            parser->SetExpr(realDef);
            parser->Eval();
            return parser;
        } catch (mu::Parser::exception_type &e) {
            return nullptr;
        }
    }


    static double collatzSteps(const double value) {
        cl::LL n = static_cast<cl::LL>(value);
        int steps = 0;

        if (n <= 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        while (n != 1) {
            n = n & 1 ? (n * 3) + 1 : n / 2;
            steps++;
        }

        return steps;
    }

    static double leibnizPi(const double value) {
        const int n = static_cast<int>(value);
        double pi = 0;

        if (n < 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        for (int i = 0; i <= n; i++) {
            pi += pow(-1, i) / (2 * i + 1);
        }

        return pi * 4.0;
    }

    static double eApprox(const double value) {
        const int n = static_cast<int>(value);
        double e = 0;

        if (n < 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        for (int i = 0; i <= n; i++) {
            e += 1 / tgamma(i + 1);
        }

        return e;
    }

    static double weierstrass(const double value) {
        double sum = 0;
        double a = 0.5;   // 0 < a < 1, controls amplitude decay
        int    b = 7;     // odd integer, controls frequency growth

        for (int n = 0; n < 20; n++) {
            sum += pow(a, n) * cos(pow(b, n) * M_PI * value);
        }

        return sum;
    }

    static double sievePrimes(const double value) {
        const int n = static_cast<int>(value);

        if (n <= 1) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        std::vector<bool> isPrime(n + 1, true);
        isPrime[0] = isPrime[1] = false;

        for (int i = 2; i * i <= n; i++)
            if (isPrime[i])
                for (int j = i * i; j <= n; j += i)
                    isPrime[j] = false;

        cl::LL count = 0;
        for (int i = 2; i <= n; i++)
            if (isPrime[i])
                count++;

        return count;
    }

};

