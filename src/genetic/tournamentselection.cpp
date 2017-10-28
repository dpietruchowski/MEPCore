#include "tournamentselection.h"

namespace mep {

TournamentSelection::TournamentSelection(uint tournamentSize):
    Selection(new FitnessScore()), tournamentSize_(tournamentSize)
{ }

uint TournamentSelection::selectIdx(
        const std::map<uint, Selection::Score> &scores) const
{
    //extract subvector with tournament size
    uint index = std::rand() % (scores.size() - tournamentSize_);
    uint best = index;
    for(uint i = index; i < tournamentSize_ + index; i++) {
        //the better individual, the lower standardize score (score/highestScore)
        if(scores.at(i).normalized < scores.at(best).normalized)
            best = i;
    }

    return best;
}

void TournamentSelection::normalize(std::map<uint, Selection::Score> &scores,
                                    uint worstScore)
{
    for(auto& score : scores) {
        score.second.normalized = static_cast<double>(score.second.value) / worstScore;
    }
}

}
