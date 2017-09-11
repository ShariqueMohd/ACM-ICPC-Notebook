#include<bits/stdc++.h>

#define pb push_back
using namespace std;
const int N=1e5+5;

vector<int> prime;
bool isC[N];    // Is_Composite

void sieve(int n) {
    memset(isC, 0, sizeof(isC));
    for(int i=2; i<n; i++) {
        if(!isC[i]]) {
            prime.pb(i);
        }
        for(int j=0; j<prime.size(); j++) {
            isC[i*prime[j]] = 1;
            if(i%prime[j]==0) {
                break;
            }
        }
    }
}

int main() {

    return 0;
}
