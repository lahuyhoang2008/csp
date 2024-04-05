#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2005;
struct node
{
    ll v;
    node* l;
    node* r;
    node* p;
    node()
    {
        l = NULL;
        r = NULL;
        p = NULL;
    }
};
ll cnt = 0;
struct bst
{
    node *root = NULL;
    void ins(node *&cur, ll x, node *par)
    {
        if(cur == NULL)
        {
            cur = new node();
            cur->p = par;
            cur->v = x;
            return;
        }else
        {
            cnt++;
            if(x < cur->v)
            {
                ins(cur->l,x, cur);
            }
            if(x > cur->v)
            {
                ins(cur->r,x, cur);
            }
        }
    }
    bool findv(node *cur, ll x)
    {
        if(cur->v == x) return 1;
        if(cur->v > x && cur->l) return findv(cur->l,x);
        if(cur->v < x && cur->r) return findv(cur->r,x);
        return 0;
    }
    ll lmouse(node *cur)
    {
        if(cur->l) return lmouse(cur->l);
        else return cur->v;
    }
};
bst f;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    ll i,j;
    for(i = 1;i <= n;i++)
    {
        ll x;
        cin >> x;
        f.ins(f.root, x, NULL);
        //cout << f.root->v << "\n";
        cout << cnt << "\n";
    }
}
