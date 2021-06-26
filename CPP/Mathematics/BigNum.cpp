// Arbitrary Precision Arithmetic
//
// Process big numbers which cannot fit in C++ data types
// Base is decimal (10 or power of 10). Usually it is int(1e9)
// There are no leading zeros in the result as long as there are no leading zeros in operands.
// Zero is represented as empty vector or single digit 0.
// Number is stored from LSB to MSB in a vector.

const int base = int(1e9);
const int base_digits = int(9);
struct BigNum {
	vector<int> A;
	int sign;

	BigNum(): sign(1) {}

	BigNum(int64_t X) {
		*this = X;
	}

	BigNum(const BigNum& other): sign(other.sign), A(other.A) {}

	BigNum(const string& S) {
		read(S);
	}

	void operator=(const BigNum& other) {
		sign = other.sign;
		A = other.A;
	}

	void operator=(int64_t X) {
		sign = 1;
		if (X < 0) {
			sign = -1, X = -X;
		}
		for (; X > 0; X /= base) {
			A.emplace_back(X % base);
		}
	}

	void trim() {
		while (!A.empty() && A.back() == 0) {
			A.pop_back();
		}
		if (A.empty()) {
			sign = 1;
		}
	}

	void read(const string& S) {
		sign = 1;
		A.clear();
		int pos = 0;
		while (pos < int(S.size()) && (S[pos] == '-' || S[pos] == '+')) {
			if (S[pos] == '-') {
				sign = -sign;
			}
			++pos;
		}

		for (int i = int(S.size()) - 1; i >= pos; i -= base_digits) {
			int X = 0;
			for (int j = max(pos, i - base_digits + 1); j <= i; j++) {
				assert(isdigit(S[j]));
				X = 10 * X + (S[j] - '0');
			}
			A.emplace_back(X);
		}
		trim();
	}

	BigNum operator-() const {
		BigNum res = *this;
		res.sign = -sign;
		return res;
	}

	BigNum abs() const {
		BigNum res = *this;
		res.sign *= res.sign;
		return res;
	}

	bool is_zero() const {
		return A.empty() || (int(A.size()) == 1 && !A[0]);
	}

	bool operator<(const BigNum& other) const {
		if (sign != other.sign) {
			return (sign < other.sign);
		}
		if (int(A.size()) != int(other.A.size())) {
			return (int(A.size()) * sign < int(other.A.size()) * other.sign);
		}
		for (int i = int(A.size()) - 1; i >= 0; i--)
			if (A[i] != other.A[i]) {
				return (A[i] * sign < other.A[i] * sign);
			}
		return false;
	}

	bool operator>(const BigNum& other) const {
		return (other < *this);
	}

	bool operator<=(const BigNum& other) const {
		return !(other < *this);
	}

	bool operator>=(const BigNum& other) const {
		return !(*this < other);
	}

	bool operator==(const BigNum& other) const {
		return !(*this < other) && !(other < *this);
	}

	bool operator!=(const BigNum& other) const {
		return (*this < other || other < *this);
	}

	BigNum operator+(const BigNum& other) const {
		if (sign == other.sign) {
			BigNum res = other;
			int N = max(int(A.size()), int(other.A.size()));
			for (int i = 0, carry = 0; (i < N) || (carry != 0); ++i) {
				if (i == int(res.A.size())) {
					res.A.emplace_back(0);
				}
				res.A[i] += carry + (i < int(A.size()) ? A[i] : 0);
				carry = (res.A[i] >= base);
				if (carry != 0) {
					res.A[i] -= base;
				}
			}
			return res;
		}
		return *this - (-other);
	}

	BigNum operator-(const BigNum& other) const {
		if (sign == other.sign) {
			if (abs() >= other.abs()) {
				BigNum res = *this;
				for (int i = 0, carry = 0; (i < int(other.A.size())) || (carry != 0); ++i) {
					res.A[i] -= carry + (i < int(other.A.size()) ? other.A[i] : 0);
					carry = (res.A[i] < 0);
					if (carry != 0) {
						res.A[i] += base;
					}
				}
				res.trim();
				return res;
			}
			return -(other - *this);
		}
		return *this + (-other);
	}

	void operator*=(int other) {
		if (other < 0) {
			sign = -sign, other = -other;
		}
		for (int i = 0, carry = 0; i < int(A.size()) || (carry != 0); ++i) {
			if (i == int(A.size())) {
				A.push_back(0);
			}
			int64_t cur = A[i] * 1ll * other + carry;
			carry = (int)(cur / base);
			A[i] = (int)(cur % base);
		}
		trim();
	}

	friend pair<BigNum, BigNum> divmod(const BigNum& A1, const BigNum& B1) {
		int norm = base / (B1.A.back() + 1);
		BigNum a = A1.abs() * norm;
		BigNum b = B1.abs() * norm;
		BigNum q, r;
		q.A.resize(a.A.size());

		for (int i = a.A.size() - 1; i >= 0; i--) {
			r *= base;
			r += a.A[i];
			int s1 = r.A.size() <= b.A.size() ? 0 : r.A[b.A.size()];
			int s2 = r.A.size() <= b.A.size() - 1 ? 0 : r.A[b.A.size() - 1];
			int d = ((int64_t) base * s1 + s2) / b.A.back();
			r -= b * d;
			while (r < 0) {
				r += b, --d;
			}
			q.A[i] = d;
		}

		q.sign = A1.sign * B1.sign;
		r.sign = A1.sign;
		q.trim();
		r.trim();
		return make_pair(q, r / norm);
	}

	static vector<int> convert_base(const vector<int>& V, int old_digits, int new_digits) {
		vector<int64_t> p(max(old_digits, new_digits) + 1);
		p[0] = 1;
		for (int i = 1; i < (int) p.size(); i++) {
			p[i] = p[i - 1] * 10;
		}
		vector<int> res;
		int64_t cur = 0;
		int cur_digits = 0;
		for (int i = 0; i < (int) V.size(); i++) {
			cur += V[i] * p[cur_digits];
			cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.push_back(int(cur % p[new_digits]));
				cur /= p[new_digits];
				cur_digits -= new_digits;
			}
		}
		res.push_back((int) cur);
		while (!res.empty() && !res.back()) {
			res.pop_back();
		}
		return res;
	}

	static vector<int64_t> karatsuba_multiply(const vector<int64_t>& P, const vector<int64_t>& Q) {
		int n = P.size();
		vector<int64_t> res(n + n);
		if (n <= 32) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					res[i + j] += P[i] * Q[j];
				}
			return res;
		}

		int k = (n >> 1);
		vector<int64_t> A1(P.begin(), P.begin() + k);
		vector<int64_t> A2(P.begin() + k, P.end());
		vector<int64_t> B1(Q.begin(), Q.begin() + k);
		vector<int64_t> B2(Q.begin() + k, Q.end());

		vector<int64_t> a1b1 = karatsuba_multiply(A1, B1);
		vector<int64_t> a2b2 = karatsuba_multiply(A2, B2);

		for (int i = 0; i < k; i++) {
			A2[i] += A1[i];
		}
		for (int i = 0; i < k; i++) {
			B2[i] += B1[i];
		}

		vector<int64_t> r = karatsuba_multiply(A2, B2);
		for (int i = 0; i < (int) a1b1.size(); i++) {
			r[i] -= a1b1[i];
		}
		for (int i = 0; i < (int) a2b2.size(); i++) {
			r[i] -= a2b2[i];
		}

		for (int i = 0; i < (int) r.size(); i++) {
			res[i + k] += r[i];
		}
		for (int i = 0; i < (int) a1b1.size(); i++) {
			res[i] += a1b1[i];
		}
		for (int i = 0; i < (int) a2b2.size(); i++) {
			res[i + n] += a2b2[i];
		}
		return res;
	}

	BigNum operator*(const BigNum& v) const {
		vector<int> a6 = convert_base(this->A, base_digits, 6);
		vector<int> b6 = convert_base(v.A, base_digits, 6);
		vector<int64_t> P(a6.begin(), a6.end());
		vector<int64_t> Q(b6.begin(), b6.end());
		while (P.size() < Q.size()) {
			P.push_back(0);
		}
		while (Q.size() < P.size()) {
			Q.push_back(0);
		}
		while (P.size() & (P.size() - 1)) {
			P.push_back(0), Q.push_back(0);
		}
		vector<int64_t> c = karatsuba_multiply(P, Q);
		BigNum res;
		res.sign = sign * v.sign;
		for (int i = 0, carry = 0; i < (int) c.size(); i++) {
			int64_t cur = c[i] + carry;
			res.A.push_back((int)(cur % 1000000));
			carry = (int)(cur / 1000000);
		}
		res.A = convert_base(res.A, 6, base_digits);
		res.trim();
		return res;
	}

	int64_t long_value() const {
		int64_t res = 0;
		for (int i = A.size() - 1; i >= 0; i--) {
			res = res * base + A[i];
		}
		return res * sign;
	}

	friend BigNum gcd(const BigNum& a, const BigNum& b) {
		return b.is_zero() ? a : gcd(b, a % b);
	}

	friend BigNum lcm(const BigNum& a, const BigNum& b) {
		return a / gcd(a, b) * b;
	}

	BigNum operator/(const BigNum& other) const {
		return divmod(*this, other).first;
	}

	BigNum operator%(const BigNum& other) const {
		return divmod(*this, other).second;
	}

	void operator/=(int other) {
		if (other < 0) {
			sign = -sign, other = -other;
		}
		for (int i = (int) A.size() - 1, rem = 0; i >= 0; --i) {
			int64_t cur = A[i] + rem * (int64_t) base;
			A[i] = (int)(cur / other);
			rem = (int)(cur % other);
		}
		trim();
	}

	BigNum operator/(int other) const {
		BigNum res = *this;
		res /= other;
		return res;
	}

	int operator%(int other) const {
		if (other < 0) {
			other = -other;
		}
		int m = 0;
		for (int i = A.size() - 1; i >= 0; --i) {
			m = (A[i] + m * (int64_t) base) % other;
		}
		return m * sign;
	}

	void operator+=(const BigNum& other) {
		*this = *this + other;
	}

	void operator-=(const BigNum& other) {
		*this = *this - other;
	}

	BigNum operator*(int other) const {
		BigNum res = *this;
		res *= other;
		return res;
	}

	void operator*=(const BigNum& other) {
		*this = *this * other;
	}

	void operator/=(const BigNum& other) {
		*this = *this / other;
	}

	friend istream& operator>>(istream& stream, BigNum& other) {
		string s;
		stream >> s;
		other.read(s);
		return stream;
	}

	friend ostream& operator<<(ostream& stream, const BigNum& other) {
		if (other.sign == -1) {
			stream << '-';
		}
		stream << (other.A.empty() ? 0 : other.A.back());
		for (int i = int(other.A.size()) - 2; i >= 0; --i) {
			stream << setw(base_digits) << setfill('0') << other.A[i];
		}
		return stream;
	}
};