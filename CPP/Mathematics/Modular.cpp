// Modular Arithmetic
//
template<typename T>
class Modular {
  private:
    const T mod;
  public:

    Modular(T mod_): mod(mod_) {}

    template <typename U>
    inline T normalize(U a) const {
        assert(std::is_integral<U>::value);
        a %= mod;
        if (a < 0) {
            a += mod;
        }
        return static_cast<T>(a);
    }
    inline T add(T a, T b) const {
        a += b;
        if (a >= mod) {
            a -= mod;
        }
        return a;
    }
    inline T sub(T a, T b) const {
        a -= b;
        if (a < 0) {
            a += mod;
        }
        return a;
    }
    T mul(T a, T b) const {
        return (a * 1LL * b) % mod;
    }
    inline T power(T a, T b) const {
        T res = 1;
        a %= mod;
        if (a < 0) {
            a += mod;
        }
        while (b > 0) {
            if (b & 1) {
                res = mul(res, a);
            }
            a = mul(a, a);
            b = b >> 1;
        }
        return res;
    }
    inline T inv(T a) const {
        a %= mod;
        if (a < 0) {
            a += mod;
        }
        T b = mod, u = 0, v = 1;
        while (a) {
            T t = b / a;
            b -= t * a;
            std::swap(a, b);
            u -= t * v;
            std::swap(u, v);
        }
        assert(b == 1);
        if (u < 0) {
            u += mod;
        }
        return u;
    }
};
constexpr int md = int(1e9) + 7;
Modular<int>modular(md);