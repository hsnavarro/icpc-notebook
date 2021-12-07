// Treap
// Operations in O (log n)

mt19937_64 llrand(random_device{}());

struct node{
    int val, cnt;
    node *r, *l;
    ll pri;
    node(int x) : val(x), cnt(1), pri(llrand()), l(0), r(0) {}
};

struct treap{
    node *root;

    int cnt(node *t) {return t ? t->cnt : 0;}

    void update(node *&t){
        if(!t) return;
        t->cnt = cnt(t->l) + cnt(t->l) + 1;
    }

    node *merge(node *l, node *r){
        if(!l and !r) return nullptr;
        if(!l or !r) return l ? l : r;
        node *t;
        if(l->pri > r->pri) t = l, t->r = merge(l->r, r);
        else t = r, t->l = merge(l, r->l);
        update(t);
        return t;
    }

    pair<node*, node*> split(node *t, int pos){
        if(!t) return {0, 0};
        if(cnt(t->l) < pos){
            auto x = split(t->r, pos - cnt(t->l) - 1);
            t->r = x.first;
            update(t);
            return {t, x.second};
        }

        auto x = split(t->l, pos);
        t->l = x.second;
        update(t);
        return {x.first, t};
    }
};
