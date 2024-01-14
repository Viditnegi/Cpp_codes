#include<iostream>
#include<climits>
#include<cmath>
#include<vector>

#define ll long long

using namespace std;

// -----------------------------------primes generator------------------------------------
vector<int> primes;

void sieve(int n){
    vector<int> temp(n+1,true);
    for(int i = 2;i*i<=n;i++){
        if(temp[i] == true){
            for(int j = i*i ;j<=n;j=j+i){
                temp[j] = false;
            }
        }
    }
    for(int i = 2;i<=n;i++){
        if(temp[i]==true){
            primes.push_back(i);
        }
    }
}
// -----------------------------------primes generator------------------------------------

int main(){
    int T;
    cin>>T;
    while(T--){
        int l,r,x,a,b;
        cin>>l>>r>>x>>a>>b;
        
        
        



    }
    return 0; 
}