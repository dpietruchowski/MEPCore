#include "object.h"

#include <limits>
#include <iostream>

namespace mep {

const uint Object::MAX_SCORE = std::numeric_limits<uint>::max();

Object::Object(uint id): color_(Color::DEFAULT), id_(id), score_(MAX_SCORE)
{
}

Object::Object(const Object& other):
    color_(other.color_), id_(other.id_), score_(other.score_)
{
}

uint Object::score() const
{
    return score_;
}

uint Object::id() const
{
    return id_;
}

void Object::setColor(Color::Code color)
{
    color_ = color;
}

void Object::setColor(const Color& color)
{
    color_ = color;
}

std::string Object::write() const
{
    std::string objectStr = "Id: " + std::to_string(id_) +
                           " Score: " + std::to_string(score_) + ", ";
    writeObject(objectStr);
    objectStr = color_ + objectStr;
    return objectStr;
}

std::string Object::writeShort() const
{
    std::string objectStr = std::to_string(id_);
    objectStr.resize(3, ' ');
    writeShortObject(objectStr);
    return objectStr;
}

void Object::setScore(uint score)
{
    score_ = score;
}

std::ostream &operator<<(std::ostream &os, const Object &obj)
{
    return os << obj.color_ << obj.writeShort() << "\033[0m";
}


} // namespace mep
