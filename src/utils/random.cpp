#include "random.h"

namespace mep {

Random::Random(): rd_{}, gen_{rd_()}
{ }

uint Random::operator()(uint max)
{
    std::binomial_distribution<uint> dis(max, 0.6);
    return dis(gen_);
}

DoubleRandom::DoubleRandom(double min, double max):
    dis_(min, max)
{ }

double DoubleRandom::operator()()
{
    return dis_(gen_);
}

void DoubleRandom::reset()
{
    dis_.reset();
}

UintRandom::UintRandom(uint min, uint max):
    dis_(min, max)
{ }

uint UintRandom::operator()()
{
    return dis_(gen_);
}

void UintRandom::reset()
{
    dis_.reset();
}

BinomialUintRandom::BinomialUintRandom(uint t, double p):
    dis_(t, p)
{ }

uint BinomialUintRandom::operator()()
{
    return dis_(gen_);
}

void BinomialUintRandom::reset()
{
    dis_.reset();
}

}
