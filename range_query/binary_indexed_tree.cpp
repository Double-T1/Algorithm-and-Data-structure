//
//  main.cpp
//  binary indexed tree
//
//  Created by Chen Wei-Chen on 2023/2/10.
//

#include <iostream>
#include <vector>

using namespace std;


class BIT {
private:
    vector<int> arr;
    
public:
    BIT(int len): arr(len+1,0) {
    }
    
    void update(int i,int delta) {
        ++i;
        for (; i<arr.size(); arr[i] += delta, i += i&(-i));
    }
    
    int query(int i) {
        ++i;
        int sum = 0;
        for (; i; sum += arr[i], i -= i&(-i));
        return sum;
    }
};
