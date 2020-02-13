#include "block.h"

void compiler::block::set_simple_block(compiler::simple_block* simple_block_)
{
    _simple_block = simple_block_;
    _block_type = block_type::SIMPLE;
}

void compiler::block::set_extended_block(compiler::extended_block* extended_block_)
{
    _extended_block = extended_block_;
    _block_type = block_type::EXTENDED;
}

compiler::block::~block()
{
    delete _extended_block;
    delete _simple_block;
}
