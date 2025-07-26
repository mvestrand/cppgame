#include "repl_commands.hpp"

#include <format>

#include "Game.hpp"

using namespace std;

namespace soba {
    using GameInst = shared_ptr<Game>;

    string ReplHelp::name() const { return "help"; }
    string ReplHelp::brief() const { return "Print help info about a command."; }
    void ReplHelp::print_usage(Repl &repl, string const &name) const {
        // // repl.out << this->name() << "\n"
        // repl.out << format(
        //     "{0}\n"
        //     "\t{1} <command>"
        // ) << endl;
        // repl.print(this->name() + "\n"
        //     "Usage: \n" +
        //     name + " [COMMAND]\n"
        //     "\tPrint out help info about COMMAND.\n"
        //     "\n" + name + " .\n"
        //     "\tList all commands.");
    }
    void ReplHelp::list_commands(Repl &repl) const {
    }
    int ReplHelp::invoke(Repl &repl, vector<string> &args) {
        repl.print("Usage: "+args[0]+ " [COMMAND]\n"
            "Prints out help info about a command.\n"
        );
        return 0;
    }

    string ReplQuitGame::name() const  { return "quit"; }
    string ReplQuitGame::brief() const  { return "Signal the attached game to quit."; }
    int ReplQuitGame::invoke(Repl &repl, vector<string> &args)  {
        GameInst game; 
        if (!repl.get_game(game)) {
            repl.print_err("Call to quit failed: No game instance is attached to this Repl.");
        } else {
            game->should_quit = true;
        }
        return 0;
    }

}
