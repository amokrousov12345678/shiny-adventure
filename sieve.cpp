//находит простые числа с отрезка (в массиве primes должны быть все простые до sqrt(r))
//массив sieve2 будет сдвинут, что элементу l соответствует 0 элемент массива. Асимптотика (r-l)*loglog (r-l)
void calcPrimes(ll l, ll r) {
    for (auto& prime: primes) {
        ll minCoeff = divRoundUp(l, prime);
        ll maxCoeff = divRoundDown(r, prime);
        minCoeff = max(minCoeff, 2ll);
        for (ll i=minCoeff;i<=maxCoeff;i++) {
            sieve2[i*prime-l] = 1;
        }
    }
}

//тупое решето (n*loglogn)
for (int i=2;i*i<SQRT_MAXN;i++) {
    if (sieve[i]) continue;
    for (int j=2*i;j<SQRT_MAXN;j+=i) {
        sieve[j] = 1;
    }
}
for (int i=2;i<SQRT_MAXN;i++) {
    if (!sieve[i]) {
        primes.push_back(i);
    }
}

//лин. решето с факторизацией( может пашет а может нет)
int lp[maxn];
vector<ll> primes;


for (int i=2; i<maxn; ++i) {
    if (lp[i] == 0) {
        lp[i] = i;
        primes.push_back(i);
    }
    for (int j = 0; j < (int) primes.size() && primes[j] <= lp[i] && i * primes[j] < maxn; ++j)
        lp[i * primes[j]] = primes[j];
}

//вычисление функции мебиуса по решету ((-1)^cntPrimes если число свободно от квадратов, иначе 0)

int mu[maxn];

mu[1] = 1;
for (int i=2;i<maxn;i++) {
    ll pred = i/lp[i];
    if (pred % lp[i]) {
        mu[i] = -mu[pred];
    } else {
        mu[i] = 0;
    }
}