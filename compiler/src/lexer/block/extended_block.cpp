#include "extended_block.h"

void compiler::extended_block::add_token(const std::string& token_)
{
    _tokens.push_back(token_);
}
