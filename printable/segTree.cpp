template <typename T_>
    struct RMQ {
        using T = T_;
        using PushT = None;
        vector<T> mas;
        T neutral;
        int size;
        std::function<T(const T&,const T&)> op;

        RMQ(int size, std::function<T(const T&,const T&)> op, T neutral) {
            this->neutral = neutral;
            int deg2 = 1;
            while (deg2<size) {
                deg2<<=1;
            }
            this->size = deg2;

            this->op = op;
            mas.assign(2*this->size, neutral);
        }

        void setVal(int ind, T val) {modify(ind,val);};//for compatibility for HLD
        T getVal(int ind) {
            return query(ind, ind);
        }
        void modify(int ind, T val) {
            ind += this->size;
            mas[ind] = val;
            for (ind >>= 1; ind >0 ;ind>>=1) mas[ind] = this->op(mas[ind << 1], mas[(ind<<1)+1]);
        }

        T query(int l, int r) {
            if (l>r) return this->neutral;
            l+=size; r+=size;
            T ans;
            if (l==r) {
                ans = mas[l];
            } else {
                ans = this->op(mas[l], mas[r]);
            }
            for (; l<r; l>>=1, r>>=1) {
                if ((l & 1) == 0 && (l + 1) < r) ans = this->op(ans, mas[l + 1]);
                if ((r & 1) == 1 && (r - 1) > l) ans = this->op(ans, mas[r - 1]);
            }
            return ans;
        }

    };