#pragma once
#include "extended_block.h"

namespace compiler
{
    enum class block_type
    {
        SIMPLE,
        EXTENDED
    };


    class block
    {
    private:
        extended_block* _extended_block;
        simple_block* _simple_block;
        block_type _block_type;


    public:
        block() = default;
        ~block();

    public:
        void set_simple_block(simple_block* simple_block_);
        void set_extended_block(extended_block* extended_block_);
    };

}