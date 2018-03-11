#include "arg/detail/Option.hpp"

#include <cstddef>
#include <string>
#include <vector>

arg::detail::Option::Option(const std::vector<std::string> &names, size_t max_value_count = 0) :
_names(names), _max_value_count(max_value_count), _is_raised(false) { }

const std::vector<std::string> &arg::detail::Option::names() const {
    return _names;
}

size_t arg::detail::Option::max_value_count() const {
    return _max_value_count;
}

bool arg::detail::Option::is_raised() const {
    return _is_raised;
}

void arg::detail::Option::set_is_raised(bool is_raised) {
    _is_raised = is_raised;
}

const std::vector<std::string> &arg::detail::Option::values() const {
    return _values;
}

bool arg::detail::Option::add_value(const std::string &value) {
    if (this->values().size() >= this->max_value_count()) {
        return false;
    }
    _values.push_back(value);
    return true;
}
