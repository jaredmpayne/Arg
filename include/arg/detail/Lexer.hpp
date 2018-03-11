#ifndef ARG_DETAIL_LEXER_HPP
#define ARG_DETAIL_LEXER_HPP

#include <string>
#include <vector>

#include <boost/optional.hpp>

#include "arg/detail/Token.hpp"

namespace arg {

    namespace detail {

        class Lexer {

        public:

            Lexer();

            std::vector<Token> lex(const std::vector<std::string> &args) const;

        private:

            std::vector<std::string> expand(const std::vector<std::string> &args) const;

            Token lex_argument(const std::string &arg) const;

            boost::optional<Token> lex_long_option(const std::string &arg) const;

            boost::optional<Token> lex_short_option(const std::string &arg) const;

            Token lex_positional_argument(const std::string &arg) const;
        };
    }
}

#endif
