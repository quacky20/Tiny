#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>

using namespace std;

extern vector<string> KEYWORDS;

enum class TokenType
{
    keyword,
    int_lit,
    semi
};

struct Token
{
    TokenType type;
    optional<string> value;
};

class Tokenizer
{
public:
    inline explicit Tokenizer(string src)
        : m_src(move(src))
    {
    }

    inline vector<Token> tokenize()
    {
        string buf;
        vector<Token> tokens;

        while(peek().has_value()){
            if (isalpha(peek().value())){
                buf.push_back(consume());
                while (peek().has_value() && isalnum(peek().value())){
                    buf.push_back(consume());
                }
                bool checked = false;
                for (const auto &key : KEYWORDS)
                {
                    if (buf == key)
                    {
                        tokens.push_back({.type = TokenType::keyword});
                        buf.clear();
                        checked = true;
                        continue;
                    }
                }
                if (!checked)
                {
                    cerr << "You messed up!" << endl;
                    exit(1);
                }
            }
            else if(isdigit(peek().value())) {
                buf.push_back(consume());
                while(peek().has_value() && isdigit(peek().value())){
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
                continue;
            }
            else if(peek().value() == ';'){
                tokens.push_back({.type = TokenType::semi});
                consume();
                continue;
            }
            else if(isspace(peek().value())){
                continue;
            }
            else{
                cerr << "You messed up!" << endl;
                exit(1);
            }

        }
        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] optional<char> peek(int count = 1) const {
        if (m_index + count >= m_src.length()) return {};
        else return m_src.at(m_index);
    }

    char consume(){
        return m_src.at(m_index++);
    }
    const string m_src;
    int m_index = 0;
};