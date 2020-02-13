#pragma once
#include <string>
#include <variant>

namespace compiler
{
    using variable_value = std::variant<int, double, std::string, bool>;

    enum class variable_type
    {
        INTEGER,
        DOUBLE,
        STRING,
        BOOLEAN,
        VOID
    };

    using std::string;
    using variable_name = std::string;

    class variable
    {
    public:
        variable_name _name;
        variable_type _type;
        variable_value _value;

    public:
        variable(const variable_name& name_, variable_type type_, const variable_value& value_);
    };

}
