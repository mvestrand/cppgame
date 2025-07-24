#ifndef SOBA_LOG_HPP
#define SOBA_LOG_HPP

#include <iostream>

#define LOG(msg) \
    std::cout << "\x1b[2m"<< __FILE__ << "(" << __LINE__ << "): \x1b[0m\n\t" << msg << std::endl << std::flush

#define WARN(msg) \
    std::cerr << "\x1b[1;33mWarning: \x1b[2m"<< __FILE__ << "(" << __LINE__ << "): \x1b[0m\n\t" << msg << std::endl << std::flush

#define ERR(msg) \
    std::cerr << "\x1b[1;31mError: \x1b[2m"<< __FILE__ << "(" << __LINE__ << "): \x1b[0m\n\t" << msg << std::endl << std::flush

#endif //SOBA_LOG_HPP