#include "object.h"

#include <limits>

namespace mep {

const uint Object::MAX_SCORE = std::numeric_limits<uint>::max();

Object::Object(uint id): id_(id), score_(MAX_SCORE)
{
}

Object::Object(const Object& other): id_(other.id_), score_(MAX_SCORE)
{
}

Object& Object::operator=(const Object& rhs) {
    id_ = rhs.id_;
    score_ = rhs.score_;
    return *this;
}

uint Object::score() const
{
    return score_;
}

uint Object::id() const
{
    return id_;
}

void Object::assess()
{
    score_ = assessObject();
}

std::string Object::write() const
{
    std::string objectStr = "Id: " + std::to_string(id_) +
                           " Score: " + std::to_string(score_) + ", ";
    writeObject(objectStr);
    return objectStr;
}


} // namespace mep
