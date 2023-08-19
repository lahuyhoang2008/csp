#include <bits/stdc++.h>
using namespace std;
#define ll long long
vector<ll> a[1005];
ll r[1005],d[1005][1005],n,m;
void dfs(ll x)
{
    d[x][x] = 1;
    ll i,j;
    for(i = 0;i < a[x].size();i++)
    {
        ll y = a[x][i];
        if(d[y][y] == 0)
        {
            dfs(y);
        }
        for(j = 0;j < n;j++)
        {
            d[x][j] = max(d[x][j], d[y][j]);
        }
    }
}
int main()
{
    cin >> n >> m;
    ll i,j;
    for(i = 0;i < m;i++)
    {
        ll u,v;
        cin >> u >> v;
        u--;
        v--;
        a[u].push_back(v);
        r[v] = 1;
    }
    for(i = 0;i < n;i++)
    {
        if(r[i] == 0)
        {
            dfs(i);
        }
    }
    ll ans = 0;
    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
            if(d[i][j] == 0 && d[j][i] == 0) ans++;
        }
    }
    cout << ans / 2;
}
