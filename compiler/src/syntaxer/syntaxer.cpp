#include "syntaxer.h"

compiler::syntaxer::syntaxer(const std::string& file_path_)
{
    this->_lex = new lexer(file_path_);
}

compiler::syntaxer::~syntaxer()
{
    delete _lex;
}

void compiler::syntaxer::parse()
{

}
