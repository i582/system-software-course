#include "token.h"

compiler::token::token(const string& lexem_)
{
    this->_lexem = lexem_;
    this->_type = which_token_type(lexem_);
}

compiler::token_type compiler::token::which_token_type(const std::string& token_)
{
    if (token_ == "let")
    {
        return token_type::LET;
    }
    else if (token_ == "const")
    {
        return token_type::CONST;
    }
    else if (token_ == "number")
    {
        return token_type::NUMBER;
    }
    else if (token_ == "string")
    {
        return token_type::STRING;
    }
    else if (token_ == "boolean")
    {
        return token_type::BOOLEAN;
    }
    else if (token_ == "void")
    {
        return token_type::VOID;
    }
    else if (token_ == "for")
    {
        return token_type::FOR;
    }
    else if (token_ == "while")
    {
        return token_type::WHILE;
    }
    else if (token_ == "if")
    {
        return token_type::IF;
    }
    else if (token_ == "else")
    {
        return token_type::ELSE;
    }
    else if (token_ == "{")
    {
        return token_type::LBRA;
    }
    else if (token_ == "}")
    {
        return token_type::RBRA;
    }
    else if (token_ == "(")
    {
        return token_type::LPAR;
    }
    else if (token_ == ")")
    {
        return token_type::RPAR;
    }
    else
    {
        return token_type::NONTERMINAL;
    }
}

compiler::token_type compiler::token::type()
{
    return _type;
}

std::string compiler::token::lexem()
{
    return _lexem;
}
