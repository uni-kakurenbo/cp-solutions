#include <bits/stdc++.h>
using namespace std;

// #include <atcoder/...>
// using namespace atcoder;

#ifdef LOCAL_JUDGE
    #include<debug>
    #define debug(...) Debug::debug(Debug::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
    #define DEBUG(...) do { Debug::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nullptr, "\033[m\n"); } while(0);
#else
    #define debug(...) { ; }
    #define DEBUG(...) { ; }
#endif

using ll = long long;
using ull = unsigned long long;

#define INF32 2147483647
#define INF64 9223372036854775807LL

#define until(...) while(!(__VA_ARGS__))

#define REP(i,n) for(int i=0, i##_length=int(n); i<i##_length; ++i)
#define REPD(i,n) for(int i=n-1; i>=0; --i)
#define FOR(i,a,b) for(ll i=a, i##_last=ll(b); i<=i##_last; ++i)
#define FORD(i,a,b) for(ll i=a, i##_stop=ll(b); i>=i##_stop; --i)
#define FORA(i,I) for(auto& i:I)

#define ALL(x) begin(x),end(x)
#define RALL(x) rbegin(x),rend(x)

#define F$ first
#define S$ second

#define R$(x,r) ((x)%(r)+(r))%(r)

template<class T> inline bool chmax(T &a, T b) { return (a<b ? a=b, true : false); }
template<class T> inline bool chmin(T &a, T b) { return (a>b ? a=b, true : false); }


signed main() {
    int n, k; cin >> n >> k;
    vector<int> p(n); REP(i, n) cin >> p[i];

    map<int,long> stage; // {�g�b�v�̃J�[�h, �ς܂�Ă��閇��}
    vector<int> ans(n+1); // ������ێ�����z��

    REP(i, n) {
        int v = p[i];
        auto itr = stage.lower_bound(v);  // �ςނׂ��J�[�h��T���Ă���B

        if(itr == stage.end()) {  // ������Ȃ�������B
            stage.emplace(v, 1);  // �V���ɒǉ��B(1�������d�Ȃ��Ă���)
        } else { // ����������g�b�v������������B
            stage[v] = itr->S$ + 1;  // ���ۂɂ́C�V���ɒǉ����āC
            ans[v] = ans[itr->F$] < 0 ? ans[itr->F$] : -itr->F$;  // (��q) ��1
            stage.erase(itr);  // �Â����������B
        }

        if(stage[v] >= k) {  // K ���𒴂�����C
            (ans[v] < 0 ? ans[-ans[v]] : ans[v]) = i+1;  // ���������������āC
            stage.erase(v);  // ���̑���H�ׂ�B
        }

        debug(stage); debug(ans);
    }

    // ans[i] �ɂ͒ʏ�C�u���̃J�[�h���H�ׂ�ꂽ�^�[���v���������ށB
    // �������C�J�[�h�̏�ɕʂȃJ�[�h���d�˂�Ƃ��C
    // ���̑��͂܂Ƃ߂ē����ɐH�ׂ���̂ŁC
    // ��Ԓ�ɂ���(�ŏ��ɒu���ꂽ)�J�[�h�ȊO�ɂ��ẮC
    // ���ۂ̓����̑���ɁC�u�ǂ̃J�[�h�Ɠ����ɐH�ׂ���̂��v��ۑ����āC
    // �������o�͂���ۂɂ��̃J�[�h�̓������Q�Ƃ���B(��2 �̕���)
    // �����́C��҂��C__�����𔽓]������__�ۑ����邱�Ƃŋ�ʂ��ł���B (��1 �̕���)

    FOR(i, 1, n) {
        int v = ans[i];
        if(v < 0) v = ans[-v];  //  ans[i] �����Ȃ�C�Q�Ɛ�̓����������Ă���B ��2
        cout << (v == 0 ? -1 : v) << "\n";
    }

    return 0;
}
