// 2D Basics
//
struct point2d {
    long double x, y;
    point2d() {}
    point2d(long double x, long double y): x(x), y(y) {}
    point2d& operator+=(const point2d& t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d& operator-=(const point2d& t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d& operator*=(long double t) {
        x *= t;
        y *= t;
        return *this;
    }
    point2d& operator/=(long double t) {
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d& t) const {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d& t) const {
        return point2d(*this) -= t;
    }
    point2d operator*(long double t) const {
        return point2d(*this) *= t;
    }
    point2d operator/(long double t) const {
        return point2d(*this) /= t;
    }
};
point2d operator*(long double a, point2d b) {
    return b * a;
}
long double cross(point2d a, point2d b) {
    return a.x * b.y - a.y * b.x;
}
long double dot(point2d a, point2d b) {
    return a.x * b.x + a.y * b.y;
}
// takes (x1,y1),(x2-x1,y2-y1),(x3,y3),(x4-x3,y4-y3)
// Form: r=a1+t*d1 where {a1} is a starting position vector and {d1} is the parallel vector to the given line.
// r=a1+t*d1 and cross_product((r-a2),d2)=0
// Therefore, t=a1+(cross_product((a2-a1),d2)/cross_product(d1,d2))*d1
point2d intersect(point2d a1, point2d d1, point2d a2, point2d d2) {
    if (cross(d1, d2) == 0) {
        cout << "Parallel lines\n";
        return point2d();
    }
    return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;
}
long double norm(point2d a) {
    return dot(a, a);
}
long double abs(point2d a) {
    return sqrt(norm(a));
}
long double proj(point2d a, point2d b) {
    return dot(a, b) / abs(b);
}
long double angle(point2d a, point2d b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}
