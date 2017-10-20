#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <iostream>

namespace mep {

class Color
{
public:
    enum Code {
        RED      = 31,
        GREEN    = 32,
        YELLOW   = 33,
        BLUE     = 34,
        MAGNETA  = 35,
        CYAN     = 36,
        DEFAULT  = 39,
    };

    Color(Code code);
    Color(const Color&) = default;
    Color& operator=(const Color&) = default;
    Color& operator=(Code code);
    friend std::ostream& operator<<(std::ostream& os, const Color& color);
    std::string operator+(const std::string &str) const;

private:
    Code code_;
};

}

#endif // COLOR_H
