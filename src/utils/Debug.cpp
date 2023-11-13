
#include "utils/Debug.hpp"

namespace zephyr {

    std::ostream &debug(const std::string &context) {
        return std::cout << "[DEBUG <" << context << ">] ";
    }

}
