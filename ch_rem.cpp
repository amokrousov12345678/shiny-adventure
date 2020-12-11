//не причесывал ибо влом
ll x, y;

ll ext_gcd(ll a, ll b) {
    if (b==0) {
        x = 1;
        y = 0;
        return a;
    }
    ll tmp = ext_gcd(b, a % b);
    ll tmp_x = y;
    ll tmp_y = x-(a/b)*y;
    x = tmp_x;
    y = tmp_y;
    return tmp;
}

ll mod_inv(ll a, ll m) {
    ll res = ext_gcd(a, m);
    assert(res==1);
    if (x<0) x+=m;
    return x;
}

ll mul(ll a, ll b, ll mod) {
    return (a*b) % mod;
}

ll add(ll a, ll b, ll mod) {
    return (a+b) % mod;
}

ll ch_rem(vector<ll> rem, vector<ll> mod) {
    ll res = 0;
    assert(rem.size()==mod.size());
    ll M = 1;
    for (int i=0;i<mod.size();i++) {
        M *= mod[i];
    }
    for (int i=0;i<mod.size();i++) {
        ll Mi = M/mod[i];
        ll invMi = mod_inv(Mi, mod[i]);
        ll tmp = mul(rem[i], mul(Mi, invMi, M), M);
        res = add(res, tmp, M);
    }
    return res;
}