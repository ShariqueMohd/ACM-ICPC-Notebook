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

unordered_map<char, int> alphabet;

int fsm[10000][100];		// SM for 100 characters

void mapCharToInt(string s) {			//input str with all possible chars.
																	//#NOTE to map chars to int it will use the globally declared map
	int index = 0,i;
	for(i = 0; i < s.size(); ++i) {
		if(alphabet.find(s[i]) == alphabet.end()) {
			alphabet[s[i]] = 	index;
			index++;
		}
	}
}

void makeFSM(string s) {
		//SUFPRE - suffix which is equal to prefix
		//input the string whose FSM is to be made
		//#NOTE It will use globally declared map. Updates fsm[][]
		//largest stores the len of largest SUFPRE (in the current string)

		int i,j,alphaNum,len,largest,nextChar;
		len = s.size();
		alphaNum = alphabet.size();

		for(j = 0; j < alphaNum; ++j) fsm[0][j] = 0;

		for(i = 0; i < len; ++i) {
			nextChar = alphabet[s[i]];
			largest = fsm[i][nextChar];		//len of largest SUFPRE after adding nextChar to curr str
			fsm[i][nextChar] = i + 1;			//after adding nextChar - making iTH state transit to newly created (i+1)TH state
			for(j = 0; j < alphaNum; ++j) fsm[i+1][j] = fsm[largest][j];	// initializing (i+1)TH state.
		}
}

void findString(string s, string text) {
	//prints the end of the occurances of the pattern in the text;
	int i,j,len,state,count,acceptableState;
	len = text.size();
	state = 0;
	acceptableState = s.size();
	for(i = 0; i < len; ++i) {
		state = fsm[state][alphabet[text[i]]];
		if(state == acceptableState) cout << "found at i = " << i << endl;
	}
}


int main()
{
	ll i,j;
	string pattern,validchar,text;
	cin >> pattern;
	cin >> validchar;
	cin >> text;
	mapCharToInt(validchar);
	makeFSM(pattern);
	findString(pattern,text);
	// for(i = 0; i <= st.size(); ++i) {
	// 	for(j = 0; j < alphabet.size(); ++j) {
	// 		cout << fsm[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	return 0;
}
