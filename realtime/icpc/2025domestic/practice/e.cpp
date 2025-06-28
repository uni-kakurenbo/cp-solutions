/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    // int $ = 0;
    // while(true) {
        // debug_("Case: #" + std::to_string($++));
        solve();
    // }
    return 0;
}

vector<string> tokens;
vector<string> variables;

struct Tree {
    string value;
    Tree *left = nullptr, *right = nullptr;

    Tree(string value) : value(value) {}

    auto is_value() { return this->left == nullptr; }
    auto to_value() { return std::stoi(this->value); }
};

void parse(Tree*& node, i32& p) {
    auto token = tokens[p++];

    if(token == "if") {
        variables.push_back(tokens[p]);

        node = new Tree{ tokens[p++] };
        if(tokens[p++] != "then") assert(false);
        parse(node->left, p);
        if(tokens[p++] != "else") assert(false);
        parse(node->right, p);
    }
    else {
        node = new Tree { token };
    }
}

void tokenize(string S) {
    tokens.clear();

    string cur;
    ITR(x, S) {
        if(x == '_') {
            tokens.push_back(cur);
            cur.clear();
        }
        else cur += x;
    }

    tokens.push_back(cur);
}

#include "numeric/modular/modint.hpp"

using mint = uni::modint998244353;

#include "template/warnings.hpp"
void solve() {
    string s; input >> s;
    tokenize(s);

    i32 p = 0;
    Tree* tree;
    parse(tree, p);

    variables.sort().unique();
    auto m = variables.ssize();
    debug(m);

    i32 indent = 0;

    unordered_map<string, i32> counter;

    auto dfs = [&](auto&& self, Tree* node) -> mint {
        debug(std::string(indent, '-') + node->value, counter);

        if(node->is_value()) {
            debug(node->to_value(), counter);
            auto ratio = MINT<2>.pow(m - counter.ssize());
            return node->to_value() * ratio;
        }

        indent += 2;

        mint res = 0;


        if(!counter.contains(node->value) || counter[node->value] < 0) {
            counter[node->value] -= 1;
            res += self(self, node->left);
            counter[node->value] += 1;

            if(counter[node->value] == 0) counter.erase(node->value);
        }

        if(!counter.contains(node->value) || counter[node->value] > 0) {
            counter[node->value] += 1;
            res += self(self, node->right);
            counter[node->value] -= 1;

            if(counter[node->value] == 0) counter.erase(node->value);
        }

        indent -= 2;

        return res;
    };

    print(dfs(dfs, tree));
}
