#ifndef TOURNAMENTSELECTION_H
#define TOURNAMENTSELECTION_H

#include "selection.h"

namespace mep {

class TournamentSelection: public Selection
{
public:
    TournamentSelection(uint tournamentSize);
private /* methods */:
    uint selectIdx(const std::map<uint, Score>& scores) const override;
    void normalize(std::map<uint, Score>& scores, uint worstScore) override;

private:
    uint tournamentSize_;
};

}

#endif // TOURNAMENTSELECTION_H
