#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace compiler
{
    using std::cout;
    using std::string;
    using std::vector;

    class lexer
    {
    private:
        string _code;
        vector<string> _tokens;

    public:
        explicit lexer(const string& file_path_);

    public:
        void parse();

        void open(const string& file_path_);
        void split();


    private:
        void skip_excess_symbols(int& index_);

        static bool is_split_symbol(const char& symbol_);
        static bool is_token_symbol(const char& symbol_);



    public:
        void print_tokens();
    };

}