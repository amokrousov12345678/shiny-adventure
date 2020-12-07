template <typename T_, typename PushT_ = None>
struct RMQPersistent {
    using T = T_;
    using PushT = PushT_;

    struct Node {
        Node *l = nullptr, *r = nullptr;
        T val;
        PushT pushVal;
        Node(T val, PushT pushVal): val(val), pushVal(pushVal) {};
        Node(const Node& rhs): l(rhs.l), r(rhs.r), val(rhs.val), pushVal(rhs.pushVal) {};
    };

    ll size;
    Node* root;

    T neutral;
    std::function<T(const T&,const T&)> op;

    vector<PushT> masPush;
    PushT neutralPush;
    std::function<pair<PushT, PushT>(const PushT&)> opPush; //calc what to push to children
    std::function<void(PushT&, T&)> opApply; //apply change in vertex
    std::function<PushT(const PushT&, const PushT&)> opPendingCompose; //compose two pending ops

    RMQPersistent(ll size, std::function<T(const T&,const T&)> op, T neutral,
                  std::function<pair<PushT, PushT>(const PushT&)> opPush = [](const PushT& p) {return make_pair(p,p);},
                  PushT neutralPush = PushT(),
                  std::function<void(PushT&, T&)> opApply = [](PushT& _1, T& p2){},
                  std::function<PushT(const PushT&, const PushT&)> opPendingCompose = [](const PushT& _1, const PushT& _2){return _2;}) {
        this->neutral = neutral;

        ll deg2 = 1;
        while (deg2<size) {
            deg2<<=1;
        }
        this->size = deg2;

        this->op = op;
        this->opPush = opPush;
        this->opApply = opApply;
        this->opPendingCompose = opPendingCompose;
        this->neutralPush = neutralPush;

        this->root = new Node(neutral, neutralPush);
    }

    void mkL(Node* root) {
        if (!(root->l)) {
            root->l = new Node(neutral, neutralPush);
        }
    }
    void mkR(Node* root) {
        if (!(root->r)) {
            root->r = new Node(neutral, neutralPush);
        }
    }
    template<bool persist = true>
    void setVal(int pos, T val) {
        root = setValImpl<persist>(pos, val, 0, size-1, root);
    }

    T getVal(int pos) {
        return query(pos, pos);
    }
    template<bool persist = true>
    Node* setValImpl(int pos, T val, int l, int r, Node* root) {
        push(root, l==r);
        if (l==r && r==pos) {
            Node* newRoot = persist ? new Node(*root) : root;
            newRoot->val = val;
            return newRoot;
        }
        if (l>pos || r< pos) return root;
        int m = (l+r)/2;
        Node* newRoot = persist ? new Node(*root) : root;
        newRoot->l = setValImpl<persist>(pos, val, l, m, newRoot->l);
        newRoot->r = setValImpl<persist>(pos, val, m+1, r, newRoot->r);
        newRoot->val = op(newRoot->l->val, newRoot->r->val);
        return newRoot;
    }

    /*void modify(int l, int r, PushT d) {
        assert(false);//групповые операции нифига не работают, но не на чем протестить
        root = modifyImpl(l, r, d, 0, size-1, root);
    }*/

    void push(Node* root, bool isLeaf) {
        if (!isLeaf) {
            auto p = opPush(root->pushVal);
            mkL(root); mkR(root);
            //works bad :(
            root->l->pushVal = opPendingCompose(root->l->pushVal, p.first);
            root->r->pushVal = opPendingCompose(root->r->pushVal, p.second);
        }
        opApply(root->pushVal, root->val);
    }

    /*Node* modifyImpl(int rq_l, int rq_r, ll d, int l, int r, Node* root){
        push(root, l==r);
        if (rq_l>r || l>rq_r) return root;
        if (rq_l<=l && r<=rq_r) {
            Node* newRoot = new Node(*root);
            newRoot->pushVal = opPendingCompose(newRoot->pushVal, d);
            push(newRoot, l==r);
            return newRoot;
        }
        int m = (l+r)/2;
        Node* newRoot = new Node(*root);
        newRoot->l = modifyImpl(rq_l, rq_r, d, l, m, newRoot->l);
        newRoot->r = modifyImpl(rq_l, rq_r, d, m+1, r, newRoot->r);
        newRoot->val = op(newRoot->l->val, newRoot->r->val);
        return newRoot;
    }*/

    T query(int l, int r) {
        return queryImpl(l, r, 0, size-1, root);
    }

    T queryImpl(int rq_l, int rq_r, int l, int r, Node* root) {
        push(root, l==r);

        if (rq_l>r || l>rq_r) return neutral;
        if (rq_l<=l && r<=rq_r) {
            return root->val;
        }
        int m = (l+r)/2;
        T ans1 = queryImpl(rq_l, rq_r, l, m, root->l);
        T ans2 = queryImpl(rq_l, rq_r, m+1, r, root->r);
        return op(ans1, ans2);
    }
};