// FFT2
//
using cd = complex<double>;
const long double PI = acos(-1);
vector<int>rev;
int bit = 2;
void get_inv() {
    rev.resize(bit);
    for (int i = 0; i < bit; i++) {
        rev[i] = ((rev[i >> 1] >> 1) | ((bit >> 1) * (i & 1)));
    }
}
void fft(vector<cd>& a, int invert) {
    for (int i = 0; i < bit; i++)
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    for (int m = 1; m < bit; m <<= 1) {
        cd wlen(cos(PI / m), invert * sin(PI / m));
        for (int i = 0; i < bit; i += (m << 1)) {
            cd w(1, 0);
            for (int j = 0; j < m; j++, w = w * wlen) {
                cd x = a[i + j], y = a[i + j + m] * w;
                a[i + j] = x + y;
                a[i + j + m] = x - y;
            }
        }
    }
    if (invert == -1) {
        for (auto& x : a) {
            x /= bit;
        }
    }
}
int main() {
    get_inv();
    int n;
    cin >> n;
    while (bit <= n + n) {
        (bit <<= 1);
    }
    vector<cd>a(bit, 0), b(bit, 0);
    for (int i = 0 ; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0 ; i < n; i++) {
        cin >> b[i];
    }
    fft(a, 1);
    fft(b, 1);
    rep(i, bit)
    a[i] *= b[i];
    fft(a, -1);
    int ans[n];
    for (int i = 0 ; i < n; i++) {
        ans[i] = (int)(a[i].real() + 0.5);
    }
}