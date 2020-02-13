#pragma once
#include <vector>
#include "variable.h"

namespace compiler
{
    using std::vector;

    class variable_declaration
    {
        vector<string> _tokens;
    };

}