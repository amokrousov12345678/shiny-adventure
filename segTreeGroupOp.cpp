//T - тип данных, PushT - тип значения, которое проталкивается групповой операцией
//opPush - получить пару, что нужно столкнуть в потомков из данной вершины из данной
//opApply - применить к вершине записанное в неё значение (и обнулить проталкивание ручками)
//opPendingCompose - стакнуть отложенную операцию

//дерево отрезков по минимуму с прибавлением на отрезке
RMQ<int, int> rmq(cntY, [] (const int& a, const int&b) {return min(a,b);}, INF,
            [] (const int& a) {return pair<int,int>(a,a);}, 0,
            [] (int& pushed, int& val) {val+=pushed; pushed = 0;},
            [] (const int& app1, const int& app2) {return app1+app2;});


//лямбды довольно тупят (спокойно могут делать +35% времени работы), поэтому возможно придется выдергивать содержимое лямбд как методы в классе
//(что не позволит 2 разных дерева отрезков разных видов адекватно использовать)
template <typename T_, typename PushT_>
struct RMQ {
    using T = T_;
    using PushT = PushT_;
    vector<T> mas;
    T neutral;
    int size;
    std::function<T(const T&,const T&)> op;

    vector<PushT> masPush;
    PushT neutralPush;
    std::function<pair<PushT, PushT>(const PushT&)> opPush; //calc what to push to children
    std::function<void(PushT&, T&)> opApply; //apply change in vertex
    std::function<PushT(const PushT&, const PushT&)> opPendingCompose; //compose two pending ops

    RMQ(int size, std::function<T(const T&,const T&)> op, T neutral,
        std::function<pair<PushT, PushT>(const PushT&)> opPush, PushT neutralPush,
        std::function<void(PushT&, T&)> opApply,
        std::function<PushT(const PushT&, const PushT&)> opPendingCompose) {
        this->neutral = neutral;

        int deg2 = 1;
        while (deg2<size) {
            deg2<<=1;
        }
        this->size = deg2;

        this->op = op;
        mas.assign(2*this->size, neutral);
        this->opPush = opPush;
        this->opApply = opApply;
        this->opPendingCompose = opPendingCompose;
        this->neutralPush = neutralPush;
        masPush.assign(2*this->size, neutralPush);
    }

    void setVal(int pos, T val) {
        setValImpl(pos, val, 0, size-1,1);
    }

    T getVal(int pos) {
        return query(pos, pos);
    }
    
    void setValImpl(int pos, T val, int l, int r, int v) {
        if (l==r && r==pos) {
            mas[v] = val;
            return;
        }
        if (l>pos || r< pos) return;
        int m = (l+r)/2;
        setValImpl(pos, val, l, m, 2*v);
        setValImpl(pos, val, m+1, r, 2*v+1);
        mas[v] = op(mas[2*v], mas[2*v+1]);
    }

    void modify(int l, int r, PushT d) {
        modifyImpl(l, r, d, 0, size-1, 1);
    }

    void push(int v, bool isLeaf) {
        if (!isLeaf) {
            auto p = opPush(masPush[v]);
            masPush[2*v] = opPendingCompose(masPush[2*v], p.first);
            masPush[2*v+1] = opPendingCompose(masPush[2*v+1], p.second);
        }
        opApply(masPush[v], mas[v]);
    }

    void modifyImpl(int rq_l, int rq_r, ll d, int l, int r, int v){
        push(v, l==r);
        if (rq_l>r || l>rq_r) return;
        if (rq_l<=l && r<=rq_r) {
            masPush[v] = opPendingCompose(masPush[v], d);
            push(v, l==r);
            return;
        }
        int m = (l+r)/2;
        modifyImpl(rq_l, rq_r, d, l, m, 2*v);
        modifyImpl(rq_l, rq_r, d, m+1, r, 2*v+1);
        mas[v] = op(mas[2*v], mas[2*v+1]);
    }

    T query(int l, int r) {
        return queryImpl(l, r, 0, size-1, 1);
    }

    T queryImpl(int rq_l, int rq_r, int l, int r, int v) {
        push(v, l==r);

        if (rq_l>r || l>rq_r) return neutral;
        if (rq_l<=l && r<=rq_r) {
            return mas[v];
        }
        int m = (l+r)/2;
        T ans1 = queryImpl(rq_l, rq_r, l, m, 2*v);
        T ans2 = queryImpl(rq_l, rq_r, m+1, r, 2*v+1);
        return op(ans1, ans2);
    }
};