// minimum static convex hull
typedef long long ll;
class Line{
    public:
    ll m , c;
    Line(){}
    Line(ll M , ll C) : m(M) , c(C){}
    ll query(ll x){
        return m*x+c;
    }
};

class Convex_Hull{
    public:
    deque < Line > S;
    int sz;
    void init(){
        S.clear();
        sz=0;
    }
    bool bad(Line L1 , Line L2 , Line L3){
        //(c3 - c1)/(m1 - m3) intersection with first;
        //(c3 - c2)/(m2 - m3) intersection with second
        ll coef1 = (L3.c - L2.c);
        coef1*= (L1.m - L3.m);
        ll coef2=(L3.c - L1.c);
        coef2*=(L2.m - L3.m);
        return coef1<=coef2;
    }
    void addline(Line L){
        while(sz > 1 && bad(S[sz-2] , S[sz-1] , L) ) {
            S.pop_back();
            sz--;
        }
        S.push_back(L);
        sz++;
    }
    ll query(ll x){
        while(sz > 1 && S[0].query(x) >= S[1].query(x) ){
            sz--;
            S.pop_front();
        }
        return S[0].query(x);
    }
};


//////////////////////////////////////////////////////////////////////////////

// maximum divine convex hull

const LL is_query = -(1LL<<62);
struct Line {
    LL m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        LL x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
    }
    void insert_line(LL m, LL b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    LL eval(LL x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};
