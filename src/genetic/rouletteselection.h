#ifndef MEP_GENETIC_ROULETTESELECTION_H
#define MEP_GENETIC_ROULETTESELECTION_H

#include "selection.h"

namespace mep {

class RouletteSelection: public Selection
{
public:
    RouletteSelection(ScoreType *scoreType);

private:
    uint selectIdx(const std::map<uint, Score>& scores) const override;
    void normalize(std::map<uint, Score>& scores, uint worstScore) override;
};

class RankRouletteSelection: public RouletteSelection {
public:
    RankRouletteSelection();
};

class FitnessRouletteSelection: public RouletteSelection {
public:
    FitnessRouletteSelection();
};

}

#endif // MEP_GENETIC_ROULETTESELECTION_H
