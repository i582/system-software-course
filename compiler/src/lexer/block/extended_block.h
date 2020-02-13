#pragma once
#include "simple_block.h"

namespace compiler
{
    using std::vector;
    using std::string;

    class block;

    class extended_block
    {
    protected:
        vector<string> _tokens;

        vector<block*> _blocks;

    public:
        void add_token(const string& token_);
    };

}