// Point
//
template <class T>
struct Point {
    T x, y;

    Point(): x(0), y(0) {}
    Point(T x_, T y_): x(x_), y(y_) {}
    template <typename U> explicit Point(const Point<U>& p) : x(p.x), y(p.y) {}
    Point(const std::array<T, 2>& p) : x(p[0]), y(p[1]) {}
    Point(const std::pair<T, T>& p) : x(p.first), y(p.second) {}
    Point(const std::complex<T>& p) : x(real(p)), y(imag(p)) {}

    operator std::array<T, 2> () const {
        return std::array<T, 2> {x, y};
    }
    operator std::pair<T, T> () const {
        return std::pair<T, T>(x, y);
    }
    operator std::complex<T> () const {
        return std::complex<T>(x, y);
    }

    friend std::ostream& operator << (std::ostream& o, const Point& p) {
        return o << '(' << p.x << ',' << p.y << ')';
    }
    friend std::istream& operator >> (std::istream& i, Point& p) {
        return i >> p.x >> p.y;
    }
    friend bool operator == (const Point& lhs, const Point& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    friend bool operator != (const Point& lhs, const Point& rhs) {
        return !(lhs == rhs);
    }

    Point operator + () const {
        return Point(+x, +y);
    }
    Point operator - () const {
        return Point(-x, -y);
    }

    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Point& operator-=(const Point& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Point& operator*=(long double other) {
        x *= other;
        y *= other;
        return *this;
    }
    Point& operator/=(long double other) {
        x /= other;
        y /= other;
        return *this;
    }
    friend Point operator + (const Point& lhs, const Point& rhs) {
        return Point(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    friend Point operator - (const Point& lhs, const Point& rhs) {
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }
    friend Point operator * (const Point& p, const T& t) {
        return Point(p.x * t, p.y * t);
    }
    friend Point operator * (const T& t , const Point& p) {
        return Point(t * p.x, t * p.y);
    }
    friend Point operator / (const Point& p, const T& t) {
        return Point(p.x / t, p.y / t);
    }

    T dist2() const {
        return x * x + y * y;
    }
    auto dist() const {
        return std::sqrt(dist2());
    }
    Point unit() const {
        return *this / this->dist();
    }
    auto angle() const {
        return std::atan2(y, x);
    }

    Point normalize() const {
        if (!x && !y) {
            return *this;
        } return *this / (__gcd(x, y));
    }

    Point perp_cw() const {
        return Point(y, -x);
    }
    Point perp_ccw() const {
        return Point(-y, x);
    }

    friend T dot(const Point& a, const Point& b) {
        return a.x * b.x + a.y * b.y;
    }
    friend T cross(const Point& a, const Point& b) {
        return a.x * b.y - a.y * b.x;
    }
    friend T cross3(const Point& a, const Point& b, const Point& c) {
        return cross(b - a, c - a);
    }

    friend bool same_dir(const Point& a, const Point& b) {
        return cross(a, b) == 0 && dot(a, b) > 0;
    }

    // check if 180 <= s..t < 360
    friend bool is_reflex(const Point& a, const Point& b) {
        auto c = cross(a, b);
        return c ? (c < 0) : (dot(a, b) < 0);
    }

    // operator < (s, t) for angles in [base, base + 2pi)
    friend bool angle_less(const Point& base, const Point& s, const Point& t) {
        int r = is_reflex(base, s) - is_reflex(base, t);
        return r ? (r < 0) : (0 < cross(s, t));
    }

    friend auto angle_cmp(const Point& base) {
        return [base](const Point & s, const Point & t) {
            return angle_less(base, s, t);
        };
    }
    friend auto angle_cmp_center(const Point& center, const Point& dir) {
        return [center, dir](const Point & s, const Point & t) -> bool { return angle_less(dir, s - center, t - center); };
    }

    // is p in [s, t] taken ccw ? 1 / 0 / -1 for in / border / out
    friend int angle_between(const Point& s, const Point& t, const Point& p) {
        if (same_dir(p, s) || same_dir(p, t)) {
            return 0;
        }
        return angle_less(s, p, t) ? 1 : -1;
    }
};