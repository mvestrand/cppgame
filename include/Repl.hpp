#ifndef SOBA_REPL_HPP
#define SOBA_REPL_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace soba {

    class Game;


    class Repl {
    public:

        class Command {
        public:
            virtual ~Command() {}
            virtual std::string name() const = 0;
            virtual std::string brief() const = 0;
            virtual int invoke(Repl &repl, std::vector<std::string> &args) = 0;
            virtual void parse_args(Repl const &repl, std::string const &cmd_string, std::vector<std::string> &args) const;
        };
    
        using CommandMap = std::map<std::string,std::shared_ptr<Command>>;

    private:
        CommandMap commands;
    public:
        Repl();
        ~Repl();

        bool readline_async();

        void add_command(std::string const &name, std::shared_ptr<Command> command);
        void free_command(std::string const &name);
        int run(std::string const &command_string);
        bool parse_command_name(std::string const &cmd_string, std::string &name) const;
        void parse_args(std::string const &cmd_string, std::vector<std::string> &args) const;

        void print(std::string const &msg);
        void print_warn(std::string const &msg);
        void print_err(std::string const &msg);


        CommandMap::iterator begin();
        CommandMap::iterator end();
        CommandMap::const_iterator begin() const;
        CommandMap::const_iterator end() const;
    };
}



#endif //SODA_REPL_HPP