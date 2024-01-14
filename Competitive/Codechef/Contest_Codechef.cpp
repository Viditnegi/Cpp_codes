#include<iostream>
#include<climits>
#include<cmath>
#include<vector>
#include<algorithm>
#include<set>

#define ll long long
#define MOD 1e9+7

using namespace std;

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

int main(){
    int T;
    cin>>T;
    while(T--){

        



    }
    return 0; 
}