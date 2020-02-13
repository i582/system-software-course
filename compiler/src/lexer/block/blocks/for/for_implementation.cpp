#include "for_implementation.h"

compiler::for_implementation::for_implementation(const std::string& start_point_, const std::string& condition_,
                                                 const std::string& action_)
{
    this->_start_point = start_point_;
    this->_condition = condition_;
    this->_action = action_;
}
