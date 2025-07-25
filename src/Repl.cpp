#include "Repl.hpp"

#include <chrono>
#include <future>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <thread>

#include "log.hpp"

using namespace std;


static string stdin_getline() {    
    string line;
    cout << "> " << flush;
    getline(cin, line);
    return line;
}

namespace soba {
    using CommandMap = Repl::CommandMap;
    using Command = Repl::Command;
    
    // Use the Repl's argument parser by default
    void Command::parse_args(Repl const &repl, string const &cmd_str, std::string const &cmd_name, vector<string> &args) const {
        repl.parse_args(cmd_str, args);
    }

    Repl::Repl() {}
    Repl::~Repl() {}

    bool Repl::process_stdin() {
        static future<string> future_input;
        if (!future_input.valid()) {
            future_input = async(stdin_getline);
        }
        if (future_input.wait_for(0ms) == future_status::ready) {
            string line = future_input.get();
            run(line);
            return true;
        }
        return false;
    }

    void Repl::add_command_name(string const &name, shared_ptr<Command> command, bool shadow) {
        auto it = commands.find(name);
        if (it != commands.end() && !shadow) {
            print_warn("Overwriting command \"" + name + "\"");
        }
        commands[name] = command;
    }
    
    void Repl::remove_command_name(string const &name, bool quiet) {
        auto it = commands.find(name);
        if (it != commands.end()) {
            commands.erase(it);
        } else if (!quiet) {
            print_err("Failed to remove unknown command name \"" + name + "\"");
        }
    }

    int Repl::run(string const &cmd_str) {
        // Look up the command by name
        string cmd_name, arg_str;
        if (!parse_command_name(cmd_str, cmd_name, arg_str))
            return 0;     // <- Skip empty input
        auto cmd_it = commands.find(cmd_name);
        if (cmd_it == commands.end()) {
            print_err("Unknown command \""+cmd_name+"\"");
            return 0;
        }
        auto cmd = cmd_it->second;
        
        // Parse the arguments, then run the command
        vector<string> args;
        cmd->parse_args(*this, arg_str, cmd_name, args);
        args.insert(args.begin(), cmd_name);
        auto res = cmd->invoke(*this, args);
        return res;
    }

    bool Repl::parse_command_name(string const &cmd_str, string &name, string &arg_str) const {
        regex words_regex("[^\\s]+");
        smatch sm;
        if (regex_search(cmd_str, sm, words_regex)) {
            name = sm.str();
            arg_str = sm.suffix();
            return true;
        }
        return false;
    }


    void Repl::parse_args(string const &cmd_str, vector<string> &args) const {
        regex words_regex("[^\\s]+");
        auto words_begin = sregex_iterator(cmd_str.begin(), cmd_str.end(), words_regex);
        auto words_end = sregex_iterator();        
        for (sregex_iterator i = words_begin; i != words_end; i++) {
            smatch sm = *i;
            string match_str = sm.str();
            args.push_back(match_str);
        }
    }

    CommandMap::iterator Repl::begin() { return commands.begin(); }
    CommandMap::iterator Repl::end() { return commands.end(); }
    CommandMap::const_iterator Repl::begin() const { return commands.begin(); }
    CommandMap::const_iterator Repl::end() const { return commands.end(); }

    void Repl::print(string const &msg) {
        LOG(msg);
    }
    void Repl::print_warn(string const &msg) {
        WARN(msg);
    }
    void Repl::print_err(string const &msg) {
        ERR(msg);
    }
}

