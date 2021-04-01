//z fun
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

//pref fun
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

//Copypaste from old reference
// Lyndon decomposition and minimal cyclical shift search in O(n)
string min_cyclic_shift(string s) {
	s += s;
	int n = (int) s.length();
	int i = 0, ans = 0;
	while (i < n / 2) {
		ans = i;
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j]) k = i;
			else ++k;
			++j;
		}
		while (i <= k)  i += j - k;
	}
	return s.substr(ans, n / 2);
}

// Palindromes
int l = 0, r = -1;
for (int i = 0; i < n; ++i) {
	int k = (i > r ? 1 : min(d1[l + r - i], r - i));
	while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) ++k;
	d1[i] = k--;
	if (i + k > r) {
		l = i - k;
		r = i + k;
	}
}
l = 0, r = -1;
for (int i = 0; i < n; ++i) {
	int k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1)) + 1;
	while (i + k - 1 < n && i - k >= 0 && s[i + k - 1] == s[i - k]) ++k;
	d2[i] = --k;
	if (i + k - 1 > r) {
		l = i - k;
		r = i + k - 1;
	}
}