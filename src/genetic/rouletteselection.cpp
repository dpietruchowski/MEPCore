#include "rouletteselection.h"

#include <assert.h>

namespace mep {

RouletteSelection::RouletteSelection(Selection::ScoreType *scoreType):
    Selection(scoreType)
{ }

uint RouletteSelection::selectIdx(
        const std::map<uint, Selection::Score> &scores) const
{
    double decision = ((double) std::rand() / (RAND_MAX));
    double sum = 0;
    for(const auto& score: scores) {
        sum += score.second.normalized;
        if(decision <= sum)
            return score.first;
    }
    //should never get here
    assert(false);
    return 0;
}

void RouletteSelection::normalize(std::map<uint, Selection::Score> &scores,
                                  uint worstScore)
{
    int sumOfScores = 0;
    for(auto& score : scores)
    {
        score.second.normalized = (worstScore - score.second.value + 1);
        sumOfScores += score.second.normalized;
    }

    for(auto& score : scores)
    score.second.normalized = score.second.normalized / sumOfScores;

}

FitnessRouletteSelection::FitnessRouletteSelection():
    RouletteSelection(new Selection::FitnessScore())
{

}

RankRouletteSelection::RankRouletteSelection():
    RouletteSelection(new Selection::RankScore())
{

}

}
