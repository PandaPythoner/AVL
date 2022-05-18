#ifndef AVL_AVL_H
#define AVL_AVL_H
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


template<class Key>
class AVL{
public:

    static int max(int a, int b){
        if(a < b){
            return b;
        }
        return a;
    }

    template<class NodeKey>
    class node{
    public:

        typedef node* pnode;

        NodeKey key;
        pnode l = nullptr;
        pnode r = nullptr;
        int h = 1;

        node(const NodeKey &key) : key(key), l(nullptr), r(nullptr), h(1) {

        }


        int get_height_slow(){
            int res = 1;
            if(l != nullptr){
                if(l->key > key){
                    // throw "Bebra...";
                }
                res = max(res, l->get_height_slow() + 1);
            }
            if(r != nullptr) {
                if(key > r->key){
                    //  "Bebra...";
                }
                res = max(res, r->get_height_slow() + 1);
            }
            return res;
        }


        int get_height(const pnode &p){
            if(p == nullptr){
                return 0;
            }
            return p->h;
        }


        inline int get_left_height(){
            return get_height(l);
        }


        inline int get_right_height(){
            return get_height(r);
        }


        void update(){
            h = max(get_left_height(), get_right_height()) + 1;
        }




    };

    typedef node<Key>* pnode;


    pnode rotate_right(pnode y){
        pnode x = y->l;
        y->l = x->r;
        x->r = y;
        y->update();
        x->update();
        return x;
    }


    pnode rotate_left(pnode x){
        pnode y = x->r;
        x->r = y->l;
        y->l = x;
        x->update();
        y->update();
        return y;
    }


    std::string print_tree_tex(pnode v){
        if(v == nullptr){
            return "nil";
        }
        return std::to_string(v->key) + ", " + print_tree_tex(v->l) + ", " + print_tree_tex(v->r);
    }


    void print_tree_tex(){
        std::cout << "\\begin{center}" << "\n";
        std::cout << "\\begin{asy}" << "\n";
        std::cout << "import binarytree;" << "\n";
        std::string bt = "bt";
        std::string pc = "pic";
        std::cout << "picture " << pc << ";" << "\n";
        std::cout << "binarytree " << bt << " = " << "binarytree(" << print_tree_tex(root) << ");" << "\n";
        std::cout << "draw(" << pc << ", " << bt << ", condensed=true);" << "\n";
        std::cout << "add(" << pc << ".fit(), (0, 0), 10N);" << "\n";
        std::cout << "\\end{asy}" << "\n";
        std::cout << "\\end{center}" << "\n";
    }


    pnode balance(pnode v, bool prnt = false){
        int lh = v->get_left_height();
        int rh = v->get_right_height();
        int balance = (lh - rh);
        if(lh + 2 == rh){
            if(v->r->get_left_height() > v->r->get_right_height()){
                v->r = rotate_right(v->r);
                v->update();
            }
            auto rs = rotate_left(v);
            if(prnt){
                print_tree_tex();
            }
            return rs;
        } else if(lh == rh + 2){
            if(v->l->get_left_height() < v->l->get_right_height()){
                v->l = rotate_left(v->l);
                v->update();
            }
            auto rs = rotate_right(v);
            if(prnt){
                print_tree_tex();
            }
            return rs;
        }
        return v;
    }


    pnode find(pnode v, const Key &key){
        while(v != nullptr && v->key != key){
            if(key < v->key){
                v = v->l;
            } else{
                v = v->r;
            }
        }
        return v;
    }


    pnode find_min(pnode v){
        while(v != nullptr && v->l != nullptr){
            v = v->l;
        }
        return v;
    }


    std::pair<pnode, pnode> delete_min(pnode v){
        if(v == nullptr){
            return std::make_pair(v, v);
        }
        if(v->l == nullptr){
            auto vr = v->r;
            v->r = nullptr;
            v->update();
            return std::make_pair(vr, v);
        }
        auto x = delete_min(v->l);
        v->l = x.first;
        v->update();
        v = balance(v);
        x.first = v;
        return x;
    }


    std::pair<pnode, pnode> delete_by_key(pnode v, const Key &key){
        if(v == nullptr){
            return std::make_pair(v, v);
        }
        if(v->key > key){
            auto x = delete_by_key(v->l, key);
            v->l = x.first;
            v->update();
            x.first = balance(v);
            return x;
        }
        if(v->key < key){
            auto x = delete_by_key(v->r, key);
            v->r = x.first;
            v->update();
            x.first = balance(v);
            return x;
        }
        auto vl = v->l;
        auto vr = v->r;
        v->l = nullptr;
        v->r = nullptr;
        if(vr == nullptr){
            return std::make_pair(vl, v);
        }
        auto x = delete_min(vr);
        auto u = x.second;
        u->l = vl;
        u->r = x.first;
        u->update();
        u = balance(u);
        return std::make_pair(u, v);
    }



    int to_strings(pnode v, std::vector<std::string> &res, std::string (*to_string)(Key)){
        res.clear();
        if(v == nullptr){
            res = {"   "};
            return 0;
        }
        if(v->l == nullptr && v->r == nullptr){
            res.push_back(to_string(v->key));
            res[0].push_back(' ');
            res[0].push_back(' ');
            res[0].push_back(' ');
            return 0;
        }
        std::vector<std::string> x, y;
        int i = to_strings(v->l, x, to_string);
        int j = to_strings(v->r, y, to_string);
        j += x[0].size();
        while(x.size() < y.size()){
            x.push_back("");
            while(x.back().size() < x[x.size() - 2].size()){
                x.back().push_back(' ');
            }
        }
        while(y.size() < x.size()){
            y.push_back("");
            while(y.back().size() < y[y.size() - 2].size()){
                y.back().push_back(' ');
            }
        }
        int sz = x[0].size() + y[0].size();
        while(i + 1 < j){
            res.push_back("");
            for(int c = 0; c < sz; ++c){
                if(c == i && v->l != nullptr){
                    res.back().push_back('/');
                } else if(c == j && v->r != nullptr){
                    res.back().push_back('\\');
                } else{
                    res.back().push_back(' ');
                }
            }
            i += 1;
            j -= 1;
        }
        std::string a = to_string(v->key);
        res.push_back("");
        for(int c = 0; c < i; ++c){
            res.back().push_back(' ');
        }
        for(int c = 0; c < a.size(); ++c){
            res.back().push_back(a[c]);
        }
        res.back().push_back(' ');
        sz = max(sz, res.back().size());
        reverse(res.begin(), res.end());
        for(int c = 0; c < x.size(); ++c){
            res.push_back(x[c] + y[c]);
        }
        for(int c = 0; c < res.size(); ++c){
            res[c].resize(sz, ' ');
        }
        return i;
    }




    pnode root = nullptr;


    pnode insert(pnode v, pnode d){
        if(v == nullptr){
            return d;
        }
        if(v->key <= d->key){
            v->r = insert(v->r, d);
            v->update();
            return balance(v);
        } else{
            v->l = insert(v->l, d);
            v->update();
            return balance(v);
        }
    }


    void print_insert(const Key &k){
        print_tree_tex();
        pnode v = root;
        std::vector<pnode> a;
        std::vector<int> x;
        while(1){
            a.push_back(v);
            if(v->key <= k){
                x.push_back(1);
                if(v->r == nullptr){
                    v->r = new node<Key>(k);
                    break;
                }
                v = v->r;
            } else{
                x.push_back(0);
                if(v->l == nullptr){
                    v->l = new node<Key>(k);
                    break;
                }
                v = v->l;
            }
        }
        while(!a.empty()){
            v = a.back();
            a.pop_back();
            x.pop_back();
            v->update();
            v = balance(v);
            if(!a.empty()){
                if(x.back() == 0){
                    a.back()->l = v;
                } else{
                    a.back()->r = v;
                }
            } else{
                root = v;
            }
            print_tree_tex();
        }

    }


    void insert(const Key &k){
        pnode v = new node<Key>(k);
        root = insert(root, v);
    }


    int checkout_height(){
        if(root == nullptr) {
            return 0;
        }
        return root->get_height_slow();
    }


    pnode find(const Key &key){
        return find(root, key);
    }


    pnode find_min(){
        return find_min(root);
    }


    void delete_min(){
        auto x = delete_min(root);
        root = x.first;
        if(x.second != nullptr){
            delete x.second;
        }
    }


    void delete_by_key(const Key &key){
        auto x = delete_by_key(root, key);
        root = x.first;
        if(x.second != nullptr){
            delete x.second;
        }
    }

};

template<class T>
std::ostream& operator<<(std::ostream &out, AVL<T> &a){
    std::vector<std::string> s;
    a.to_strings(a.root, s, std::to_string);
    for(auto &x: s){
        out << x << "\n";
    }
    return out;
}


#endif //AVL_AVL_H
