//slow :( (uncomment reductions if krendle zdox)
struct Frac {
    ll num;
    ll den;

    static void reduce(Frac& l) {
        ll tmp = __gcd(l.num,l.den);
        l.num /= tmp;
        l.den /= tmp;
        if (l.den<0) {
            l.num*=-1;
            l.den*=-1;
        }
    }

    static void unify(Frac& l, Frac& r) {
        ll lcmDen = l.den/__gcd(l.den, r.den)*r.den;
        ll mult1 = lcmDen/l.den;
        ll mult2 = lcmDen/r.den;
        l.num *= mult1;
        r.num *= mult2;
        l.den = lcmDen;
        r.den = lcmDen;
    }

    friend bool operator<(Frac l, Frac r) {
        //reduce(l);
        //reduce(r);
        return l.num*r.den < r.num*l.den;
    }

    friend bool operator>(Frac l, Frac r) {
        return r<l;
    }

    friend bool operator==(Frac l, Frac r) {
        //reduce(l);
        //reduce(r);
        return l.num==r.num && l.den==r.den;
    }

    friend bool operator<=(Frac l, Frac r) {
        return l<r || l==r;
    }

    friend bool operator>=(Frac l, Frac r) {
        return l>r || l==r;
    }

    friend Frac operator+(Frac l, Frac r) {
        unify(l,r);
        auto res = Frac(l.num+r.num, l.den);
        reduce(res);
        return res;
    }

    Frac(ll num, ll den): num(num), den(den) {};
    Frac(): Frac(0,1) {};
};