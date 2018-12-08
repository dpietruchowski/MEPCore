#include "terminal.h"

namespace mep {

Terminal::Terminal(const std::any& terminal,const std::string& name):
    Operation(name, 0), terminal_(terminal)
{ }

std::any Terminal::runOperation(const Args<std::any>& /* args */) const {
    return terminal_;
}
/*
std::any Terminal::runOperation(const RefArgs<std::any>&) const {
    return terminal_;
}
*/
void Terminal::write(std::string &objectStr) const {
    objectStr += "Terminal";
}

}