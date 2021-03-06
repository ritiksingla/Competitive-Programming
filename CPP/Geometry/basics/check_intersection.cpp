// Check Intersection
//
struct pt {
    int64_t x, y;
    pt(): x(), y() {}
    pt(int64_t x_, int64_t y_): x(x_), y(y_) {}
    pt operator-(const pt& a) const {
        return pt(x - a.x, y - a.y);
    }
    int64_t cross(const pt& a) const {
        return x * a.y - y * a.x;
    }
    int64_t cross(const pt& a, const pt& b) const { // Cross Product of (a-this*),(b-this*)
        return (a - *this).cross(b - *this);
    }
};
// Orientation based on sign
int64_t orientation(const int64_t& x) {
    return (x >= 0 ? x ? 1 : 0 : -1);
}
// If two segments overlap or intersect on more than 1 point
// Check for (x1,x2,x3,x4) and then (y1,y2,y3,y4)
bool overlap(int64_t a, int64_t b, int64_t c, int64_t d) {
    if (a > b) {
        swap(a, b);
    }
    if (c > d) {
        swap(c, d);
    }
    return max(a, c) <= min(b, d);
}
bool intersect(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0) { //If d lies on same side for both a,b means d is collinear with a,b.
        return overlap(a.x, b.x, c.x, d.x) && overlap(a.y, b.y, c.y, d.y);
    }
    return orientation(a.cross(b, c)) != orientation(a.cross(b, d)) && orientation(c.cross(d, a)) != orientation(c.cross(d, b));
}
