operations/member functions:\
1. search: O(logn)\
2. insert: O(logn)\
3. delete: O(logn)\
4. uplift: O(1) with randomness\

structure:\
1. Skiplist is built upon linked list, thus random acces is not allowed. Rather, there are nodes with pointers pointing to each other.\
2. A headnode serves as an entrant without carrying actual data, all operations start from here. In particular, the node links only to the smallest node on the highest layer.\
3. There are layers of listnodes, which all have four pointers, top, down, left and right.\
4. All inserted value creates a node in sorted matter at the lowest layer. Whether the node is uplifted to next upper level depends on probability of 0.5.  




