#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "arg/detail/Option.hpp"
#include "arg/detail/Token.hpp"

namespace arg {

    class Parser {

    public:

        /// Creates a new parser.
        Parser();

        /// Adds an option to the parser.
        ///
        /// If an option name conflicts with the name of a previously added option, the name
        /// defaults to the last option added with thtat name.
        ///
        /// @param names The option names.
        /// @param max_value_count The maximum number of values that can be added to the option.
        void add_option(const std::vector<std::string> &names, size_t max_value_count = 0);

        /// The argument passed as the executable.
        ///
        /// @return The executable argument.
        const std::string &executable_argument() const;

        /// The arguments passed to the parser that were unrecognized.
        ///
        /// @return The unrecognized arguments.
        const std::vector<std::string> &unrecognized_arguments() const;

        /// Checks if the parser contains a raised option with the given name.
        ///
        /// @param name The option name.
        ///
        /// @return true if the parser has a raised option with the name, false otherwise.
        bool has_raised_option(const std::string &name) const;

        /// Returns the values of the option with the given name.
        ///
        /// @param name The option name.
        ///
        /// @return The option values.
        ///
        /// @throw std::out_of_range The option is not found.
        const std::vector<std::string> &option_values(const std::string &name) const;

        /// Parses the program arguments.
        ///
        /// @param args The arguments.
        void parse(const std::vector<std::string> &args);

    private:

        void parse(const detail::Token &token);

        void parse_long_option(const detail::Token &token);

        void parse_short_option(const detail::Token &token);

        void parse_positional_argument(const detail::Token &token);

        void raise_option(const std::string &name);

        void set_executable_argument(const std::string &executable_argument);

        std::string _executable_argument;

        std::vector<std::string> _unrecognized_arguments;

        std::unordered_map<std::string, std::shared_ptr<detail::Option>> _option_map;

        std::shared_ptr<detail::Option> _last_raised_option;
    };
}

#endif
