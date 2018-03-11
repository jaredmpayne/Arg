#include "arg/detail/Lexer.hpp"

#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>

#include "arg/detail/Token.hpp"

using namespace std::placeholders;

arg::detail::Lexer::Lexer() { }

std::vector<arg::detail::Token> arg::detail::Lexer::lex(const std::vector<std::string> &args) const {
    std::vector<Token> tokens;
    std::vector<std::string> expanded = this->expand(args);
    auto lex_argument = std::bind(&Lexer::lex_argument, this, _1);
    std::transform(expanded.begin(), expanded.end(), std::back_inserter(tokens), lex_argument);
    return tokens;
}

std::vector<std::string> arg::detail::Lexer::expand(const std::vector<std::string> &args) const {
    std::vector<std::string> expanded;
    for (const std::string &arg : args) {
        std::vector<std::string> components;
        boost::split(components, arg, boost::is_any_of("="));
        std::move(components.begin(), components.end(), std::back_inserter(expanded));
    }
    return expanded;
}

arg::detail::Token arg::detail::Lexer::lex_argument(const std::string &arg) const {
    boost::optional<Token> result;
    if ((result = this->lex_long_option(arg))) {
        return result.value();
    }
    if ((result = this->lex_short_option(arg))) {
        return result.value();
    }
    return this->lex_positional_argument(arg);
}

boost::optional<arg::detail::Token> arg::detail::Lexer::lex_long_option(const std::string &arg) const {
    if (arg.size() > 2 && boost::starts_with(arg, "--")) {
        return Token(arg, Token::LexType::LongOption);
    }
    return boost::none;
}

boost::optional<arg::detail::Token> arg::detail::Lexer::lex_short_option(const std::string &arg) const {
    if (arg.size() > 1 && boost::starts_with(arg, "-")) {
        return Token(arg, Token::LexType::ShortOption);
    }
    return boost::none;
}

arg::detail::Token arg::detail::Lexer::lex_positional_argument(const std::string &arg) const {
    return Token(arg, Token::LexType::PositionalArgument);
}
