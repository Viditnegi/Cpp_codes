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
    string y = "";
    for(int  i =0;i<52;i++){
        y+="Yes";
    }
    while(T--){
        string s;
        cin>>s;
        
        int size = y.size()-s.size();
        bool flag = false;
        for(int i =0;i<=size;i++){
            string substring = y.substr(i,s.size());
            if(substring == s){
                cout<<"YES"<<endl;
                flag = true;
                break;
            }
        } 
        if(!flag){cout<<"NO"<<endl;}
    
    }
    return 0; 
}