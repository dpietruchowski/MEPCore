#ifndef MEP_GENETIC_SELECTION_H
#define MEP_GENETIC_SELECTION_H

#include <map>
#include <memory>

namespace mep {

class Selection
{
protected:
    struct Score {
        uint value;
        double normalized;
    };
    struct ScoreType {
        virtual Score add(uint score, uint rank) const = 0;
    };
    struct FitnessScore final: public ScoreType {
        Score add(uint score, uint rank) const override;
    };
    struct RankScore final: public ScoreType {
        Score add(uint score, uint rank) const override;
    };

public:
    Selection(ScoreType *scoreType);
    virtual ~Selection()
    { }

    void add(uint idx, uint score, uint rank);
    void reset();
    uint select();

private /* methods */:
    virtual uint selectIdx(const std::map<uint, Score>& scores) const = 0;
    virtual void normalize(std::map<uint, Score>& scores, uint worstScore) = 0;

private:
    std::unique_ptr<ScoreType> scoreType_;
    std::map<uint, Score> scores_;
    uint worstScore_;
    bool calculated_;
};

}

#endif // MEP_GENETIC_SELECTION_H
