//integer division, correctly works with negative values
pair<ll,ll> divNorm(ll a, ll b) {
    ll res = a/b;
    ll mod = a%b;
    if (mod<0) {
        res--;
        mod+=b;
    }
    return {res, mod};
}

ll divRoundDown(ll a, ll b) {
    auto divRes = divNorm(a,b);
    return divRes.first;
}

ll divRoundUp(ll a, ll b) {
    auto divRes = divNorm(a,b);
    ll res = divRes.first;
    if (divRes.second) {
        res++;
    }
    return res;
}