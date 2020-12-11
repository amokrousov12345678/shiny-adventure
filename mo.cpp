int sqrtN;
bool cmp(const pair<pair<int,int>,int>& lhs, const pair<pair<int,int>,int>& rhs) {
    int part1 = lhs.first.first/sqrtN;
    int part2 = rhs.first.first/sqrtN;
    if (part1<part2) return false;
    if (part1>part2) return true;
    return lhs.first.second<rhs.first.second;
}

vector<ll> nums_cnt(1000000+7, 0);
ll ans;

void addL(ll val) {
    ans+=2*nums_cnt[val]*val;
    ans+=1*val;
    nums_cnt[val]++;
}

void addR(ll val) {
    ans+=2*nums_cnt[val]*val;
    ans+=1*val;
    nums_cnt[val]++;
}

void delL(ll val) {
    nums_cnt[val]--;
    ans-=2*nums_cnt[val]*val;
    ans-=1*val;

}

void delR(ll val) {
    ans+=2*nums_cnt[val]*val;
    ans+=1*val;
    nums_cnt[val]++;
}

//main
sqrtN = sqrt(n);
vector<ll> a(n);
for (int i=0;i<n;i++) {
    cin >> a[i];
}
vector<pair<pair<int,int>, int>> rq(t);
for (int i=0;i<t;i++) {
    cin >> rq[i].first.first >> rq[i].first.second;
    rq[i].first.first--;
    rq[i].first.second--;
    rq[i].second = i;
}

nums_cnt[a[0]] = 1;
vector<ll> ans_vec(t);
ans = a[0]; //ответ для отрезка [0;0]
sort(rq.begin(), rq.end(), cmp);
int l = 0;
int r = 0;
for (int i=0;i<t;i++) {
    while (l>rq[i].first.first) {
        addL(a[l-1]);
        l--;
    }
    while (r<rq[i].first.second) {
        addR(a[r+1]);
        r++;
    }
    while (l<rq[i].first.first) {
        delL(a[l]);
        l++;
    }
    while (r>rq[i].first.second) {
        delR(a[r]);
        r--;
    }
    ans_vec[rq[i].second] = ans;
}

for (int i=0;i<t;i++) {
    cout << ans_vec[i] << endl;
}