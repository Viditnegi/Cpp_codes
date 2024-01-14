#include<iostream>
#include<climits>
#include<cmath>
#include<vector>
#include<set>

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
        int m,s;
        cin>>m>>s;
        set<int> st;
        for(int i = 0;i<m;i++){
            int temp;
            cin>>temp;
            st.insert(temp);
        }

        int counter = 1;
        while(s>0){
            if(st.find(counter) == st.end()){
                st.insert(counter);
                s -= counter;
            }
            counter++;
        }


        counter = 1;
        bool flag = true;
        while(counter <= st.size()){
            if(st.find(counter) == st.end()){
                flag = false;
                break;
            }
            counter++;
        }

        if(s<0){
            cout<<"NO\n";
        }
        else if(flag == false){
            cout<<"NO\n";
        }
        else{
            cout<<"YES\n";
        }
    
    }
    return 0; 
}