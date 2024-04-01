#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;

constexpr bool typetest = 0;
constexpr int N = 2e5 + 5;
constexpr int Inf = 1e9 + 7;

int id[N],ide[N],cnt = 1,par[25][N],h[N];
ll b[N];
vector<pair<int,ll>> p[N];
ll n;
void buildtree(ll x)
{
    ll i,j;
    id[x] = cnt;
    cnt++;
    ide[x] = id[x];
    par[0][x] = x;
    for(i = 0;i < p[x].size();i++)
    {
        ll x2 = p[x][i].first;
        if(id[x2] == 0)
        {
            h[x2] = h[x] + 1;
            b[cnt] = b[id[x]] + p[x][i].second;
            par[1][x2] = x;
            buildtree(x2);
            ide[x] = max(ide[x], ide[x2]);
        }
    }
}
void bnsk(ll i)
{
    if(i > 1)
    {
        bnsk(i - 1);
        ll j;
        for(j = 1;j <= n;j++)
        {
            ll j2 = par[i - 1][j];
            par[i][j] = par[i - 1][j2];
        }
    }
}
#define bit(a,b) ((a >> b) & 1)
ll findpa(ll x, ll y)
{
    for(ll i = 0;(1 << i) <= y;i++) if(bit(y,i)) x = par[i + 1][x];
    return x;
}
ll lca(ll x, ll y)
{
    if(h[x] > h[y]) x = findpa(x, h[x] - h[y]);
    else y = findpa(y, h[y] - h[x]);
    if(x == y) return x;
    else
    {
        ll l = 1, r = h[x];
        while(true)
        {
            if(l == r)
            {
                return findpa(x,l);
            }
            if(l + 1 == r)
            {
                if(findpa(x,l) == findpa(y,l)) return findpa(x,l);
                else return findpa(x,r);
            }
            ll mid = (l + r) / 2;
            if(findpa(x,mid) == findpa(y,mid)) r = mid;
            else l = mid;
        }
    }
}
struct segtree
{
    ll b[N * 4];
    ll si[N * 4];
    ll lazy[N * 4];
    ll n;
    void build(ll n, ll a[N * 4])
    {
        this->n = n;
        build(0, 1, n, a);
    }
    void build(ll x, ll l, ll r, ll a[N * 4])
    {
        if(l == r)
        {
            si[x] = 1;
            b[x] = a[l];
            lazy[x] = 0;
        }else
        {
            ll mid = (l + r) / 2;
            build(x * 2 + 1,l ,mid, a);
            build(x * 2 + 2,mid + 1,r, a);
            b[x] = b[x * 2 + 1] + b[x * 2 + 2];
            si[x] = si[x * 2 + 1] + si[x * 2 + 2];
            lazy[x] = 0;
        }
    }
    void push(ll x)
    {
        b[x * 2 + 1] += lazy[x] * si[x * 2 + 1];
        lazy[x * 2 + 1] += lazy[x];
        b[x * 2 + 2] += lazy[x] * si[x * 2 + 2];
        lazy[x * 2 + 2] += lazy[x];
        lazy[x] = 0;
    }
    void udt(ll l, ll r, ll v)
    {
        udt(0, 1, n, l, r, v);
    }
    void udt(ll x,  ll l, ll r, ll s, ll e, ll v)
    {
        if(r < s || e < l) return;
        if(s <= l && r  <= e)
        {
            b[x] += v * si[x];
            lazy[x] += v;
            return;
        }
        push(x);
        ll mid = (l +  r) / 2;
        udt(x * 2 + 1, l, mid, s, e, v);
        udt(x * 2 + 2,mid + 1,r,s,e,v);
        b[x] = b[x * 2 + 1] + b[x * 2 + 2];
    }
    ll get(ll l, ll r)
    {
        return get(0, 1, n, l, r);
    }
    ll get(ll x, ll l, ll r,ll s,ll e)
    {
        if(r < s || e  < l) return 0;
        if(s <= l && r <= e)
        {
            return b[x];
        }
        push(x);
        ll mid = (l + r) / 2;
        ll ans1 = get(x * 2 + 1,l,mid,s,e);
        ll ans2 = get(x * 2 + 2,mid + 1,r,s,e);
        return ans1 + ans2;
    }
};
segtree f;
pair<pair<ll,ll>,ll> r[N];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    ll i,j;
    for(i = 1;i < n;i++)
    {
        ll u,v,c;
        cin >> u >> v >> c;
        r[i] = {{u,v},c};
        p[u].push_back({v,c});
        p[v].push_back({u,c});
    }
    buildtree(1);
    bnsk(20);
    f.build(n,b);
    ll q;
    cin >> q;
    while(q--)
    {
        ll qr;
        cin >> qr;
        if(qr == 1)
        {
            ll x,m;
            cin >> x >> m;
            ll tmp;
            if(h[r[x].first.first] > h[r[x].first.second]) tmp = r[x].first.first;
            else tmp = r[x].first.second;
            f.udt(id[tmp], ide[tmp], m - r[x].second);
            r[x].second = m;
        }else
        {
            ll x,y;
            cin >> x >> y;
            ll z = lca(x,y);
            cout << f.get(id[x],id[x]) + f.get(id[y],id[y]) - 2 * f.get(id[z],id[z]) << "\n";
        }
    }
    //cout << lca(2,3);

}
