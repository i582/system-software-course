#pragma once
#include "../../extended_block.h"

namespace compiler
{


    class for_implementation : public extended_block
    {
    private:
        string _start_point;
        string _condition;
        string _action;

    public:
        for_implementation(const string& start_point_, const string& condition_, const string& action_);

    private:

    };

}