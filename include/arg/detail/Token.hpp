#ifndef ARG_DETAIL_TOKEN_HPP
#define ARG_DETAIL_TOKEN_HPP

#include <string>

namespace arg {

    namespace detail {

        class Token {

        public:

            enum class LexType {
                LongOption,
                ShortOption,
                PositionalArgument
            };

            Token(const std::string &value, LexType lex_type);

            bool operator==(const Token &other) const;

            const std::string &value() const;

            LexType lex_type() const;

        private:

            std::string _value;

            LexType _lex_type;
        };
    }
}

#endif
