// Tries
//
#include<bits/stdc++.h>
using namespace std;
template<int max_ascii>
struct trie
{
    struct node
    {
        node *c[max_ascii];
        int cnt = 0;
    };
    node *root = new node();
    void insert(const int &x)
    {
        node *head = root;
        for(int i = 30; i >= 0; i--)
        {
            int d = (x >> i) & 1;
            if(!head->c[d])
            {
                head->c[d] = new node();
            }
            head = head->c[d];
            head->cnt++;
        }
    }
    void remove(const int &x)
    {
        node *head = root;
        for(int i = 30; i >= 0; i--)
        {
            int d = (x >> i) & 1;
            head = head->c[d];
            head->cnt--;
        }
    }
    int query(const int &x)
    {
        node *head = root;
        int res{};
        for(int i = 30; i >= 0; i--)
        {
            int d = (x >> i) & 1;
            if(head->c[(d ^ 1)] != nullptr && head->c[(d ^ 1)]->cnt > 0)
            {
                res += (1 << i);
                head = head->c[(d ^ 1)];
            }
            else
            {
                head = head->c[d];
            }
        }
        return res;
    }
};
