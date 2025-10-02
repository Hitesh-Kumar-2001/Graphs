#include<bits/stdc++.h>
using namespace std;
 
#define debug(x) cout<<"{"<<(#x)<<":"<<(x)<<"}";
#define ll long long
#define dd double
#define pl pair<ll,ll>
#define pi pair<int,int>
#define vl vector <pl>
#define vi vector <pi> 
#define all(v) v.begin(),v.end()           
#define trav(a,x) for(auto& a : x)
#define pb push_back
#define mp make_pair
#define endm "\n"
#define sec second
#define lb(v,a) lower_bound(v.begin(), v.end(), a)
#define ub(v,a) upper_bound(v.begin(), v.end(), a);
#define loop(I,intialise,N,INC) for(I=intialise;I<N&&I>N;I+=INC)
#define sortd(v) sort(vr(v), greater<int>());
#define forin(i,n) for(ll i=0;i<n;i++)
#define take(x) int x;cin>>x;
#define input(v) forin(i,v.size())cin>>v[i];
 
////////////////////////////////////////////////////////////////////////////////////////////////templates
template<typename T, typename U> static inline void amin(T &x, U y){ if(y < x) x = y; }
template<typename T, typename U> static inline void amax(T &x, U y){ if(x < y) x = y; }
 
 
////////////////////////////////////////////////////////////////////////////////////////////////constants            
const int MOD = 1e9 + 7;
 
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ascii value   0->48, a->97, A->65 write functions here
 
 
/////////////////////////////////////////////////////////////////////////////////
// segment tree

string operation = "sum";

int segmentOperation(int a, int b) {
    if (operation == "sum") return a + b;
    if (operation == "min") return min(a, b);
    if (operation == "max") return max(a, b);
    if (operation == "gcd") return gcd(a, b); // C++17 gcd
    return 0;
}

vector<int> segment;

void build(vector<int> &v, int i, int l, int r) {
    if (l == r) {
        segment[i] = v[l];
    } else {
        int mid = (l + r) / 2;
        build(v, 2 * i + 1, l, mid);
        build(v, 2 * i + 2, mid + 1, r);
        segment[i] = segmentOperation(segment[2 * i + 1], segment[2 * i + 2]);
    }
}

int query(int i, int sl, int sr, int l, int r) {
   // sr and sl define the segment which segment[i]covers in base array
   // this below is not intersection with the segment[i]
    if (l > sr || r < sl) {
        // return neutral element based on operation
        if (operation == "sum") return 0;
        if (operation == "min") return INT_MAX;
        if (operation == "max") return INT_MIN;
        if (operation == "gcd") return 0; 
    }
    // this below is exact equal to the segment[i] range
    if (l <= sl && sr <= r) return segment[i];
    // this below ispartial intersection segment[i] range
    int mid = (sl + sr) / 2;
    int left = query(2 * i + 1, sl, mid, l, r);
    int right = query(2 * i + 2, mid + 1, sr, l, r);
    return segmentOperation(left, right);
}


// for find kth zero or any number
// given a segment tree in which nodes stores occurences of that number we can get kth in range

int find_kth(int v, int tl, int tr, int k) {
    if (k > t[v])
        return -1;
    if (tl == tr)
        return tl;
    int tm = (tl + tr) / 2;
    if (t[v*2] >= k)
        return find_kth(v*2, tl, tm, k);
    else 
        return find_kth(v*2+1, tm+1, tr, k - t[v*2]);
}
void update(int i, int sl, int sr, int pos, int newVal) {
   // leaf case
    if (sl == sr) {
        segment[i] = newVal;
        return;
    }
    int mid = (sl + sr) / 2;
    // left child location
    if (pos <= mid)
        update(2 * i + 1, sl, mid, pos, newVal);
    // right child location
    else
        update(2 * i + 2, mid + 1, sr, pos, newVal);

    segment[i] = segmentOperation(segment[2 * i + 1], segment[2 * i + 2]);
}
void kurumi()
{  
  
   
}
 
//////////////////////////////////////////////////////////////////////////////////////
   int main ()
    {   
       ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
       int zaphkeil=1,i;
       // cin>>zaphkeil;
        
        for(i=0;i<zaphkeil;i++)
         {
           kurumi();
         }
              
        return 0;
    }
 
/////////////////////////////////////////////////////////////////////////
