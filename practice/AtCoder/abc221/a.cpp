//Codeforces��128bit�������g�������Ƃ�
//��__int128_t���g��&GNU C++17 (64)�Œ�o����

//�C���N���[�h�Ȃ�
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//�C�e���[�V����
#define REP(i,n) for(ll i=0;i<ll(n);i++)
#define REPD(i,n) for(ll i=n-1;i>=0;i--)
#define FOR(i,a,b) for(ll i=a;i<=ll(b);i++)
#define FORD(i,a,b) for(ll i=a;i>=ll(b);i--)
#define FORA(i,I) for(const auto& i:I)
//x:�R���e�i
#define ALL(x) x.begin(),x.end() 
#define SIZE(x) ll(x.size()) 
//�萔
#define INF32 2147483647 //2.147483647�~10^{9}:32bit������inf
#define INF64 9223372036854775807 //9.223372036854775807�~10^{18}:64bit������inf
#define MOD 1000000007 //���ɂ��
//���L
#define F first
#define S second
//�o��(�󔒋�؂�ŏ�����)
#define coutALL(x) for(auto i=x.begin();i!=--x.end();i++)cout<<*i<<" ";cout<<*--x.end()<<endl;

//a��b�Ŋ��鎞�̌J�グ,�J�艺��
ll myceil(ll a,ll b){return (a+(b-1))/b;}
ll myfloor(ll a,ll b){return a/b;}

int main(){
  int a, b;
  cin >> a >> b;
  cout << (ll)pow(32, a - b) << endl;
  //�����̌����̏o�͎w��
  //cout<<fixed<<setprecision(10);
  //���͂̍������p�̃R�[�h
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);
}
