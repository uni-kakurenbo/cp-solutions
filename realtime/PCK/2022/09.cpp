#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); ++i)
#define REPR(i, a, b) for(int i=(a); i<(b); ++i)

// <expr> = <term> [ '+' <term> ]*
// <term> = <factor> [ '*' <factor> ]*
// <factor> = <number> | <value> | '(' <expr> ')'
// <value> = <var> [ <var> ]*

long expr();

string s;
long a, b, c, d;

int len = 0;
int pos = 0;

long var() {
    if(s[pos] == 'a') return a;
    if(s[pos] == 'b') return b;
    if(s[pos] == 'c') return c;
    if(s[pos] == 'd') return d;
    assert(false);
}

long value() {
    long res = 0;
    while(pos < len and (bool)std::isalpha(s[pos])) {
        res *= 10;
        res += var();
        ++pos;
    }

    return res;
}

long number() {
    long res = 0;
    while(pos < len and (bool)std::isdigit(s[pos])) {
        res *= 10;
        res += s[pos] - '0';
        ++pos;
    }

    return res;
}

long factor() {
    if((bool)(std::isdigit(s[pos]))) return number();
    if((bool)(std::isalpha(s[pos]))) return value();

    ++pos;
    long res = expr();
    ++pos;

    return res;
}

long term() {
    long res = factor();

    while(pos < len and s[pos] == '*') {
        ++pos;
        res *= factor();
    }

    return res;
}

long expr() {
    long res = term();

    while(pos < len and (s[pos] == '+' or s[pos] == '-')) {
        char op = s[pos++];
        res += term() * (op == '+' ? 1 : -1);
    }

    return res;
}

long calc() {
    pos = 0;
    return expr();
}

int main() {
    cin >> s;
    len = s.size();
    long n; cin >> n;

    int last_a, last_b, last_c, last_d;

    int cnt = 0;
    for(a=0; a<10; ++a) {
        for(b=0; b<10; ++b) {
            for(c=0; c<10; ++c) {
                for(d=0; d<10; ++d) {
                    if(calc() == n) {
                        cnt++;
                        last_a = a;
                        last_b = b;
                        last_c = c;
                        last_d = d;
                    }
                }
            }
        }
    }

    std::cout << cnt << "\n";

    if(cnt == 1) {
        std::cout << last_a << last_b << last_c << last_d <<"\n";
    }
}
