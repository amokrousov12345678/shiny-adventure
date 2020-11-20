struct IInt {
          int val;
          IInt(int val): val(val) {};
          operator int() {
              return val;
          }
          IInt operator-=(int val) {
              this->val -= val;
              return *this;
          }
          friend bool operator<(const IInt& l, const IInt& r) {
              return l.val<r.val;
          }
    };

    template<typename Key, typename Value=None, typename Less=std::less<Key>>
    struct Treap {
        #define IsImplicitTreap std::is_same<Key, IInt>::value

        struct Node {
            Node *left = nullptr;
            Node *right = nullptr;
            int y = rand();
            Key x;
            Value val, sVal;
            int sz = 1;
            Node(Key x, Value val): x(x), val(val), sVal(val) {};
        };
        std::function<Value(const Value&, const Value&)> op;
        Value neutral;
        Node* root = nullptr;

        Treap(std::function<Value(const Value&, const Value&)> op, Value neutral, Node* root = nullptr): op(op), neutral(neutral), root(root) {};

        int getSz(Node* node) {
            return node ? node->sz : 0;
        }

        Value getSval(Node* node) {
            return node ? node->sVal : neutral;
        }

        void fix(Node* node) {
            assert(node);
            node->sz = 1 + getSz(node->left) + getSz(node->right);
            node->sVal = op(op(getSval(node->left), node->val), getSval(node->right));
        }


        template<typename Value_=Value>
        typename std::enable_if<!IsImplicitTreap, Value_>::type getVertValue(Node* root) {
            return root->x;
        }

        template<typename Value_=Value>
        typename std::enable_if<IsImplicitTreap, Value_>::type getVertValue(Node* root) {
            return getSz(root->left);
        }

        template<bool LessWithEq = false>
        pair<Node*, Node*> split(Node* root, Key key) {
            if (!root) return {nullptr, nullptr};
            auto rootVal = getVertValue(root);
            if (Less()(rootVal, key) || (LessWithEq && rootVal == key)) {
                if (IsImplicitTreap) key -= rootVal+1;
                auto p = split<LessWithEq>(root->right, key);
                root->right = p.first;
                fix(root);
                return {root, p.second};
            } else {
                auto p = split<LessWithEq>(root->left, key);
                root->left = p.second;
                fix(root);
                return {p.first, root};
            }
        }

        Node* merge(Node* root1, Node* root2) {
            if (!root1) return root2;
            if (!root2) return root1;
            if (root1->y>root2->y) {
                root1->right = merge(root1->right, root2);
                fix(root1);
                return root1;
            } else {
                root2->left = merge(root1, root2->left);
                fix(root2);
                return root2;
            }
        }

        Node* insert(Node* root, Key key, Value value = {}) {
            Node* tmp = new Node(key, value);
            auto p = split<false>(root, key);
            Node* new_root = p.first;
            new_root = merge(new_root, tmp);
            new_root = merge(new_root, p.second);
            return new_root;
        }

        Node* erase(Node* root, Key key) {
            auto p = split<false>(root, key);
            if (IsImplicitTreap) key = 0;
            auto p1 = split<true>(p.second, key);
            p1.first = merge(p1.first->left, p1.first->right); //=0 to remove ALL entries
            Node* tmp_ans = p.first;
            tmp_ans = merge(tmp_ans, p1.first);
            tmp_ans = merge(tmp_ans, p1.second);
            return tmp_ans;
        }

        int size() {
            return getSz(root);
        }

        void insert(Key key, Value value) {
            root = insert(root, key, value);
        }

        void erase(Key key) {
            root = erase(root, key);
        }

        Value queryAll() {
            return getSval(root);
        }

        Value query(Key keyL, Key keyR) {
            auto p = split<false>(root, keyL);
            if (IsImplicitTreap) keyR -= keyL;
            auto p1 = split<true>(p.second, keyR);
            auto res = getSval(p1.first);
            root = merge(p.first, merge(p1.first, p1.second));
            return res;
        }

        Treap& operator=(Treap&& rhs) noexcept {
            this->root = rhs.root;
            this->op = rhs.op;
            this->neutral = rhs.neutral;
            rhs.root = nullptr;
            return *this;
        }

        Treap(Treap &&rhs) {
            *this = std::move(rhs);
        }

        template<bool LessWithEq = false>
        static pair<Treap, Treap> split(Treap&& treap, Key key) {
            auto res = treap.split<LessWithEq>(treap.root, key);
            treap.root = nullptr;
            return make_pair(Treap(treap.op, treap.neutral, res.first), Treap(treap.op, treap.neutral, res.second));
        }

        static Treap merge(Treap&& l, Treap&& r) {
            auto res = l.merge(l.root, r.root);
            l.root = nullptr;
            r.root = nullptr;
            return Treap(l.op, l.neutral, res);
        }
    };