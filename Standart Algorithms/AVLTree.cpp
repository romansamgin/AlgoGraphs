#include <iostream>

using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

//добавить шаблонность, функции разрезания/склеивания поддеревьев
class BST {
private:
    struct Node {
        int key;
        int height;      //высота поддерева
        long long sum;         //сумма эл-ов поддерева
        Node* left;
        Node* right;

        Node(long long k) :
            key(k), height(1), sum(k), left(nullptr), right(nullptr)
        {
        }
    };

    int height(Node* s) {
        return s ? s->height : 0;
    }

    int height_diff(Node* s) {
        return height(s->right) - height(s->left);
    }

    void new_height(Node*& s) {
        s->height = max(height(s->left), height(s->right)) + 1;
    }


    void new_sum(Node*& s) {
        long long left = 0, right = 0;
        if (s->left) {
            left = s->left->sum;
        }
        if (s->right) {
            right = s->right->sum;
        }
        s->sum = left + right + s->key;
    }

    Node* findmin(Node* s) {
        return s->left ? findmin(s->left) : s;
    }

    //InOrder обход
    void showR(Node* s) const {        
        if (s) {
            showR(s->left);
            cout << s->key << ' ';
            showR(s->right);
        }     
    }
    
    //заменить pair на структуру с понятными именами полей 
    pair<Node*, Node*> find_with_parent(int key) const {
        Node* cur = head;
        Node* parrent = nullptr;

        while (cur != nullptr) {
            if (key < cur->key) {
                parrent = cur;
                cur = cur->left;
            }
            else if (key > cur->key) {
                parrent = cur;
                cur = cur->right;
            }
            else {
                break;
            }
        }

        return { cur, parrent };
    }


    void insertR(Node*& s, int key) {
        if (!s) {
            s = new Node(key);
            N++;
            return;
        }
        else if (key < s->key) {
            insertR(s->left, key);
        }
        else if (key > s->key) {
           insertR(s->right, key);
        }
        else {
            return;
        }
        balance(s);
    }

    //Для L - те что меньше l
    long long sum_L(Node* s, int key) const {
        Node* cur = s;
        Node* parrent = s;
        long long sum = 0;
        while (cur != nullptr) {           
            if (key < cur->key) {
                cur = cur->left;
            }
            else if (key > cur->key) {
                parrent = cur;

                if (cur->left) {
                    sum += cur->left->sum;
                }
                sum += cur->key;
                cur = cur->right;
            }
            else {
                break;
            }
        }

        if (cur && cur->left) {
            sum += cur->left->sum;
        }
        return sum;
    }


    //Для R - те что больше r
    long long sum_R(Node* s, int key) const {
        Node* cur = s;
        Node* parrent = s;
        long long sum = 0;
        while (cur != nullptr) {
            if (key < cur->key) {               
                parrent = cur;
                if (cur->right) {
                    sum += cur->right->sum;
                }
                sum += cur->key;
                cur = cur->left;
            }
            else if (key > cur->key) {   
                cur = cur->right;
            }
            else {
                break;
            }
        }

        if (cur && cur->right) {
            sum += cur->right->sum;
        }
        return sum;
    }


    //Наименьший общий предок
    Node* LCA(int l, int r) const {
        Node* lca = head;
        while (lca && !(l <= lca->key && r >= lca->key)) {
            if (l < lca->key) {
                lca = lca->left;         
            }
            else {
                lca = lca->right;
            }
        }
        return lca;
    }



    void removemin(Node*& s) {
        if (!(s->left)) {
            s = s->right;
            return;
        }          
        removemin(s->left);
        balance(s);
    }


    void removeR(Node*& s, int key) {
        if (!s) {
            return;
        }
        if (key < s->key) {
            removeR(s->left, key);
        }
        else if (key > s->key) {
            removeR(s->right, key);
        }
        else {
            Node* l = s->left;
            Node* r = s->right;
            delete s;
            N--;
            if (!r) {
                s = l;
                return;
            }
            Node* min = findmin(r);
            removemin(r);
            min->right = r;
            min->left = l; 
            balance(min);
            s = min;
        }
        balance(s);
    }


    //малый левый поворот - высота правого поддерева больше на 2
    //height_diff(s) = 2
    void rotateL(Node*& s) {
        Node* x = s->right;
        s->right = x->left;
        x->left = s;
        new_height(s);
        new_height(x);
        new_sum(s);
        new_sum(x);
        s = x;       
    }


    //малый правый поворот - высота левого поддерева больше на 2
    //height_diff(s) = -2
    void rotateR(Node*& s) {
        Node* x = s->left;
        s->left = x->right;
        x->right = s;
        new_height(s);
        new_height(x);
        new_sum(s);
        new_sum(x);
        s = x;
    }
    
 
    void balance(Node*& s) {
        new_height(s);
        new_sum(s);

        //правое поддерево больше на 2
        if (height_diff(s) == 2) {
            //высота левого поддерева правого поддерева исходной вершины строго больше высоты правого
            //поддерева правого поддерева исходной вершины
            if (height_diff(s->right) < 0) {
                rotateR(s->right);
            }
            rotateL(s);
        }

        //левое поддерево больше на 2
        if (height_diff(s) == -2) {
            //высота правого поддерева левого поддерева исходной вершины строго больше высоты левого
            //поддерева левого поддерева исходной вершины
            if (height_diff(s->left) > 0) {
                rotateL(s->left);
            }
            rotateR(s);
        }
    }

    Node* head;

    int N = 0;

public:

    BST() : head(nullptr) {}

    BST(int key) { 
        head = new Node(key); 
        N = 1;
    }


    Node* get_root() const {
        return head;
    }


    void show() const {
        showR(head);
        cout << endl;
    }



    Node* find(int key) const {
        auto res = find_with_parent(key);
        return res.first;
    }


    void insert (int key) {
        insertR(head, key);
    }


    void remove(int key) {
        removeR(head, key);
    }
   

    long long sum(int l, int r) const {
        long long res = 0;
        Node* lca = LCA(l, r);
        if (!lca) {
            return 0;
        }
        long long sum_l = sum_L(lca, l);
        long long sum_r = sum_R(lca, r);
        res = lca->sum - sum_l - sum_r;
        return res;
    }


    int size() const {
        return N;
    }
};


int f(int x, long long s) {
    return (x + s) % 1'000'000'001;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    BST tr;
    int n;
    cin >> n;
    
    int key;
    int l, r;
    long long s = 0;
    string query;
    for (int i = 0; i < n; ++i) {
        cin >> query;
        if (query == "s") {
            cin >> l >> r;
            l = f(l, s);
            r = f(r, s);
            if (l > r) {
                cout << 0 << '\n';
                continue;
            }
            s = tr.sum(l, r);
            cout << s << '\n';
        }
        else {
            cin >> key;
            key = f(key, s);
            if (query == "+") {
                tr.insert(key);
            }
            else if (query == "-") {
                tr.remove(key);
            }
            else if (query == "?") {
                auto ptr = tr.find(key);
                if (ptr != nullptr) {
                    cout << "Found\n";
                }
                else {
                    cout << "Not found\n";
                }
            }   
        }
    }

    return 0;
}
