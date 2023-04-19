#include "Utils.h"

std::string Utils::getWorkingDirectory(const std::string &argvZero) {

    int i = argvZero.find_last_of('/');

    return argvZero.substr(0, i + 1);
}