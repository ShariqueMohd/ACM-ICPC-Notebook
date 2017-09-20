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

int zvalues[100005];
string st;

void findZvalues(string s, int * values) {
/* aabxaabxcaabxaabxay */
	int i,j,k,left,right,len;
	len = s.size();
	values[0] = 0;
	left = right = 0;

	for(i = 1; i < len; ++i) {
		k = i - left;
		if(right < i) {
			left = right = i;
			while((right < len) && (s[right] == s[right - i])) {
				right++;
			}
			right--;
			values[i] = right - left + 1;
		}
		else if((values[k] + i - 1) < right) { //value of z[k] !crossing the frontier
			values[i] = values[k];
		}
		else {
			left = i;
			right++;
			while((right < len) && (s[right] == s[right - i])) {
				right++;
			}
			right --;
			values[i] = right - left + 1;
		}
	}
}


int main()
{
//	ios::sync_with_stdio(0);
//	cin.tie(0);
	ll i,j,k,n,m,p,q,u,v,count,ans,temp,test;
	cin >> st;
	findZvalues(st, zvalues);
	int len = st.size();
	forn(i,0,len-1) cout << zvalues[i];
	cout << endl;
	// cout << st[1] << endl;
	return 0;
}
