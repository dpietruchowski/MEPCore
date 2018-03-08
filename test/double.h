#ifndef DOUBLE_H
#define DOUBLE_H

#include <vector>
#include <iostream>
#include <math.h>
#include "genetic/fitness.h"

struct Double {
    Double() = default;
    Double(const Double&) = default;
    Double& operator=(const Double&) = default;
    double value;
    const double& operator*() const;
    double& operator*();
    Double clone() const;
    void clear();
};

Double add(const std::vector<Double*>& args);
Double sub(const std::vector<Double*>& args);
Double mult(const std::vector<Double*>& args);
Double div(const std::vector<Double*>& args);

class DoubleFitness: public mep::Fitness<Double> {
public:
    DoubleFitness(const Double& reference): mep::Fitness<Double>(reference)
    { }
    uint measure(const Double& input, const Double& reference) const override {
        return abs(input.value * 1000 - reference.value * 1000);
    }
};

#endif // DOUBLE_H
