#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pl pair<ll,ll>
#define pi pair<int,int>
#define vi vector<int>
#define vl vector<ll>
#define all(v) v.begin(),v.end()

/////////////////////////////////////////////////////////////////
// Segment tree with lazy propagation (sum example)

string operation = "sum"; // can be "sum", "min", "max", "gcd"

// Combine two segments based on operation
int segmentOperation(int a, int b) {
    if (operation == "sum") return a + b;
    if (operation == "min") return min(a, b);
    if (operation == "max") return max(a, b);
    if (operation == "gcd") return gcd(a, b); // C++17
    return 0;
}

// Segment tree node: {value, lazy}
vector<pair<ll,int>> segment;

// Build segment tree
void build(vector<int> &v, int i, int l, int r) {
    if (l == r) {
        // Leaf node stores single array element
        segment[i] = {v[l], 0};
    } else {
        int mid = (l + r) / 2;
        build(v, 2*i + 1, l, mid);
        build(v, 2*i + 2, mid + 1, r);
        // Internal node combines children
        segment[i] = {segmentOperation(segment[2*i+1].first, segment[2*i+2].first), 0};
    }
}

// Push lazy value to children
void push(int i, int l, int r) {
    if (segment[i].second != 0) {
        int mid = (l + r) / 2;
        // Update left child
        segment[2*i + 1].first += 1LL * (mid - l + 1) * segment[i].second;
        segment[2*i + 1].second += segment[i].second;
        // Update right child
        segment[2*i + 2].first += 1LL * (r - mid) * segment[i].second;
        segment[2*i + 2].second += segment[i].second;
        // Clear current node lazy
        segment[i].second = 0;
    }
}

// Range update: add 'val' to [l,r]
void rangeUpdate(int i, int sl, int sr, int l, int r, int val) {
    // No overlap
    if (l > sr || r < sl) return;

    // Complete overlap
    if (l <= sl && sr <= r) {
        segment[i].first += 1LL * (sr - sl + 1) * val;
        segment[i].second += val; // mark lazy for children
        return;
    }

    // Partial overlap
    push(i, sl, sr); // push lazy before going deeper
    int mid = (sl + sr) / 2;
    rangeUpdate(2*i + 1, sl, mid, l, r, val);
    rangeUpdate(2*i + 2, mid + 1, sr, l, r, val);
    // Recompute current node after children updates
    segment[i].first = segmentOperation(segment[2*i+1].first, segment[2*i+2].first);
}

// Query sum (or operation) in [l,r]
ll query(int i, int sl, int sr, int l, int r) {
    // No overlap
    if (l > sr || r < sl) {
        if (operation == "sum") return 0;
        if (operation == "min") return INT_MAX;
        if (operation == "max") return INT_MIN;
        if (operation == "gcd") return 0;
    }

    // Complete overlap
    if (l <= sl && sr <= r) return segment[i].first;

    // Partial overlap
    push(i, sl, sr); // push lazy to children
    int mid = (sl + sr) / 2;
    ll left = query(2*i + 1, sl, mid, l, r);
    ll right = query(2*i + 2, mid + 1, sr, l, r);
    return segmentOperation(left, right);
}

// Single point update: set arr[pos] = newVal
void pointUpdate(int i, int sl, int sr, int pos, int newVal) {
    if (sl == sr) {
        // Leaf node
        segment[i].first = newVal;
        segment[i].second = 0; // clear lazy
        return;
    }
    push(i, sl, sr); // push lazy before going deeper
    int mid = (sl + sr) / 2;
    if (pos <= mid) pointUpdate(2*i + 1, sl, mid, pos, newVal);
    else pointUpdate(2*i + 2, mid + 1, sr, pos, newVal);
    // Update current node after child update
    segment[i].first = segmentOperation(segment[2*i+1].first, segment[2*i+2].first);
}

/////////////////////////////////////////////////////////////////
// Example usage
void kurumi() {
    vector<int> arr = {1,2,3,4,5};
    int n = arr.size();
    segment.assign(4*n, {0,0}); // 4*n size for segment tree

    build(arr, 0, 0, n-1);

    cout << "Initial sum [1,3]: " << query(0,0,n-1,1,3) << "\n"; // 2+3+4=9

    rangeUpdate(0, 0, n-1, 1, 3, 2); // add +2 to [1,3]
    cout << "After range update +2 [1,3]: " << query(0,0,n-1,1,3) << "\n"; // 4+5+6=15

    pointUpdate(0, 0, n-1, 2, 10); // arr[2] = 10
    cout << "After point update arr[2]=10, sum [1,3]: " << query(0,0,n-1,1,3) << "\n"; // 4+10+6=20
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    kurumi();
    return 0;
}
