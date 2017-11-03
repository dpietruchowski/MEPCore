#ifndef HAMMINGFITNESS_H
#define HAMMINGFITNESS_H

#include "genetic.h"
#include "image.h"

class HammingFitness: public mep::Fitness<Image>
{
public:
    HammingFitness(const Image& reference);
private:
    uint measure(const Image& input, const Image& reference) const;
};

#endif // HAMMINGFITNESS_H
