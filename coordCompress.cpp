//CoordComp<dataType>
//add - добавить ссылки на места, где лежат сжимаемые значения
//exec - заменит значения на пожатые, когда всё добавили
//revert - дергать когда обратную замену

template <typename T>
struct CoordComp {
    vector<T> s;
    unordered_map<T, int> m;
    vector<T> back;
    std::vector<T*> poses;

    void add(T& val) {
        poses.push_back(&val);
        s.push_back(val);
    }

    int exec() {
        std::sort(begin(s), end(s));
        s.erase(std::unique(begin(s), end(s)), end(s));
        back.swap(s);
        for (int i=0;i<back.size();i++) {
            m[back[i]] = i;
        }
        for (auto& it: poses) {
            auto& val = *it;
            val = m[val];
        }
        return back.size();
    }

    T revert(int val) {
        return back[val];
    }

    //if you don't want in-place modification
    void addVal(T val) {
        s.push_back(val);
    }

    int compress(T val) {
        return m[val];
    }
};