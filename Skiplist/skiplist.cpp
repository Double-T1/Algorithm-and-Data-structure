class Skiplist {
public:
    Skiplist() {
        head = make_shared<SkipNode>();
    }
    
    bool search(int target) {
        for (auto node=head; node; node=node->down) {
            while (node->right && node->right->val < target) 
                node = node->right;
            if (node->right && node->right->val == target) return true;
        }
        return false;
    }
    
    void add(int num) {
        stack<shared_ptr<SkipNode>> pres;
        
        for (auto node=head; node; node=node->down) {
            while (node->right && node->right->val < num) 
                node = node->right;
            pres.push(node);
        }
        
        //the key is that is all layers are filled, we need to create a new dummy layer 
        //with the head only
        shared_ptr<SkipNode> lower = nullptr;
        bool insert = true;
        while (!pres.empty() && insert) {
            auto pre = pres.top(); pres.pop();
            pre->right = make_shared<SkipNode>(num,pre->right,lower);
            lower = pre->right;
            
            insert = rand()&1;
        }
        
        if (pres.empty())
            head = make_shared<SkipNode>(-1,nullptr,head);
    }
    
    bool erase(int target) {
        bool found = false;
        for (auto node=head; node; node=node->down) {
            while (node->right && node->right->val < target) 
                node = node->right;
            if (node->right && node->right->val == target) {
                node->right = node->right->right;
                found = true;
            }
        }
        return found;
    }
    
private:
    void print() {
        for (auto levels = head; levels; levels = levels->down) {
            for (auto node = levels; node; node = node->right) {
                cout << node->val << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    struct SkipNode {
        int val;
        shared_ptr<SkipNode> right;
        shared_ptr<SkipNode> down;
        
        SkipNode(int v = -1, 
                 shared_ptr<SkipNode> r = nullptr, 
                 shared_ptr<SkipNode> d = nullptr):
            val(v), right(r), down(d) {}
    };
    
    shared_ptr<SkipNode> head;
};
