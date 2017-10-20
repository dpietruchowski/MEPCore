#include "double.h"

const double& Double::operator *() const {
    return value;
}

double& Double::operator*() {
    return value;
}

Double Double::clone() const {
    return {value};
}

void Double::clear() {
    value = 0;
}

Double add(const std::vector<Double*>& args) {
    double sum = 0;
    for(const auto& arg: args)
        sum += **arg;
    return {sum};
}
Double sub(const std::vector<Double*>& args) {
    return {**args[0] - **args[1]};
}
Double mult(const std::vector<Double*>& args) {
    double product = 1;
    for(const auto arg: args)
        product *= **arg;
    return {product};
}
Double div(const std::vector<Double*>& args) {
    return {**args[0] / **args[1]};
}
