// Mint
//
template<typename T>
struct Modular {
    T mod;
    Modular(): mod(0) {}
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

class Mint {
  public:
    Mint() {
        N = 0;
    }

    template <class U>
    Mint(const U& N_) {
        N = modular.normalize(N_);
    }

    explicit operator string() const {
        return to_string(N);
    }

    explicit operator int() const {
        return N;
    }

    friend std::ostream& operator << (std::ostream& out, const Mint& n) {
        return out << int(n);
    }

    friend std::istream& operator >> (std::istream& in, Mint& n) {
        int64_t v_;
        in >> v_;
        n = Mint(v_);
        return in;
    }

    friend bool operator == (const Mint& lhs, const Mint& rhs) {
        return lhs.N == rhs.N;
    }

    friend bool operator != (const Mint& lhs, const Mint& rhs) {
        return !(lhs.N == rhs.N);
    }

    Mint inv(const Mint& m) const {
        Mint res;
        res.N = modular.mul(N, modular.inv(m.N));
        return res;
    }

    Mint neg() const {
        Mint res;
        res.N = N ? modular.mod - N : 0;
        return res;
    }

    Mint power(const Mint& o) const {
        Mint res;
        res.N = modular.power(N, o.N);
        return res;
    }

    Mint operator- () {
        return neg();
    }

    Mint& operator ++ () {
        N = modular.add(N, 1);
        return *this;
    }

    Mint& operator -- () {
        N = modular.sub(N, 1);
        return *this;
    }

    Mint& operator += (const Mint& o) {
        N = modular.add(N, o.N);
        return *this;
    }

    Mint& operator -= (const Mint& o) {
        N = modular.sub(N, o.N);
        return *this;
    }

    Mint& operator *= (const Mint& o) {
        N = modular.mul(N, o.N);
        return *this;
    }

    Mint& operator /= (const Mint& o) {
        N = modular.mul(N, modular.inv(o.N));
        return *this;
    }

    friend Mint operator ++ (Mint& a, int) {
        Mint r = a;
        ++a;
        return r;
    }

    friend Mint operator -- (Mint& a, int) {
        Mint r = a;
        --a;
        return r;
    }

    friend Mint operator + (const Mint& lhs, const Mint& rhs) {
        return Mint(lhs) += rhs;
    }

    friend Mint operator - (const Mint& lhs, const Mint& rhs) {
        return Mint(lhs) -= rhs;
    }

    friend Mint operator * (const Mint& lhs, const Mint& rhs) {
        return Mint(lhs) *= rhs;
    }

    friend Mint operator / (const Mint& lhs, const Mint& rhs) {
        return Mint(lhs) /= rhs;
    }
  private:
    int N;
};

template <class T, class U>
Mint power(const T& x, const U& y) {
    return Mint(x).power(y);
}

string to_string(const Mint& x) {
    return string(x);
}