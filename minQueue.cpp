template<typename T>
struct MinStack {
    T inf;
    MinStack(T inf): inf(inf) {};

    vector<pair<T,T>> s;
    T getMin() { //only non empty
        if (s.empty()) {
            return inf;
        }
        return s.back().second;
    }
    void pop() {
        s.pop_back();
    }
    void push(T val) {
        s.push_back({val, min(val, s.empty() ? inf : s.back().second)});
    }
    T top() {
        return s.back().first;
    }
    bool empty() {
        return s.empty();
    }
};

template<typename T>
struct MinQueue {
    T inf;
    MinStack<T> s1, s2;
    MinQueue(T inf): inf(inf), s1(inf), s2(inf) {};

    T getMin() {
        T res = inf;
        if (!s1.empty()) {
            res = min(res, s1.getMin());
        }
        if (!s2.empty()) {
            res = min(res, s2.getMin());
        }
        return res;
    }
    void push(T val) {
        s1.push(val);
    }
    void pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                T tmp = s1.top();
                s2.push(tmp);
                s1.pop();
            }
        }
        s2.pop();
    }
};