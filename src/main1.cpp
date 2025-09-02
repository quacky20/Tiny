#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

#include "./tokenization.hpp"

using namespace std;

vector<string> KEYWORDS = {"says", "num", "dec", "letter","bye"};

enum class TokenType {
    keyword,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    optional<string> value;
};

string tokenTypeToString(TokenType t) {
    switch (t) {
        case TokenType::keyword: return "keyword";
        case TokenType::int_lit: return "int_lit";
        case TokenType::semi:    return "semi";
        default: return "unknown";
    }
}

ostream& operator<<(ostream& os, const Token& tok) {
    os << "{ type: " << tokenTypeToString(tok.type);
    if (tok.value.has_value()) {
        os << ", value: \"" << tok.value.value() << "\"";
    }
    os << " }";
    return os;
}

vector<Token> tokenize(string& str){
    string buf;
    vector<Token> tokens;
    for (int i = 0; i < str.length(); i++){
        char c = str.at(i);
        if (isalpha(c)){
            buf.push_back(c);
            i++;
            while(isalnum(str.at(i))){
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            bool checked = false;
            for (const auto& key : KEYWORDS){
                if (buf == key){
                    tokens.push_back({.type = TokenType::keyword});
                    buf.clear();
                    checked = true;
                    continue;
                }
            }
            if (!checked) {
                cerr << "You messed up!" << endl;
                exit(1);
            }
        }
        else if(isdigit(c)){
            buf.push_back(c);
            i++;
            while(isdigit(str.at(i))){
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf.clear();
        }
        else if(c == ';'){
            tokens.push_back({.type = TokenType::semi});
        }
        else if (isspace(c)) continue;
        else {
            cerr << "You messed up!" << endl;
            exit(1);
        }
    }
    return tokens;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Incorrect usage. Correct usage is..." << endl;
        cerr << "tiny <input.tiny>" << endl;
        return 1;
    }

    string contents;
    {
        fstream input(argv[1], ios::in);
        stringstream contents_stream;
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }
    vector<Token> tokens = tokenize(contents);
    cout << contents << endl;
    for (const auto& token : tokens){
        cout << token << endl;
    }
    return 0;
}