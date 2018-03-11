#include "arg/Parser.hpp"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "arg/detail/Lexer.hpp"
#include "arg/detail/Option.hpp"
#include "arg/detail/Token.hpp"

arg::Parser::Parser() { }

void arg::Parser::add_option(const std::vector<std::string> &names, size_t max_value_count) {
    auto option = std::make_shared<detail::Option>(names, max_value_count);
    for (const std::string &name : option->names()) {
        _option_map[name] = option;
    }
}

const std::string &arg::Parser::executable_argument() const {
    return _executable_argument;
}

const std::vector<std::string> &arg::Parser::unrecognized_arguments() const {
    return _unrecognized_arguments;
}

bool arg::Parser::has_raised_option(const std::string &name) const {
    try {
        return _option_map.at(name)->is_raised();
    }
    catch (const std::out_of_range &exception) {
        return false;
    }
}

const std::vector<std::string> &arg::Parser::option_values(const std::string &name) const {
    return _option_map.at(name)->values();
}

void arg::Parser::parse(const std::vector<std::string> &args) {
    if (args.empty()) {
        return;
    }
    _executable_argument = args.front();
    std::vector<std::string> tail(args.begin() + 1, args.end());
    std::vector<detail::Token> tokens = detail::Lexer().lex(tail);
    for (const detail::Token &token : tokens) {
        this->parse(token);
    }
}

void arg::Parser::parse(const detail::Token &token) {
    switch (token.lex_type()) {
        case detail::Token::LexType::LongOption:
            this->parse_long_option(token);
            break;
        case detail::Token::LexType::ShortOption:
            this->parse_short_option(token);
            break;
        case detail::Token::LexType::PositionalArgument:
            this->parse_positional_argument(token);
            break;
    }
}

void arg::Parser::parse_long_option(const detail::Token &token) {
    std::string name = token.value().substr(2);
    this->raise_option(name);
}

void arg::Parser::parse_short_option(const detail::Token &token) {
    std::string names = token.value().substr(1);
    for (char character : names) {
        std::string name(1, character);
        this->raise_option(name);
    }
}

void arg::Parser::parse_positional_argument(const detail::Token &token) {
    if (!_last_raised_option || !_last_raised_option->add_value(token.value())) {
        _unrecognized_arguments.push_back(token.value());
    }
}

void arg::Parser::raise_option(const std::string &name) {
    try {
        auto option = _option_map.at(name);
        _last_raised_option = option;
        option->set_is_raised(true);
    }
    catch (const std::out_of_range &exception) {
        _unrecognized_arguments.push_back(name.size() > 1 ? "--" + name : "-" + name);
    }
}
