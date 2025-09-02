#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

#include "./tokenization.hpp"

using namespace std;

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

    Tokenizer tokenizer(move(contents));

    vector<Token> tokens = tokenizer.tokenize();
    cout << contents << endl;
    for (const auto& token : tokens){
        cout << token << endl;
    }
    return 0;
}