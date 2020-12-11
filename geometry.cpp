struct pt {
        ld x,y;
        pt(ld x, ld y): x(x), y(y) {};
        pt() : pt(0,0) {};
        friend pt operator-(const pt& lhs, const pt& rhs) {
            return {lhs.x-rhs.x, lhs.y-rhs.y};
        }
        friend pt operator+(const pt& lhs, const pt& rhs) {
            return {lhs.x+rhs.x, lhs.y+rhs.y};
        }
        friend pt operator*(const pt& lhs, ld rhs) {
            return {lhs.x*rhs, lhs.y*rhs};
        }
        friend pt operator/(const pt& lhs, ld rhs) {
            return {lhs.x/rhs, lhs.y/rhs};
        }
        ld length() const {
            return sqrt(length2());
        }
        pt normed() const {
            return {x/length(), y/length()};
        }
        ld length2() const {
            return (x*x+y*y);
        }
        friend bool operator==(const pt& lhs, const pt& rhs) {
            return abs(lhs.x-rhs.x)<eps && abs(lhs.y-rhs.y)<eps;
        }
        friend bool operator< (const pt& lhs, const pt & rhs) {
            return lhs.x < rhs.x-eps || (abs(lhs.x - rhs.x) < eps && lhs.y < rhs.y-eps);
        }

        friend ld vp(const pt& lhs, const pt& rhs) {
            return lhs.x * rhs.y - lhs.y * rhs.x;
        }

        friend int rotation(const pt& o, const pt& from, const pt& to) {
            ld Vp = vp(from-o, to-o);
            if (Vp>eps) return 1;
            if (Vp<-eps) return -1;
            return 0;
        }

        friend bool ccw(const pt& lhs, const pt& rhs) {
            return vp(lhs, rhs) < -eps;
        }
    };

    struct line {
        ld a,b,c; //ax+by=c
        line(): a(0), b(0), c(0) {};
        line(pt pt1, pt pt2) {
            if (pt1.x==0 && pt2.x==0 && pt1.y==0 && pt2.y==0) {
                pt1.x+=1;
            }
            ld det = pt1.x*pt2.y-pt1.y*pt2.x;
            if (abs(det)<eps) {
                if (abs(pt1.x)<eps && abs(pt1.y)<eps) swap(pt1, pt2);
                a = pt1.y;
                b = -pt1.x;
                c = 0;
            } else {
                a = (pt2.y-pt1.y);
                b = (pt1.x-pt2.x);
                c = det;
            }
        }

        ld sgnDistPt(const pt& p) const {
            ld dist = (a*p.x+b*p.y-c)/sqrt(a*a+b*b);
            return dist;
        }

        ld distPt(const pt& p) const {
            return abs(sgnDistPt(p));
        }

        bool contains(const pt& p) const {
            return distPt(p) < eps;
        }
    };

    struct seg {
        line l;
        pt pt1, pt2;
        //инициализация отрезка по двум точкам
        seg(pt pt1, pt pt2) : pt1(pt1), pt2(pt2), l(pt1, pt2) {}
        bool contains(const pt& p) const {
            return p.x>=min(pt1.x, pt2.x)-eps && p.x<=max(pt1.x, pt2.x)+eps
                && p.y>=min(pt1.y, pt2.y)-eps && p.y<=max(pt1.y, pt2.y)+eps && l.contains(p);
        }
        ld sgnDistPt(const pt& p) const {
            ld dist = l.distPt(p);
            pt pt_min_dist = p-pt(l.a,l.b)*(dist/sqrt(l.a*l.a+l.b*l.b));
            if (contains(pt_min_dist)) {
                return abs(dist);
            } else {
                return min((p-pt1).length(), (p-pt2).length());
            }
        }
        ld distPt(const pt& p) const {
            return abs(sgnDistPt(p));
        }
    };

    struct CollData {
        bool isInf = false;
        vector<pt> pnts;

        CollData(const vector<pt>& pnts): isInf(false), pnts(pnts) {};
        CollData(): isInf(true) {};
    };

    CollData inters(const line& l1, const line& l2) {
        ld det = l1.a*l2.b-l1.b*l2.a;
        if (abs(det)<eps) {
            ld det1 = l1.a*l2.c-l1.c*l2.a;
            ld det2 = l1.b*l2.c-l1.c*l2.b;
            if (abs(det1)<eps && abs(det2)<eps) {
                return CollData();
            } else {
                return CollData(vector<pt>{});
            }
        } else {
            pt res;
            res.x = (l1.c*l2.b-l1.b*l2.c)/det;
            res.y = (l1.a*l2.c-l1.c*l2.a)/det;
            return CollData(vector<pt>{res});
        }
    }

    CollData inters(const seg& s1, const seg& s2) { //no INF inters
        auto collLines = inters(s1.l, s2.l);
        if (collLines.isInf) {
            auto a = s1.pt1;
            auto b = s1.pt2;
            auto c = s2.pt1;
            auto d = s2.pt2;
            if (b < a)  swap(a, b);
            if (d < c)  swap(c, d);
            auto left = max(a, c);
            auto right = min(b, d);
            if (right<left) {
                return CollData(vector<pt>{});
            } else if (left==right) {
                return CollData(vector<pt>{left});
            } else {
                return CollData(vector<pt>{left, right});
            }
        }
        vector<pt> res;
        for (auto& it: collLines.pnts) {
            if (s1.contains(it) && s2.contains(it)) {
                res.push_back(it);
            }
        }
        return CollData(res);
    }

    struct circle {
        pt center;
        ld r;
    };

    CollData inters(const circle& c, const line& l) { //no INF inters
        ld d = l.sgnDistPt(c.center);
        ld abs_d = abs(d);
        if (abs_d>c.r+eps) {
            return CollData(vector<pt>{});
        }
        pt proj = c.center - (pt(l.a,l.b).normed())*d;
        if (abs(abs_d-c.r)<eps) {
            return CollData(vector<pt>{proj});
        }
        ld left = sqrt(c.r*c.r-abs_d*abs_d);
        pt delta = pt(l.b,-l.a).normed()*left;
        return CollData(vector<pt>{proj-delta, proj+delta});
    }

    CollData inters(const circle& c1, const circle& c2) {
        if (c1.center == c2.center) {
            if (abs(c1.r-c2.r)<eps) {
                return CollData();
            } else {
                return CollData(vector<pt>{});
            }
        }
        pt c_2 = c2.center-c1.center;
        line l;
        l.a = -2*c_2.x;
        l.b = -2*c_2.y;
        l.c = -(c_2.x*c_2.x + c_2.y*c_2.y + c1.r*c1.r - c2.r*c2.r);
        circle c_1 = {pt{0,0}, c1.r};
        auto res = inters(c_1, l);
        //assert(!res.isInf);
        for (auto& it: res.pnts) {
            it=it+c1.center;
        }
        return CollData(res.pnts);
    }
