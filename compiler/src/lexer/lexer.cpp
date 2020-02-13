#include "lexer.h"

compiler::lexer::lexer(const std::string& file_path_)
{
    open(file_path_);
}

void compiler::lexer::parse()
{
    split();
    join_in_tokens();
    split_by_blocks();
}

void compiler::lexer::open(const string& file_path_)
{
    std::ifstream in(file_path_, std::ios::binary);

    if (!in.is_open())
    {
        throw std::logic_error("File not found!");
    }

    int size = in.seekg( 0, std::ios::end).tellg();
    in.seekg(0);

    _code.resize(size);
    in.read(&_code[0], size);
}

void compiler::lexer::split()
{
    string temp_token;

    for (int i = 0; i < _code.size(); ++i)
    {
        skip_excess_symbols(i);

        auto& symbol = _code[i];


        if (is_split_symbol(symbol))
        {
            if (!temp_token.empty())
            {
                _tokens.push_back(temp_token);
                temp_token.clear();
            }

            if (is_token_symbol(symbol))
            {
                if (i + 1 < _code.size() && next_token_is_part_of_token(symbol, _code[i + 1]))
                {
                    auto next_symbol = _code[i + 1];

                    string symbol_token(1, symbol);
                    symbol_token += next_symbol;
                    _tokens.push_back(symbol_token);
                    ++i;
                }
                else
                {
                    const string symbol_token(1, symbol);
                    _tokens.push_back(symbol_token);
                }
            }


            continue;
        }

        temp_token += symbol;
    }

    if (!temp_token.empty())
    {
        _tokens.push_back(temp_token);
        temp_token.clear();
    }
}

void compiler::lexer::join_in_tokens()
{
    auto temp_tokens = std::move(_tokens);
    _tokens.clear();

    string temp_token;
    for (int i = 0; i < temp_tokens.size(); ++i)
    {
        auto& token = temp_tokens[i];

        if (is_string_token(token))
        {
            temp_token += token;
            ++i;
            token = temp_tokens[i];

            while (i < temp_tokens.size() && !is_string_token(token))
            {
                temp_token += token;

                ++i;
                token = temp_tokens[i];
            }
            temp_token += token;

            if (!temp_token.empty())
            {
                _tokens.push_back(temp_token);
                temp_token.clear();
            }
            continue;
        }

        if (is_symbol_token(token))
        {
            temp_token += token;
            ++i;
            token = temp_tokens[i];

            while (i < temp_tokens.size() && !is_symbol_token(token))
            {
                temp_token += token;

                ++i;
                token = temp_tokens[i];
            }
            temp_token += token;

            if (!temp_token.empty())
            {
                _tokens.push_back(temp_token);
                temp_token.clear();
            }
            continue;
        }


        _tokens.push_back(token);
    }
}

void compiler::lexer::skip_excess_symbols(int& index_)
{
    const char current_symbol = _code[index_];

    if (current_symbol == '\n' || current_symbol == '\r')
    {
        _code[index_] = ' ';
    }


    if (current_symbol == ' ')
    {
        if (index_ + 1 < _code.size() && _code[index_ + 1] == ' ')
        {
            ++index_;
        }
    }
}

bool compiler::lexer::is_split_symbol(const char& symbol_)
{
    return  symbol_ == ' ' || symbol_ == ':' ||
            symbol_ == ';' || symbol_ == '{' ||
            symbol_ == '}' || symbol_ == '(' ||
            symbol_ == ')' || symbol_ == ',' ||
            symbol_ == '[' || symbol_ == ']' ||
            symbol_ == '*' || symbol_ == '&' ||
            symbol_ == '+' || symbol_ == '-' ||
            symbol_ == '/' || symbol_ == '%' ||
            symbol_ == '=' || symbol_ == '!' ||
            symbol_ == '^' || symbol_ == '#' ||
            symbol_ == '\''|| symbol_ == '"' ||
            symbol_ == '<' || symbol_ == '>' ||
            symbol_ == '.' || symbol_ == '?' ||
            symbol_ == '|' || symbol_ == '\\';
}

bool compiler::lexer::is_token_symbol(const char& symbol_)
{
    return symbol_ != ' ' && symbol_ != '\0';
}

void compiler::lexer::print_tokens()
{
    for (const auto& token : _tokens)
    {
        cout << "" << token << "\n";
    }
}

bool compiler::lexer::next_token_is_part_of_token(const char& token_, const char& symbol_)
{
    switch (token_)
    {
        case '=':
        {
            return symbol_ == '=';
        }

        case '!':
        {
            return symbol_ == '=';
        }

        case '<':
        {
            return symbol_ == '=' || symbol_ == '<';
        }

        case '>':
        {
            return symbol_ == '=' || symbol_ == '>';
        }

        case '-':
        {
            return symbol_ == '>' || symbol_ == '-'  || symbol_ == '=';
        }

        case '+':
        {
            return symbol_ == '+' || symbol_ == '=';
        }

        case '*':
        {
            return symbol_ == '=';
        }

        case '/':
        {
            return symbol_ == '=' || symbol_ == '*' || symbol_ == '/';
        }

        case '%':
        {
            return symbol_ == '=';
        }

        case ':':
        {
            return symbol_ == ':';
        }

        case '|':
        {
            return symbol_ == '|' || symbol_ == '=';
        }

        case '&':
        {
            return symbol_ == '&' || symbol_ == '=';
        }

        case '^':
        {
            return symbol_ == '=';
        }

        case '\\':
        {
            return true;
        }

        default:
            return false;
    }
}

bool compiler::lexer::is_string_token(const string& token_)
{
    return token_ == "\"";
}

bool compiler::lexer::is_symbol_token(const string& token_)
{
    return token_ == "'";
}

void compiler::lexer::split_by_blocks()
{
    auto temp_block = new block();

    auto temp_extended_block = new extended_block();
    auto temp_simple_block = new simple_block();

    for (int i = 0; i < _tokens.size(); ++i)
    {
        auto& token = _tokens[i];

        const token_type current_token_type = what_token_type(token);

        switch (current_token_type)
        {
            case token_type::FOR:
            case token_type::WHILE:
            {
                temp_block->set_extended_block(temp_extended_block);

                while (i < _tokens.size() - 1 && what_token_type(token) != token_type::RBRA)
                {
                    temp_extended_block->add_token(token);

                    ++i;
                    token = _tokens[i];
                }

                _blocks.push_back(temp_block);
                break;
            }
            case token_type::NONTERMINAL:
            {

                break;
            }
            case token_type::LET:
            {

                break;
            }
            case token_type::CONST:
            {

                break;
            }
            case token_type::NUMBER:
            {

                break;
            }
            case token_type::STRING:
            {

                break;
            }
            case token_type::BOOLEAN:
            {

                break;
            }
            case token_type::VOID:
            {

                break;
            }
            case token_type::IF:
            {

                break;
            }
            case token_type::ELSE:
            {

                break;
            }

            default: break;
        }
    }
}

compiler::lexer::~lexer()
{
    _blocks.clear();
}

compiler::token_type compiler::lexer::what_token_type(const std::string& token_)
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
    else
    {
        return token_type::NONTERMINAL;
    }
}
