// NTT
//
const int maxn = 1 << 18;
constexpr int mod = 163577857;
const int g = 23;
int invfact[maxn], fact[maxn];
int gpow[30], invgpow[30];
inline int mul(int x, int y)
{
    return (x % mod * (y % mod)) % mod;
}
inline int add(int x, int y)
{
    return (x % mod + y % mod + mod) % mod;
}
int power(int x, int y)
{
    int res = 1;
    x %= mod;
    for (; y; y >>= 1)
    {
        if (y & 1)
            res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}
int ncr(int n, int r)
{
    if (r<0 or r>n)
        return 0;
    return mul(fact[n], mul(invfact[r], invfact[n - r]));
}
void pre()
{
    fact[0] = 1;
    forn(i, 1, maxn - 1)
    fact[i] = fact[i - 1] * i % mod;
    invfact[maxn - 1] = power(fact[maxn - 1], mod - 2);
    for (int i = maxn - 2; i >= 0; i--)
        invfact[i] = invfact[i + 1] * (i + 1) % mod;
    int where = (mod - 1) / 2, invg = power(g, mod - 2);
    int idx = 0;
    while (where % 2 == 0)
    {
        idx++;
        gpow[idx] = power(g, where);
        invgpow[idx] = power(invg, where);
        where /= 2;
    }
}
struct NTT
{
    vector<int>a, b;
    int n_;
    NTT(int n)
    {
        this->n_ = 1 << (int)(ceil((ld)log2(n + 1int)));
        a.resize(n_, 0), b.resize(n_, 0);
    }
    void fft(vector<int> &a, bool invert)
    {
        for (int i = 1, j = 0; i < n_; i++)
        {
            int bit = n_ >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2, idx = 1; len <= n_; len <<= 1, idx++)
        {
            int wlen = (invert ? invgpow[idx] : gpow[idx]);
            for (int i = 0; i < n_; i += len)
            {
                int w = 1;
                for (int j = i; j < i + (len >> 1); j++)
                {
                    int u = a[j], v = mul(a[j + (len >> 1)], w);
                    a[j] = add(u, v);
                    a[j + (len >> 1)] = add(u, -v);
                    w = mul(w, wlen);
                }
            }
        }
        if (invert)
        {
            int n_1 = power(n_, mod - 2);
            rep(i, n_)
            a[i] = mul(a[i], n_1);
        }
    }
    void multiply(int na, int nb)
    {
        na++;
        nb++;
        fft(a, 0);
        fft(b, 0);
        rep(i, n_)
        a[i] = mul(a[i], b[i]);
        fft(a, 1);
        for (int i = na + nb - 1; i < n_; i++)
        {
            a[i] = 0;
        }
    }
};
/*
pre();
int n;
cin>>n;
NTT ntt(n);
for(int i = 0; i < n; ++i) {
    cin >> ntt.a[i];
}
for(int i = 0; i < n; ++i) {
    cin >> ntt.b[i];
}
ntt.multiply(n, n);
*/
