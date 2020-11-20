//просто создаём от строки, получаем перестановку и массив классов эквивалентности для каждой подстроки длины 2^k
//ВНИМАНИЕ: надо приписать '\0' к концу строки, если нужна именно перестановка суффиксов

struct SufArray {
    const int alphabet = 256;

    vector<int> p;
    vector<vector<int>> c;
    SufArray(const string& s) {
        int n = s.size();
        int logn = 0;
        int cur = 1;
        while (cur<n) {
            logn++;
            cur <<=1;
        }

        c.resize(logn);
        for (int i=0;i<logn;i++) {
            c[i].resize(n);
        }
        p.resize(n);

        vector<int> cnt(alphabet,0);
        vector<int> c(n,0), p(n,0), cn(n,0), pn(n,0);
        //0 iter;
        for (int i=0; i<n; ++i)
            ++cnt[s[i]];
        for (int i=1; i<alphabet; ++i)
            cnt[i] += cnt[i-1];
        for (int i=0; i<n; ++i)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i=1; i<n; ++i) {
            if (s[p[i]] != s[p[i - 1]]) ++classes;
            c[p[i]] = classes - 1;
        }
        this->c[0] = c;

        for (int h=0; h<logn-1; ++h) {
            for (int i = 0; i < n; ++i) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += n;
            }
            cnt.assign(classes, 0);
            for (int i = 0; i < n; ++i)
                ++cnt[c[pn[i]]];
            for (int i = 1; i < classes; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; ++i) {
                int mid1 = (p[i] + (1 << h)) % n, mid2 = (p[i - 1] + (1 << h)) % n;
                if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c = cn;
            this->c[h+1] = c;
        }
        this->p = p;
    }
};

