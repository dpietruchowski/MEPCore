#ifndef MEPOBJECT_H
#define MEPOBJECT_H

#include "types.h"
#include "color.h"

#include <string>
#include <iostream>

namespace mep {

class Object
{
public:
    static const uint MAX_SCORE;
    Object(uint id);
    Object(const Object& other);
    Object& operator=(const Object& rhs) = default;
    virtual ~Object() {}
    uint score() const;
    uint id() const;
    void setColor(Color::Code color);
    void assess(/* const Fitness& fitness */);
    std::string write() const;
    std::string writeShort() const;
    friend std::ostream& operator<<(std::ostream& os, const Object& obj);

protected:
    virtual void writeObject(std::string &objectStr) const = 0;
    virtual void writeShortObject(std::string &objectStr) const = 0;
private /* methods */:
    virtual uint assessObject(/* const Fitness& fitness */) const = 0;

private:
    uint id_;
    uint score_;
    Color color_;
};

} // namespace mep

#endif // MEPOBJECT_H
