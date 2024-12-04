#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum Tokens {
    MUL,
    LEFT_PAR,
    RIGHT_PAR,
    NUMBER,
    COMMA,
    NONE
};

struct Token {
    string value;
    Tokens type;
};

Token nextToken(const string& s, size_t& pos) {
    while (pos < s.size()) {
        // Check for "mul"
        if (s.substr(pos, 3) == "mul" && (pos + 3 == s.size() || !isalnum(s[pos + 3]))) {
            pos += 3;
            return {"mul", Tokens::MUL};
        }
        // Parentheses
        if (s[pos] == '(') {
            pos++;
            return {"(", Tokens::LEFT_PAR};
        }
        if (s[pos] == ')') {
            pos++;
            return {")", Tokens::RIGHT_PAR};
        }

        // Comma
        if (s[pos] == ',') {
            pos++;
            return {",", Tokens::COMMA};
        }

        // Numbers
        if (isdigit(s[pos])) {
            string number;
            while (pos < s.size() && isdigit(s[pos])) {
                number += s[pos];
                pos++;
            }
            return {number, Tokens::NUMBER};
        }

        pos++;
    }

    return {"", Tokens::NONE};
}

long long parse(const string& s) {
    vector<Token> tokens;
    size_t pos = 0;

    while (true) {
        Token token = nextToken(s, pos);
        if (token.type == Tokens::NONE) break;
        tokens.push_back(token);
    }

    long long res = 0;
    for (size_t i = 0; i + 5 < tokens.size(); i++) {

        if ((tokens[i].type == Tokens::MUL &&
             tokens[i+1].type == Tokens::LEFT_PAR &&
             tokens[i+2].type == Tokens::NUMBER &&
             tokens[i+3].type == Tokens::COMMA &&
             tokens[i+4].type == Tokens::NUMBER &&
             tokens[i+5].type == Tokens::RIGHT_PAR)) {
            const long long a = stoll(tokens[i+2].value);
            const long long b = stoll(tokens[i+4].value);
            res +=  (a * b);
            i += 5;
        }
    }
    return res;
}

int main() {
    string s;
    long long result = 0;
    while (getline(cin, s)) {
        if (s.empty()) break;
        result += parse(s);
    }

    cout << result << endl;
    return 0;
}