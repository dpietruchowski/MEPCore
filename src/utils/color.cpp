#include "color.h"
#include <iostream>

namespace mep {

Color::Color(Code code): code_(code)
{

}

Color &Color::operator=(Color::Code code)
{
    code_ = code;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Color &color)
{
    return os << "\033[" << color.code_ << "m";
}

std::string Color::operator+(const std::string &str) const
{
    std::string returned = "\033[";
    returned += std::to_string(code_);
    returned += "m";
    returned += str;
    returned += "\033[0m";

    return returned;
}

}
