#ifndef SOBA_REPL_COMMANDS_HPP
#define SOBA_REPL_COMMANDS_HPP

#include "Repl.hpp"

namespace soba {
    class ReplHelp final : public Repl::Command {
    public:
        std::string name() const override;
        std::string brief() const override;
        void print_usage(Repl &repl, std::string const &name) const;
        void list_commands(Repl &repl) const;
        int invoke(Repl &repl, std::vector<std::string> &args) override;
    };
    class ReplListAllCommands : public Repl::Command {

    };
    class ReplQuitGame final : public Repl::Command {
    public:
        std::string name() const override;
        std::string brief() const override;
        int invoke(Repl &repl, std::vector<std::string> &args) override;
    };
}

#endif