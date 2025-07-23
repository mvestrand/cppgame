#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include <string>

typedef void (*console_input_callback_t)(std::string);
bool handle_console_input(console_input_callback_t callback);

#endif