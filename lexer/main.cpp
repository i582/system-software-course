#include <chrono>
#include "src/lexer.h"

int main()
{
    compiler::lexer lex("test.cpp");

    auto begin = std::chrono::steady_clock::now();

    lex.parse();

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " mrs\n";

    

    lex.print_tokens();

    return 0;
}
