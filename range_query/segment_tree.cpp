using namespace std;

//with lazy propagation
class SegmentTree {
//attributes to be determined by the user
private:
    int originalEnd;
    vector<int> segment;
    vector<int> lazy;
    void update_function();
    void merge_function();
    void compare_function();
    
public:
    SegmentTree(vector<int>& arr) {
        int n = arr.size();
        originalEnd = n-1;
        int size = 1;
        while (size < 2*n) {
            size <<= 1;
        }
        
        segment.resize(size,0);
        lazy.resize(size,0);
        
        build_tree(arr,0,0,n-1);
    }
    
    void update_point(int index, int delta) {
        update_helper(index,index,delta,0,0,originalEnd);
    }
    
    void update_range(int left, int right, int delta) {
        update_helper(left, right, delta, 0, 0, originalEnd);
    }
    
    int query_point(int index) {
        return query_helper(index, index, 0, 0, originalEnd);
    }
    
    int query_range(int left, int right) {
        return query_helper(left, right, 0, 0, originalEnd);
    }

private:
    int build_tree(vector<int>& original, int sPos, int left, int right) {
        if (left == right) {
            return segment[sPos] = original[left];
        }
        
        int leftTree = sPos*2 + 1, rightTree = sPos*2 + 2, mid = left + (right-left)/2;
        return segment[sPos] = merge(build_tree(original,leftTree,left,mid)
            + build_tree(original,rightTree,mid+1,right));
    }
    
    int update_helper(int left, int right, int delta, int sPos, int sLeft, int sRight) {
        //lazy update first
        if (lazy[sPos]) {
            if (sLeft != sRight) update_lazy_sub(sPos,delta);
            segment[sPos] = update_function(segment, sPos, delta, lazy[sPos]);
            lazy[sPos] = 0;
        }
        
        if (left > sRight || right < sLeft) return segment[sPos];
        
        if (sLeft >= left && sRight <= right) {
            if (sLeft != sRight) update_lazy_sub(sPos);
            return segment[sPos] = update_function(segment, sPos, delta);
        }
        
        int sMid = sLeft + (sRight-sLeft)/2;
        int leftTree = sPos * 2 + 1, rightTree = sPos * 2 + 2;
        return segment[sPos] = merge(update_helper(left,right,delta,leftTree,sLeft,sMid)
            , update_helper(left,right,delta,rightTree,sMid+1,sRight));
    }
    
    void update_lazy_sub(int sPos,int delta) {
        lazy[sPos * 2 + 1] ^= 1;
        lazy[sPos * 2 + 2] ^= 1;
        return;
    }
    
    int query_helper(int left, int right, int pos, int sLeft, int sRight) {
        //lazy update first
        if (lazy[sPos]) {
            if (sLeft != sRight) update_lazy_sub(sPos,delta);
            segment[sPos] = update_function(segment, sPos, delta, lazy[sPos]);
            lazy[sPos] = 0;
        }
        
        if (left > sRight || sLeft > right) return -1;

        if (left <= sLeft && sRight <= right) {
            return segment[pos];
        }

        int leftTree = 2*pos+1, rightTree = 2*pos+2, mid = sLeft + (sRight-sLeft)/2;
        return compare(query_range(left,right,leftTree,sLeft,mid),query_range(left,right,rightTree,mid+1,sRight));
    }
    
    virtual int merge(int sPos) {
        int leftTree = 2*sPos + 1, rightTree = 2*sPos + 2;
        //dictates the relationship between children nodes and parent nodes
        //i.e. for a max segment tree
        //merge() := { parent = max(child_a,child_b); }
        return segment[sPos] = merge_function(segment[leftTree],segment[rightTree]);
    }
    
    virtual int compare(int a, int b) {
        return compare_function(a,b);
    }
};
