#include <bits/stdc++.h>

#define pb push_back
using namespace std;

const int N=1e5+5;

vector<int> prime;
bool isC[N];    // Is_Composite
int phi[N];

void ETF(int n) {
    memset(isC, 0, sizeof(isC));
    for(int i=2; i<n; i++) {
        if(!isC[i]) {
            prime.pb(i); phi[i]=i-1;
        }
        for(int j=0; j<prime.size(); j++) {
            isC[i*prime[j]] = 1;
            if(i%prime[j] == 0) {
                phi[i*prime[j]] = phi[i] * prime[j];
                break;
            }
            else {
                phi[i*prime[j]] = phi[i] * phi[prime[j]];
            }
        }
    }
}


int main() {
    ETF(100);
    for(int i=2;i<40;i++) {
        cout << i << "\t" << phi[i] << "\n";
    }

    return 0;
}
