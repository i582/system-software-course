#pragma once
#include "../lexer/lexer.h"

namespace compiler
{
    class syntaxer
    {
    private:
        lexer* _lex;

    public:
        explicit syntaxer(const string& file_path_);
        ~syntaxer();


    public:
        void parse();

    };
}