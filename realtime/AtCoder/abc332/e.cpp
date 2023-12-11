/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}



int d;
ld res = INF64;
// Function to print a partition
void printPartition(const std::vector<std::vector<int>>& ans)
{
    if(ans.size() != d) return;
    ld e2 = 0, e = 0;
    ITR(part, ans) {
        i64 s = lib::sum(part);
        e2 += 1.0L * s * s;
        e += s;
    }
    e2 /= d;
    e /= d;
    chmin(res, e2 - e * e);
}

// Function to generate all partitions
void Partition(const std::vector<int>& set, int index,
               std::vector<std::vector<int>>& ans)
{

    // If we have considered all elements
    // in the set print the partition
    if(index == set.size()) {
        printPartition(ans);
        return;
    }

    // For each subset in the partition
    // add the current element to it
    // and recall
    for (int i = 0; i < ans.size(); i++) {
        ans[i].push_back(set[index]);
        Partition(set, index + 1, ans);
        ans[i].pop_back();
    }

    // Add the current element as a
    // singleton subset and recall
    ans.push_back({ set[index] });
    Partition(set, index + 1, ans);
    ans.pop_back();
}

// Function to generate all
// partitions for a given set
void allPartitions(std::vector<int> set)
{
    std::vector<std::vector<int> > v;
    Partition(set, 0, v);
}

// Main function
void solve()
{

    // The size of the set
    int n; input >> n >> d;
    std::vector<int> w(n); input >> w;
    // Generate all partitions of the set
    allPartitions(w);
    // return 0;

    print(res);
}
