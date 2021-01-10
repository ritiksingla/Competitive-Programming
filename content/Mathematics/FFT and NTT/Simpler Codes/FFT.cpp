// FFT
//
using cd = complex<double>;
const int maxn = 1e6 + 10;
const long double pi = acos(-1);
long long a[maxn], b[maxn];
void fft(vector<cd> &a, bool invert)
{
    long long n = a.size();
    for (long long i = 1, j = 0; i < n; i++)
    {
        long long bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (long long len = 2; len <= n; len <<= 1)
    {
        double ang = (2 * pi / len) * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (long long i = 0; i < n; i += len)
        {
            cd w(1);
            for (long long j = i; j < i + (len >> 1); j++)
            {
                cd u = a[j];
                cd v = w * a[j + (len >> 1)];
                a[j] = u + v;
                a[j + (len >> 1)] = u - v;
                w = w * wlen;
            }
        }
    }
    if (invert)
    {
        for (cd &x : a)
            x /= n;
    }
}
void multiply(vector<long long>a, vector<long long>b,int n)
{
    vector<cd>na(begin(a), end(a)), nb(begin(b), end(b));
    int n_ = 1;
    while (n_ < 2 * n + 1)
        n_ <<= 1;
    na.resize(n_);
    nb.resize(n_);
    fft(na, false);
    fft(nb, false);
    rep(i, n_)
    na[i] = na[i] * nb[i];
    fft(na, true);
    rep(i, 2 * n - 1)
    cout << (long long)round(na[i].real()) << " ";
    cout << "\n";
}