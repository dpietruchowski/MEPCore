#ifndef MEP_CORE_OBJECT_H
#define MEP_CORE_OBJECT_H

#include "utils/types.h"
#include "utils/color.h"
#include "genetic/fitness.h"

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
    void setColor(const Color& color);
    std::string write() const;
    std::string writeShort() const;
    friend std::ostream& operator<<(std::ostream& os, const Object& obj);

protected:
    Color color_;
    void setScore(uint score);
    virtual void writeObject(std::string &objectStr) const = 0;
    virtual void writeShortObject(std::string &objectStr) const = 0;

private:
    uint id_;
    uint score_;
};

} // namespace mep

#endif // MEP_CORE_OBJECT_H
