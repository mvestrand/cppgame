#ifndef SOBA_REPL_HPP
#define SOBA_REPL_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace soba {

    /** A shell for running custom commands in an app. */
    class Repl {
    public:

        /** Base class to use for commands that can be registered with the `Repl` */
        class Command {
        public:
            virtual ~Command() {}
            /** The command's name. This can be different from the name
             * registered with the command line.
             */
            virtual std::string name() const = 0;
            /** A brief description of the command. */
            virtual std::string brief() const = 0;
            /** Run this command with the given arguments.
             * 
             * @param repl This is the `Repl` from which this command is being 
             * called. This can be used to modify the state of the Repl or the
             * Game it is connected to.
             * @param args A vector of argument strings. `args[0]` is the name
             * the command was called with (when using the default arg parser).
             */
            virtual int invoke(Repl &repl, std::vector<std::string> &args) = 0;
            /** Parse the arguments of a command string.
             * This DOESN'T include parsing the name the command was called
             * with. The command name is instead added to the front of args
             * by `Repl` automatically after calling this.
             * 
             * @param repl The `Repl` the command is running in.
             * @param cmd_name The name used to call this command.
             * @param args_string A string of arguments given with the command 
             * (doesn't include the command name).
             * @param args The vector to write parsed arguments into.
             */
            virtual void parse_args(Repl const &repl, std::string const &cmd_name, std::string const &args_string, std::vector<std::string> &args) const;
        };
    
        using CommandMap = std::map<std::string,std::shared_ptr<Command>>;

    private:
        CommandMap commands;

        /** Get the command name from command string.
         * The name is the first word of a command string, used for lookup in
         * the command map.
         * 
         * @param cmd_string The command string to parse.
         * @param name The string to write the name into.
         * @returns `true` if `name` was written to. `false` if `name` is 
         * unchanged because a string of only whitespace was given.
         * @see Repl::Command::parse_args()
         */
        bool parse_command_name(std::string const &cmd_string, std::string &name, std::string &arg_str) const;

    public:
        Repl();
        ~Repl();

        /** Processes input from stdin without blocking.
         * Starts an async read of at least a full line of input from stdin and 
         * attempts to run that input as a command.
         *
         * @return `true` if a line was read, `false` otherwise.
         */
        bool process_stdin();

        /** Add a new name link to a command.
         * This can be used to add entirely new commands, alias existing 
         * commands, or shadow them with a new definition.
         * 
         * @param name The name to register the command under.
         * @param command An instance of a class inheriting from `Repl::Command`.
         * @param shadow Allow this declaration to shadow existing commands with
         * the same name. Defaults to `false`.
         */
        void add_command_name(std::string const &name, std::shared_ptr<Command> command, bool shadow=false);
        /** Remove a name link to a command.
         * 
         * @param name The command name to forget.
         * @param quiet Silently ignore removal of commands that don't exist. 
         * Defaults to `false`.
         */
        void remove_command_name(std::string const &name, bool quiet=false);
        /** Parse and run a command string.
         * 
         * @param command_string A command and arguments to run
         * @returns The exit code given by the command that was run.
         */
        int  run(std::string const &command_string);
        /** Parse a command string into arguments.
         * This is the default argument parser used by commands. It can be 
         * overridden on a per command basis by implementing `parse_args` on
         * a `Repl::Command`.
         * 
         * @param cmd_string The command string to parse.
         * @param args A `vector<string>` to write the arguments to.
         * @see Repl::Command::parse_args()
         */
        void parse_args(std::string const &cmd_string, std::vector<std::string> &args) const;

        /** Print text to the Repl.
         */
        void print(std::string const &msg); //< TODO: Convert these functions to be handles or streams that are written to instead.
        /** Print warning text to the Repl.
         */
        void print_warn(std::string const &msg);
        /** Print error text to the Repl.
         */
        void print_err(std::string const &msg);

        /** Iterate commands.
         */
        CommandMap::iterator begin();
        CommandMap::iterator end();
        /** Iterate commands.
         */
        CommandMap::const_iterator begin() const;
        CommandMap::const_iterator end() const;
    };
}



#endif //SODA_REPL_HPP