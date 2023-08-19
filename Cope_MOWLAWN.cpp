#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100000
ll d1[N + 5];
ll d2[N + 5];
ll a[N + 5];
ll sum[N + 5];
int main()
{
    ll n,k;
    cin >> n >> k;
    ll i,j, ans = 0;
    for(i = 0;i < n;i++) cin >> a[i];
    for(i = 0;i < n;i++) sum[i + 1] = sum[i] + a[i];
    d1[0] = a[0];
    d2[0] = a[0];
    for(i = 1;i < n;i++)
    {
        if(i >= k && (d2[i - k] + sum[i] - sum[i - k + 1]) == d1[i - 1])
        {
            for(j = 1;j <= k - 1;j++)
            {
                d1[i] = max(d1[i], d2[i - j] + sum[i + 1] - sum[i - j + 1]);
            }
        }else
        {
            d1[i] = d1[i - 1] + a[i];
        }
        if(i > 1)
        {
            d2[i] = max(d2[i - 1], d1[i - 2] + a[i]);
        }else
        {
            d2[i] = max(d2[i - 1], a[i]);
        }
        d1[i] = max(d1[i], d2[i]);
        ans = max(ans, d1[i]);
    }
    cout << ans;
}
