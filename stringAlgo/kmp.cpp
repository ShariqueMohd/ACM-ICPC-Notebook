#include<bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int> > vvi;
#define forn(i,x,y) for(i = (x) ; i <= (y) ; ++i)
#define forr(i,y,x) for(i = (y) ; i >= (x) ; --i)
#define forv(v,i) for(i=v.begin();i!=v.end();++i)
#define forvr(v,i) for(i=v.end()-1;i!=v.begin();--i)
#define FA(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define PB push_back
#define PF push_front
#define MP make_pair
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define MOD(x,y) (((x%M)*(y%M))%M)
#define CLR(x,y) memset(x,y,sizeof(x))
#define precisionvalue printf("%.6lf\n",ans);
ll M=1000000007;
//while(~scanf("%d",&n) )

/*-------------------------Template Ends--------------------------------*/

void preKMP(string pattern, int f[]) {
    int m = pattern.length()+1,k;
    f[0] = -1;
    for (int i = 1; i < m; ++i) {
        k = f[i-1];
        while (k >= 0 && pattern[k] != pattern[i-1]) {
            k = f[k];
        }
        f[i] = k + 1;
    }
}

long long int KMP(string pattern, string text) {
    int n,m,i,k,freq;
    m = pattern.length(), n = text.length();
    int f[m+1];
    preKMP(pattern, f);
    i = 0, k = 0, freq = 0;

    while (i < n) {
        if (k == -1) {
            ++i; k = 0;
        } else if (text[i] == pattern[k]) {
            ++i; ++k;
            if (k >= m) ++freq, k = m;     //String matched
        }
        else k = f[k];
    }
    return freq;
}


int main()
{
//	ios::sync_with_stdio(0);
//	cin.tie(0);
	ll count;
    string pat, text;
	cin >> pat >> text;
	count = KMP(pat, text);
	cout << count << endl;
	// cout << st[1] << endl;
	return 0;
}
