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
#include<list>
#include<cassert>
#include<cstdint>

using namespace std;

#define ll long long
const int MOD = 1e9+7;
// ---------------------------Mpower-------------------------------------------
long long Mpower(long long base,long long exp){
    if(exp == 0){
        return 1;
    }
    
    long long result = 1;
    if((exp & 1) == 1){ 
        result = base;
    }
    
    long long temp = Mpower(base,exp>>1);
    temp = (temp*temp)%MOD;
    result = (result*temp)%MOD;
    return result%MOD;
}   
// ---------------------------Mpower----------------------------------------
// --------------------------Mint-------------------------------------
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}

template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }

  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }

  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }

  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
      "divl %4; \n\t"
      : "=a" (d), "=d" (m)
      : "d" (xh), "a" (xl), "r" (mod())
    );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {
    int64_t q = static_cast<int64_t>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend std::istream& operator>>(std::istream& stream, Modular<U>& number);

 private:
  Type value;
};

template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Modular<T>& number) {
  return stream << number();
}

template <typename T>
std::istream& operator>>(std::istream& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, int64_t>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}

/*
using ModType = int;

struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/

constexpr int md = MOD;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;
// --------------------------Mint-------------------------------------

// ------------------------BIT TRIE-------------------------------------
class bitNode{
public:
    bitNode* links[2];
    int count[2] = {0};
    bool containsKey(int bit){
        return (links[bit] != NULL);
    }
    bitNode* get(int bit){
        return links[bit];
    }
    void put(int bit){
        bitNode* node = new bitNode();
        links[bit] = node;
    }
};


class bitTrie{
private:
    bitNode* root;
    int nbits = 32;
public:
    bitTrie(){
        root = new bitNode();
    }
    bitTrie(int n){
        root = new bitNode();
        nbits = n;
    }
public:
    void insert(int number){
        bitNode* temp = root;
        for(int i = nbits-1;i>=0;i--){
            int bit = (number>>i) & 1;
            temp->count[bit]++;
            if(!temp->containsKey(bit)){
                temp->put(bit);
            }
            temp = temp->get(bit);
        }
    }
    void remove(int number){
        bitNode* temp = root;
        for(int i = nbits-1;i>=0;i--){
            int bit = (number>>i)&1;
            temp->count[bit]--;
            if(temp->count[bit] == 0){
                temp->links[bit] = NULL;
                break;
            }
            temp = temp->get(bit);
        }
        
    }
    bool find(int number){
        bitNode* temp = root;
        for(int i = nbits-1;i>=0;i--){
            int bit = (number>>i) &1;
            if(!temp->containsKey(bit)){
                return false;
            }
            temp = temp->get(bit);
        }

        return true;
    }
    int getMax(int number){
        bitNode* temp = root;
        int x =0;
        for(int i = nbits-1;i>=0;i--){
            int bit = (number>>i)&1;
            if(temp->containsKey(1-bit)){
                x = x | (1<<i);
                temp = temp->get(1-bit);
            }
            else{
                temp = temp->get(bit);
            }
        }

        return x;
    }
    
};
// ----------------------BIT TRIE-------------------------------------
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

// ---------------------------- SEGMENT TREE -------------------------------
class segTree{
public:
    vector<int> v;
    vector<int> segMax;
    vector<int> segSum;
    vector<int> lazy;
    segTree(vector<int> &arr){
        v.resize(arr.size());
        segMax.resize(4*arr.size(),0);
        segSum.resize(4*arr.size(),0);
        lazy.resize(4*arr.size(),0);


        for(int i =0;i<arr.size();i++) v[i] = arr[i];

        buildMax(0,0,v.size()-1);
        buildSum(0,0,v.size()-1);

    }
    void buildMax(int ind,int low,int high){
        if(low == high){
            segMax[ind] = v[low];
            return;
        }
        int mid = low+(high-low)/2;
        buildMax(ind*2+1,low,mid);
        buildMax(ind*2+2,mid+1,high);
        segMax[ind] = max(segMax[2*ind+1],segMax[2*ind+2]);
    }

    void buildSum(int ind,int low,int high){
        if(low==high){
            segSum[ind] = v[low];
            return;
        }
        int mid = low+(high-low)/2;
        buildSum(2*ind+1,low,mid);
        buildSum(2*ind+2,mid+1,high);
        segSum[ind] = segSum[2*ind + 1] + segSum[2*ind+2];
    }

    int findMax(int ind,int low,int high,int l,int r){
        if(l <= low && high <=r){
            return segMax[ind];
        }
        if(high<l || low>r) return INT_MIN;
        int mid = low + (high-low)/2;
        int left = findMax(2*ind+1,low,mid,l,r);
        int right = findMax(2*ind+2,mid+1,high,l,r);
        return max(left,right);
    }

    // int findSum(int ind,int low,int high,int l,int r){
    //     if(l<=low and high<=r){
    //         return segSum[ind];
    //     }
    //     if(high<l ||low>r) return 0;
    //     int mid = low+(high-low)/2;
    //     int left = findSum(2*ind+1,low,mid,l,r);
    //     int right = findSum(2*ind+2,mid+1,high,l,r);
    //     return left+right;
    // }

    // void pointUpdate(int ind,int low,int high,int node,int val){
    //     if(low == high){
    //         segSum[ind] +=val;
    //         return;
    //     }
    //     int mid = low + (high-low)/2;
    //     if(node<=mid and node>=low){
    //         pointUpdate(2*ind + 1,low,mid,node,val);
    //     }
    //     else{
    //         pointUpdate(2*ind + 2,mid+1,high,node,val);
    //     }
    //     segSum[ind] = segSum[2*ind+1]+segSum[2*ind+2];
    // }

    void propogate(int ind,int low,int high){
        if(lazy[ind]!=0){
            segSum[ind] += (high-low+1)*lazy[ind];
            if(low!=high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
    }
    void rangeUpdate(int ind,int low,int high,int l,int r,int val){

        propogate(ind,low,high);

        if(r<low || l>high || low>high) return;

        if(low>=l && high<=r){
            segSum[ind] +=(high-low+1)*val;
            if(low!=high){
                lazy[2*ind+1] += val;
                lazy[2*ind+2] += val;
            } 
            return;
        }

        int mid = low + (high-low)/2;
        rangeUpdate(2*ind+1,low,mid,l,r,val);
        rangeUpdate(2*ind+2,mid+1,high,l,r,val);
        segSum[ind] = segSum[2*ind+1] + segSum[2*ind+2];
    }

    int findLazySum(int ind,int low,int high,int l,int r){

        propogate(ind,low,high);

        if(r<low || l>high || low>high) return 0;
        if(low>=l && high<=r){
            return segSum[ind];
        }

        int mid = low + (high-low)/2;
        int left = findLazySum(2*ind+1,low,mid,l,r);
        int right = findLazySum(2*ind+2,mid+1,high,l,r);

        return left + right;
    }
};
// ---------------------------- SEGMENT TREE -------------------------------

//x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x

void solve1(){
    
    
   




}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(3);
    int T =1;
    cin>>T;
    while(T--){
        
        solve1();

    }
    return 0; 
}