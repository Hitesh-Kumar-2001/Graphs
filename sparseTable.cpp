#include<bits/stdc++.h>
using namespace std;

#define debug(x) cout<<"{"<<(#x)<<":"<<(x)<<"}";
#define debug2(x) cout<<"{"<<(#x)<<":"<<(x)<<"}\n";
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
#define sec second
#define lb(v,a) lower_bound(all(v), a)
#define ub(v,a) upper_bound(all(v), a)
#define loop(I,intialise,N,INC) for(I=intialise;I<N&&I>N;I+=INC)
#define sortd(v) sort(all(v), greater<int>());
#define forin(i,n) for(ll i=0;i<n;i++)
#define take(x) int x;cin>>x;
#define input(v) forin(i,v.size())cin>>v[i];
#define amin(a,b) a = min(a,b)
#define amax(a,b) a = max(a,b)
#define printvec(v) forin(i,v.size())cout<<v[i]<<" ";cout<<"\n";

////////////////////////////////////////////////////////////////////////////////////////////////templates
//bitset<32>(v[i]).to_string() convert into binary


////////////////////////////////////////////////////////////////////////////////////////////////constants            
const int MOD = 1e9 + 7;
const int max_size = 1e7;
const int inf = INT_MAX;
#define amod(a) a=a%MOD;
#define neg_mod(a) a=(MOD+a%MOD)%MOD


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ascii value   0->48, a->97, A->65 write functions here

vector<vector<int>> sparseTable;

int query( int l, int r, int n){
   int h = log2( r - l + 1 );
   int ans = INT_MAX;
   int k = l;
   for(int i = h; i>=0;i--){
        // Ensure we stay within bounds, no need to check if the index is whitin the range of next iteration of i
        // becuase if it has to skip that particular i then that means r is probably less than that of increament
        // so ultimately check with r if it withing bounds let it increeement
        if (k + (1 << i) - 1 <= r) {  
            ans = min(ans, sparseTable[i][k]);  
            k += (1 << i);  // Move to the next range
        }

   }

   return ans;
}

void buildSparseTable( vector<int> v ){
   // array size
   int n = v.size();
   // depth of table
   int h = log2(n);
   sparseTable.push_back(v);
   for(int i=1;i<=h;i++){
      // size optimization
      int vSize = n - pow(2,i) + 1;
      sparseTable.push_back(vector<int>(vSize));

      for(int j=0;j<sparseTable[i].size();j++){
         // element of current row will operator( sparseTable[i][j] + sparseTable[i][ j+ 1<<(i-1) ] )
         // first element will cover starting element and second element is taken ( 2^(i-1) == 1<<(i-1) )
         // becuase it will avoid overlap, eg 2nd row is op(4 elements ) i.e [ ( 1,2,3,4 ), (2,3,4,5),
         // (3,4,5,6), ( 4,5,6,7 ), (5,6,7,8) ] then 3rd row os op( 8 elements ) so we will need 1st element
         // in above 2nd rows of element mention above i.e (1,2,3,4) + ( 5,6,7,8 ) which is pow(2,i-1) skip to the
         // jth index
         // cout<< j + pow( 2, i-1 )<<"       "<< j+ ( 1<<(i-1) ) <<endl;
         sparseTable[i][j] = min (sparseTable[i-1][j] , sparseTable[i-1][j+ ( 1<<(i-1) ) ]);
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////

void kurumi()
{  
      vector<int> v = {4,2,3,7,1,5,3,3,9,6,7,-1,4};
      buildSparseTable(v);
      cout<<query(0,11,12);
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
