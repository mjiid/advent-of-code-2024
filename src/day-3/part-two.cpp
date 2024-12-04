#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

enum TokenType {
    MUL,
    LEFT_PAR,
    RIGHT_PAR,
    NUMBER,
    COMMA,
    NONE,
    DO,
    DONT
};

struct Token {
    string value;
    TokenType type;
};

Token nextToken(const string& s, int& pos) {

    while (pos < s.size()) {
        if (s.substr(pos, 3) == "mul" && (pos + 3 == s.size() || !isalnum(s[pos + 3]))) {
            pos += 3;
            return {"mul", TokenType::MUL};
        }
        if (s.substr(pos, 2) == "do" && (pos + 2 == s.size() || !isalnum(s[pos + 2]))) {
            pos += 2;
            return {"do", TokenType::DO};
        }
        if (s.substr(pos, 5) == "don't" && (pos + 5 == s.size() || !isalnum(s[pos + 5]))) {
            pos += 5;
            return {"don't", TokenType::DONT};
        }
        if (s[pos] == '(') {
            pos++;
            return {"(", TokenType::LEFT_PAR};
        }
        if (s[pos] == ')') {
            pos++;
            return {")", TokenType::RIGHT_PAR};
        }
        if (s[pos] == ',') {
            pos++;
            return {",", TokenType::COMMA};
        }
        if (isdigit(s[pos])) {
            string number;
            while (pos < s.size() && isdigit(s[pos])) {
                number += s[pos];
                pos++;
            }
            return {number, TokenType::NUMBER};
        }
        pos++;
    }
    return {"", TokenType::NONE};
}

long long parse(const string& s, bool& enabled) {
    int pos = 0;
    long long res = 0;
    vector<Token> tokens;

    while (true) {
        Token token = nextToken(s, pos);
        if (token.type == TokenType::NONE) break;
        tokens.push_back(token);
    }

    for (int i = 0; i < tokens.size(); i++) {
        if (enabled) {
            const bool validMul = ((i  + 5 < tokens.size() &&
                tokens[i].type == TokenType::MUL &&
                tokens[i+1].type == TokenType::LEFT_PAR &&
                tokens[i+2].type == TokenType::NUMBER &&
                tokens[i+3].type == TokenType::COMMA &&
                tokens[i+4].type == TokenType::NUMBER &&
                tokens[i+5].type == TokenType::RIGHT_PAR));

            if (validMul) {
                const long long a = stoll(tokens[i + 2].value);
                const long long b = stoll(tokens[i + 4].value);
                res += (a * b);
                i += 5;
            } else if ((i + 2 < tokens.size() &&
                tokens[i].type == TokenType::DONT &&
                tokens[i+1].type == TokenType::LEFT_PAR &&
                tokens[i+2].type == TokenType::RIGHT_PAR)) {
                enabled = false;
                i += 2;
            }
        } else {
            const bool validDo = ((i + 2 < tokens.size() &&
                tokens[i].type == TokenType::DO &&
                tokens[i+1].type == TokenType::LEFT_PAR &&
                tokens[i+2].type == TokenType::RIGHT_PAR));

            if (validDo) {
                enabled = true;
                i += 2;
            }
        }
    }
    return res;
}

int main() {
    string s;
    long long res = 0;
    bool enabled = true;
    while (getline(cin, s)) {
        if (s.empty()) break;
        res += parse(s, enabled);
        cout << res << endl;
    }

    cout << res << endl;
    return 0;
}