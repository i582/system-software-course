#include "variable.h"

compiler::variable::variable(const std::string& name_, compiler::variable_type type_, const compiler::variable_value& value_)
{
    this->_name = name_;
    this->_type = type_;
    this->_value = value_;
}
