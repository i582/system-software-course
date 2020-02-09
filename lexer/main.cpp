#include "src/lexer.h"

int main()
{
    compiler::lexer lex("test.cpp");
    lex.parse();
    lex.print_tokens();

    return 0;
}
