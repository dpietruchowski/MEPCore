#include "selection.h"

#include "core/object.h"
#include "utils/log.h"

#include <assert.h>
#include <iostream>

namespace mep {

Selection::Selection(Selection::ScoreType *scoreType):
    scoreType_(scoreType), scores_(), worstScore_(0), calculated_(false)
{

}

void Selection::add(uint idx, uint score, uint rank)
{
    auto success = scores_.emplace(idx, scoreType_->add(score, rank));
    assert(success.second);
    const Score& sc = success.first->second;
    if(sc.value > worstScore_)
        worstScore_ = sc.value;
    calculated_ = false;
}

uint Selection::select()
{
    if(!calculated_) {
        PopulationLog(DEBUG) << "Normalize scores";
        normalize(scores_, worstScore_);
        calculated_ = true;
    }
    uint idx = selectIdx(scores_);
    PopulationLog(DEBUG) << "Selected index: " << idx;
    return idx;
}

Selection::Score Selection::FitnessScore::add(uint score, uint /* rank */) const
{
    return {score, 0.0};
}

Selection::Score Selection::RankScore::add(uint /* score */, uint rank) const
{
    return {rank, 0.0};
}

}
