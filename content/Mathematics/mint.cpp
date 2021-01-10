// Mint
// 
template<const int _mod>
struct modular_int
{
    int x;
    static vector<int> inverse_list ;
    const static int inverse_limit;
    const static bool is_prime;
    modular_int()
    {
        x = 0;
    }
    template<typename T>
    modular_int(const T z)
    {
        x = (z % _mod);
        if (x < 0) x += _mod;
    }
    modular_int(const modular_int<_mod> *z)
    {
        x = z->x;
    }
    modular_int(const modular_int<_mod> &z)
    {
        x = z.x;
    }
    modular_int operator - (const modular_int<_mod> &m) const
    {
        modular_int<_mod> U;
        U.x = x - m.x;
        if (U.x < 0) U.x += _mod;
        return U;
    }
    modular_int operator + (const modular_int<_mod> &m) const
    {
        modular_int<_mod> U;
        U.x = x + m.x;
        if (U.x >= _mod) U.x -= _mod;
        return U;
    }
    modular_int &operator -= (const modular_int<_mod> &m)
    {
        x -= m.x;
        if (x < 0) x += _mod;
        return *this;
    }
    modular_int &operator += (const modular_int<_mod> &m)
    {
        x += m.x;
        if (x >= _mod) x -= _mod;
        return *this;
    }
    modular_int operator * (const modular_int<_mod> &m) const
    {
        modular_int<_mod> U;
        U.x = (x * 1ull * m.x) % _mod;
        return U;
    }
    modular_int &operator *= (const modular_int<_mod> &m)
    {
        x = (x * 1ull * m.x) % _mod;
        return *this;
    }
    template<typename T>
    friend modular_int operator + (const T &l, const modular_int<_mod> &p)
    {
        return (modular_int<_mod>(l) + p);
    }
    template<typename T>
    friend modular_int operator - (const T &l, const modular_int<_mod> &p)
    {
        return (modular_int<_mod>(l) - p);
    }
    template<typename T>
    friend modular_int operator * (const T &l, const modular_int<_mod> &p)
    {
        return (modular_int<_mod>(l) * p);
    }
    template<typename T>
    friend modular_int operator / (const T &l, const modular_int<_mod> &p)
    {
        return (modular_int<_mod>(l) / p);
    }

    int value() const
    {
        return x;
    }
    modular_int operator ^ (const modular_int<_mod> &cpower) const
    {
        modular_int<_mod> ans;
        ans.x = 1;
        modular_int<_mod> curr(this);
        int power = cpower.x;

        if (curr.x <= 1)
        {
            if (power == 0) curr.x = 1;
            return curr;
        }
        while ( power > 0)
        {
            if (power & 1)
            {
                ans *= curr;
            }
            power >>= 1;
            if (power) curr *= curr;
        }
        return ans;
    }
    modular_int operator ^ (long long power) const
    {
        modular_int<_mod> ans;
        ans.x = 1;
        modular_int<_mod> curr(this);
        if (curr.x <= 1)
        {
            if (power == 0) curr.x = 1;
            return curr;
        }
        // Prime Mods
        if (power >= _mod && is_prime)
        {
            power %= (_mod - 1);
        }

        while ( power > 0)
        {
            if (power & 1)
            {
                ans *= curr;
            }
            power >>= 1;
            if (power) curr *= curr;

        }
        return ans;
    }
    modular_int operator ^ (int power) const
    {
        modular_int<_mod> ans;
        ans.x = 1;
        modular_int<_mod> curr(this);
        if (curr.x <= 1)
        {
            if (power == 0) curr.x = 1;
            return curr;
        }
        while ( power > 0)
        {
            if (power & 1)
            {
                ans *= curr;
            }
            power >>= 1;
            if (power) curr *= curr;
        }
        return ans;
    }
    template<typename T>
    modular_int &operator ^= (T power)
    {
        modular_int<_mod> res = (*this)^power;
        x = res.x;
        return *this;
    }
    template<typename T>
    modular_int pow(T x)
    {
        return (*this)^x;
    }
    pair<long long, long long> gcd(const int a, const int b) const
    {
        if (b == 0) return {1, 0};
        pair<long long, long long> c = gcd(b, a % b);
        return { c.second, c.first - (a / b) *c.second};
    }
    inline void init_inverse_list() const
    {
        vector<int> &dp = modular_int<_mod>::inverse_list;
        dp.resize(modular_int<_mod>::inverse_limit + 1);
        int n = modular_int<_mod>::inverse_limit;
        dp[0] = 1;
        if (n > 1) dp[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            dp[i] = (dp[_mod % i] * 1ull * (_mod - _mod / i)) % _mod;
        }
    }
    modular_int<_mod> get_inv() const
    {
        if (modular_int<_mod>::inverse_list.size() < modular_int<_mod>::inverse_limit + 1) init_inverse_list();
        if (this->x <= modular_int<_mod>::inverse_limit)
        {
            return modular_int<_mod>::inverse_list[this->x];
        }
        pair<long long, long long> G = gcd(this->x, _mod);
        return modular_int<_mod>(G.first);
    }
    modular_int<_mod> operator - () const
    {
        modular_int<_mod> v(0);
        v -= (*this);
        return v;
    }
    modular_int operator / (const modular_int<_mod> &m) const
    {
        modular_int<_mod> U(this);
        U *= m.get_inv();
        return U;
    }
    modular_int &operator /= (const modular_int<_mod> &m)
    {
        (*this) *= m.get_inv();
        return *this;
    }
    bool operator==(const modular_int<_mod> &m) const
    {
        return x == m.x;
    }
    bool operator < (const modular_int<_mod> &m) const
    {
        return x < m.x;
    }
    template<typename T>
    bool operator == (const T &m) const
    {
        return (*this) == (modular_int<_mod>(m));
    }
    template<typename T>
    bool operator < (const T &m) const
    {
        return x < (modular_int<_mod>(m)).x;
    }
    template<typename T>
    bool operator > (const T &m) const
    {
        return x > (modular_int<_mod>(m)).x;
    }
    template<typename T>
    friend bool operator == (const T &x, const modular_int<_mod> &m)
    {
        return (modular_int<_mod>(x)).x == m.x;
    }
    template<typename T>
    friend bool operator < (const T &x, const modular_int<_mod> &m)
    {
        return (modular_int<_mod>(x)).x < m.x;
    }
    template<typename T>
    friend bool operator > (const T &x, const modular_int<_mod> &m)
    {
        return (modular_int<_mod>(x)).x > m.x;
    }
    friend istream &operator >> (istream &is, modular_int<_mod> &p)
    {
        int64_t val;
        is >> val;
        p.x = (val % _mod);
        if (p.x < 0) p.x += _mod;
        return is;
    }
    friend ostream &operator << (ostream &os, const modular_int<_mod> &p)
    {
        return os << p.x;
    }
};
const int mod = (int)1e9 + 7;
using mint = modular_int<mod>;
template<const int mod>
vector<int> modular_int<mod>::inverse_list;
template<const int mod>
const int modular_int<mod>::inverse_limit = -1;
template<const int mod>
const bool modular_int<mod>::is_prime = true;
