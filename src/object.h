#ifndef MEPOBJECT_H
#define MEPOBJECT_H

#include "types.h"
#include <string>

namespace mep {

class Object
{
public:
    static const uint MAX_SCORE;
    Object(uint id);
    Object(const Object& other);
    Object& operator=(const Object& rhs);
    virtual ~Object() {}
    uint score() const;
    uint id() const;
    void assess(/* const Fitness& fitness */);
    std::string write() const;
protected:
    virtual void writeObject(std::string &objectStr) const = 0;
private /* methods */:
    virtual uint assessObject(/* const Fitness& fitness */) const = 0;

private:
    uint id_;
    uint score_;
};

} // namespace mep

#endif // MEPOBJECT_H
