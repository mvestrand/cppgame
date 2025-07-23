#include "console_input.h"

#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

static string stdin_getline() {    
    string line;
    cout << "> " << flush;
    getline(cin, line);
    return line;
}


bool handle_console_input(console_input_callback_t callback) {
    static future<string> future_input;
    if (!future_input.valid()) {
        future_input = async(stdin_getline);
    }
    if (future_input.wait_for(0ms) == future_status::ready) {
        callback(future_input.get());
        return true;
    }
    return false;
}

