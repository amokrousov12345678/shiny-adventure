//z функция
template<typename T>
    vector<int> calc_z(const T& s) {
        vector<int> z(s.size());
        z[0] = s.size();
        int l = 0, r = 0;
        for (int i=1;i<s.size();i++) {
            if (i>r) {
                z[i] = 0;
            } else {
                z[i] = min(r-i+1, z[i-l]);
            }
            while (i+z[i]<s.size() && s[i+z[i]]==s[z[i]]) {
                z[i]++;
            }
            if (i+z[i]-1>r) {
                l = i;
                r = i+z[i]-1;
            }
        }
        return z;
    }

//префикс функция
template<typename T>
vector<int> calc_pi(const T& s) {
    int n = s.size();
    vector<int> pi(n);
    if (n) {
        pi[0] = 0;
    }
    for (int i=1;i<n;i++) {
        int k = pi[i-1];
        while (k && s[k]!=s[i]) {
            k = pi[k-1];
        }
        if (s[i]==s[k]) k++;
        pi[i] = k;
    }
    return pi;
}