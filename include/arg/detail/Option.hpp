#ifndef ARG_DETAIL_OPTION_HPP
#define ARG_DETAIL_OPTION_HPP

#include <cstddef>
#include <string>
#include <vector>

namespace arg {

    namespace detail {

        class Option {

        public:

            Option(const std::vector<std::string> &names, size_t max_value_count);

            const std::vector<std::string> &names() const;

            size_t max_value_count() const;

            bool is_raised() const;

            void set_is_raised(bool is_raised);

            const std::vector<std::string> &values() const;

            bool add_value(const std::string &value);

        private:

            std::vector<std::string> _names;

            size_t _max_value_count;

            bool _is_raised;

            std::vector<std::string> _values;
        };
    }
}

#endif
