// TODO: build libs as a separate CMake project and include it in the main build

#ifndef CODE_PARSER_HPP
#define CODE_PARSER_HPP

#include <string>
#include <list>

/**
 * @brief General command parsing container
 * Breaks down a single string of code into individual commands
 * and provides access and state to the command list
 * 
 * Each line of the input string is a separate command
 * 
 * Trims whitespace and comments from the commands (starting with //)
 * 
 * Iterates through the list of commands with NextCommand() and provides current command
 * with GetCurrentCommand()
 */
class CommandParser {
public:
    /**
     * @brief Setup the command parser and prepare the first command
     * 
     * @param code Block of code to break down into commands by line
     */
    void Initialize(std::string code);

    /**
     * @brief Checks if any commands are unparsed
     * 
     * @return true if there are more commands
     * @return false if the end of the command list has been reached
     */
    bool HasMoreCommands();

    /**
     * @brief Move the parser to the next command
     * 
     * Get that command with GetCurrentCommand()
     */
    void NextCommand();

    /**
     * @brief Get the current command from the parser
     * 
     * @return std::string current command string
     */
    std::string GetCurrentCommand();

protected:
    std::list<std::string> Commands;
    std::list<std::string>::iterator CommandsIterator;
};

#endif