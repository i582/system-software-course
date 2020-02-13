#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "block/block.h"

namespace compiler
{
    using std::cout;
    using std::string;
    using std::vector;

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


    class lexer
    {
    private:
        string _code;
        vector<string> _tokens;

        vector<block*> _blocks;

    public:
        explicit lexer(const string& file_path_);
        ~lexer();

    public:
        void parse();

        void open(const string& file_path_);
        void split();

        void join_in_tokens();


        static token_type what_token_type(const string& token_);

        // split by blocks
        void split_by_blocks();


    private:
        void skip_excess_symbols(int& index_);

        static bool is_split_symbol(const char& symbol_);
        static bool is_token_symbol(const char& symbol_);
        static bool next_token_is_part_of_token(const char& token_, const char& symbol_);

        static bool is_string_token(const string& token_);
        static bool is_symbol_token(const string& token_);

    public:
        void print_tokens();
    };

}