// Treap
// Operations in O (log n)

mt19937_64 llrand(random_device{}());

struct Node {
    int val, cnt;
    Node *r, *l;
    ll pri;
    Node(int x) : val(x), cnt(1), pri(llrand()), l(0), r(0) {}
};

struct Treap {
    Node *root;

    int cnt(Node *t) {return t ? t->cnt : 0;}

    void update(Node *&t){
        if(!t) return;
        t->cnt = cnt(t->l) + cnt(t->l) + 1;
    }

    Node *merge(Node *l, Node *r){
        if(!l and !r) return nullptr;
        if(!l or !r) return l ? l : r;
        Node *t;
        if(l->pri > r->pri) t = l, t->r = merge(l->r, r);
        else t = r, t->l = merge(l, r->l);
        update(t);
        return t;
    }

    pair<Node*, Node*> split(Node *t, int pos){
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
