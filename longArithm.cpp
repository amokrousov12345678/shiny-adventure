//только сложение и умножение положительных чисел
struct LongNumber { //each digit mod 2*10^9
    static const ll modulo = 1'000'000'000;

    vector<ll> digits;
    LongNumber(ll val) {
        digits.push_back(val % modulo);
        digits.push_back(val / modulo);
        truncate();
    }
    LongNumber(): LongNumber(0) {};

    void truncate() {
        while (digits.size()>1 && digits.back()==0) {
            digits.pop_back();
        }
    }

    friend LongNumber operator+(const LongNumber&a, const LongNumber& b) {
        LongNumber res;
        int resLen = max(a.digits.size(), b.digits.size());
        ll carry = 0;
        res.digits.assign(resLen, 0);
        for (int i=0;i<resLen;i++) {
            ll newRes = (i<a.digits.size() ? a.digits[i] : 0) + (i<b.digits.size() ? b.digits[i] : 0) + carry;
            carry = newRes / modulo;
            newRes %= modulo;
            res.digits[i] = newRes;
        }
        if (carry) {
            res.digits.push_back(carry);
        }
        res.truncate();
        return res;
    }

    LongNumber operator+=(const LongNumber& rhs) {
        *this = *this+rhs;
        return *this;
    }

    friend LongNumber operator*(const LongNumber&a, const LongNumber& b) {
        LongNumber res;
        for (int i=0;i<a.digits.size();i++) {
            for (int j=0;j<b.digits.size();j++) {
                ll mulRes = a.digits[i]*b.digits[j];
                LongNumber addendum(mulRes);
                reverse(addendum.digits.begin(), addendum.digits.end());
                for (int k=0;k<i+j;k++) {
                    addendum.digits.push_back(0);
                }
                reverse(addendum.digits.begin(), addendum.digits.end());
                res += addendum;
            }
        }
        return res;
    }

    LongNumber operator*=(const LongNumber& rhs) {
        *this = (*this)*rhs;
        return *this;
    }

    friend bool operator<(const LongNumber&a, const LongNumber& b) {
        if (a.digits.size() != b.digits.size()) return a.digits.size()<b.digits.size();
        int sz = a.digits.size();
        for (int i=sz-1;i>=0;i--) {
            if (a.digits[i] != b.digits[i]) {
                return a.digits[i] < b.digits[i];
            }
        }
        return false;
    }

    friend bool operator==(const LongNumber& a, const LongNumber& b) {
        return a.digits==b.digits;

    }
    friend bool operator<=(const LongNumber& a, const LongNumber& b) {
        return (a<b) || (a==b);
    }
};