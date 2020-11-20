//permutation - sequence of numbers of elements taken from original sequence. Apply permutation - create sequence in this order.
ll idOfPerm(const vector<int>& perm) {
    int n=perm.size();
    int pos[n];
    int elems[n];
    ll k=0,m=1;

    for(int i=0;i<n;i++) {pos[i]=i; elems[i]=i;}

    for(int i=0;i<n-1;i++) {
        k+=m*pos[perm[i]];
        m=m*(n-i);
        pos[elems[n-i-1]]=pos[perm[i]];
        elems[pos[perm[i]]]=elems[n-i-1];
    }

    return k;
}

vector<int> permById(int n, ll k) {
    int i, ind;
    vector<int> permuted(n);
    int elems[n];

    ll m = k;
    for(i=0;i<n;i++) elems[i]=i;

    for(i=0;i<n;i++) {
        int ind=m%(n-i);
        m=m/(n-i);
        permuted[i]=elems[ind];
        elems[ind]=elems[n-i-1];
    }

    return permuted;
}

//apply permutation (also can be used to multiply permutations)
void applyPerm(const vector<int>& a, const vector<int>& perm, vector<int>& res) {
    assert(perm.size() == a.size());
    assert(perm.size() == res.size());
    for (int i=0;i<perm.size();i++) {
        res[i] = a[perm[i]];
    }
}

vector<int> applyPerm(const vector<int>& a, const vector<int>& perm) {
    vector<int> res(a.size());
    applyPerm(a, perm, res);
    return res;
}

void invPerm(const vector<int>& perm, vector<int>& res) {
    assert(perm.size() == res.size());
    int n = perm.size();
    for (int i=0;i<n;i++) {
        res[perm[i]] = i;
    }
}

vector<int> invPerm(const vector<int>& perm) {
    vector<int> res(perm.size());
    invPerm(perm, res);
    return res;
}

vector<vector<int>> getPermLoops(const vector<int>& perm) {
    int n = perm.size();
    vector<vector<int>> res;
    vector<int> used(n, 0);
    for (int i=0;i<n;i++) {
        if (used[i]) continue;
        vector<int> curLoop;
        int v = i;
        do {
            curLoop.push_back(v);
            used[v] = 1;
            v = perm[v];
        } while (v != i);
        res.push_back(std::move(curLoop));
    }
    return res;
}