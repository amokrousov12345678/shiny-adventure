//persistent. Or if setVal<persist=false>, just segtree on pointers (for sparse segtree)
template <typename T_>
struct RMQPersistent {
    using T = T_;

    struct Node {
        Node *l = nullptr, *r = nullptr;
        T val;
        Node(T val): val(val) {};
        Node(const Node& rhs): l(rhs.l), r(rhs.r), val(rhs.val) {};
    };

    ll size;
    Node* root;

    T neutral;
    std::function<T(const T&,const T&)> op;

    RMQPersistent(ll size, std::function<T(const T&,const T&)> op, T neutral) {
        this->neutral = neutral;
        ll deg2 = 1;
        while (deg2<size) {
            deg2<<=1;
        }
        this->size = deg2;
        this->op = op;
        this->root = new Node(neutral);
    }

    void mkL(Node* root) {
        if (!(root->l)) {
            root->l = new Node(neutral);
        }
    }
    void mkR(Node* root) {
        if (!(root->r)) {
            root->r = new Node(neutral);
        }
    }

    void push(Node* root, bool isLeaf) {
        if (!isLeaf) {
            mkL(root);
            mkR(root);
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