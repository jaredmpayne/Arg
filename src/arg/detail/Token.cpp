#include "arg/detail/Token.hpp"

#include <string>

arg::detail::Token::Token(const std::string &value, LexType lex_type) :
_value(value), _lex_type(lex_type) { }

bool arg::detail::Token::operator==(const Token &other) const {
    return this->lex_type() == other.lex_type() && this->value() == other.value();
}

const std::string &arg::detail::Token::value() const {
    return _value;
}

arg::detail::Token::LexType arg::detail::Token::lex_type() const {
    return _lex_type;
}
