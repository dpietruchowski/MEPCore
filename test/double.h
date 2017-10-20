#ifndef DOUBLE_H
#define DOUBLE_H

#include <vector>

struct Double {
    Double() = default;
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

#endif // DOUBLE_H
