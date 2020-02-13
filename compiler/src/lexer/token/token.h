#pragma once
#include <string>

namespace compiler
{
    enum class token_type
    {
        NONTERMINAL,

        LET,
        CONST,

        NUMBER,
        STRING,
        BOOLEAN,
        VOID,

        FOR,
        WHILE,
        IF,
        ELSE,


        LBRA, // {
        RBRA, // }
        LPAR, // (
        RPAR, // )
    };

    using std::string;

    class token
    {
    private:
        string _lexem;
        token_type _type;

    public:
        explicit token(const string& lexem_);

    public:
        token_type type();
        string lexem();

    private:
        static token_type which_token_type(const string& token_);
    };
}