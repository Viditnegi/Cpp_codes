#include<iostream>
#include<climits>
#include<cmath>
#include<vector>
#include<algorithm>
#include<set>
#include<unordered_map>
#include<iomanip>
#include<map>
#include<stack>
#include<queue>

using namespace std;

#define ll long long
int MOD = 1e9+7;

// ---------------------SIEVE---------------------------------
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
// --------------------------SIEVE---------------------------------

//---------------------------AREAS-----------------------------------
double areaTriangle(double base,double height){
    return (base*height*0.5);
}
double areaTrapezium(double upperBase,double lowerBase,double height){
    return ((upperBase+lowerBase)*0.5*height);
}

//---------------------------AREAS-----------------------------------

// ---------------------------DSU------------------------------------------
class dset{
public:
    vector<int> parent;
    vector<int> rank;
    vector<int> size;
public:
    dset(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1,1);
        for(int i = 0;i<=n;i++){
            parent[i] = i;
        }
    }
    int findparent(int node){
        if(node == parent[node]){
            return node;
        }
        return parent[node] = findparent(parent[node]);
    }
   void unionbyrank(int u,int v){
        int parentu=  findparent(u);
        int parentv = findparent(v);

        if(parentu == parentv)return;
        if(rank[parentu] < rank[parentv]){
            parent[parentu] = parentv;
        }
        else if(rank[parentv] < rank[parentu]){
            parent[parentv] = parentu;
        }
        else{
            parent[parentv] = parentu;
            rank[parentu]++;
        }
    }
    void unionbysize(int u,int v){
        int parentu=  findparent(u);
        int parentv = findparent(v);
        if(parentu == parentv)return;
        if(size[parentu] < size[parentv]){
            parent[parentu] = parentv;
            size[parentv] += size[parentu];
      
        }
        else{
            parent[parentv] = parentu;
            size[parentu] += size[parentv];
        }
    } 
};
// ---------------------------DSU------------------------------------------









//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x

void solve1(){
    
    





}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(3);
    int T;
    cin>>T;
    while(T--){
        
        solve1();

    }
    return 0; 
}