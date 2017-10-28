#ifndef RANDOM_H
#define RANDOM_H

#include "types.h"
#include <random>

namespace mep {

class Random
{
public:
    Random();
    uint operator()(uint max);

private:
    std::random_device rd_;
protected:
    std::mt19937 gen_;
};

class DoubleRandom: public Random {
public:
    DoubleRandom(double min, double max);
    double operator()();
    void reset();

private:
    std::uniform_real_distribution<> dis_;
};


class UintRandom: public Random {
public:
    UintRandom(uint min, uint max);
    uint operator()();
    void reset();

private:
    std::uniform_int_distribution<uint> dis_;
};

class BinomialUintRandom: public Random {
public:
    BinomialUintRandom(uint t, double p);
    uint operator()();
    void reset();

private:
    std::binomial_distribution<uint> dis_;
};

}

#endif // RANDOM_H
