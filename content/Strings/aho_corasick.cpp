// Aho Corasick
//
template<int alphabet_size = 26, char minimal_char = 'a'>
class aho_corasick {
	struct vertex {
		vector<int>next;
		bool leaf = false;
		int suffix_link; // Fail link
		int exit; // Nearest fail link leaf
		int cnt; // For multiple matches
		vector<int>finish; // vector if multple patterns with same name present and we need them all at output
		vertex() {
			suffix_link = -1;
			exit = -1;
			cnt = 0;
			next.resize(alphabet_size, -1);
		}
	};
	vector<vertex>T; // Aho Corasick Tree
	vector<string>P; // Patterns
	aho_corasick(const vector<string>& S): P(S) {
		T.emplace_back();
		T[0].finish.emplace_back(0);
		add();
	}
	int query(const string& S, vector<bool>& isMatch) const {
		int ans{};
		int v = 0;
		for (int i = 0; i < int(S.size()); ++i) {
			int c = (S[i] - minimal_char);
			if (T[v].next[c] != -1) {
				v = T[v].next[c];
			} else {
				while (T[v].next[c] == -1 && v != 0) {
					v = T[v].suffix_link;
				}
				v = T[v].next[c];
			}
			if (v == -1) {
				v = 0;
			}
			ans += T[v].cnt;
			int t = v;
			while (t > 0) {
				if (!T[t].finish.empty()) {
					for (int x : T[t].finish) {
						// cout << "Pattern " << x + 1 << " matched at " << ((i + 1) - int(P[x].size()) + 1) << '\n';
						isMatch[x] = 1; // xth pattern is present in text
					}
				}
				t = T[t].exit;
			}
		}
		return ans;
	}
  private:
	void add() {
		int N = int(P.size());
		for (int i = 0; i < N; ++i) {
			int v = 0;
			for (int j = 0 ; j < int(P[i].size()); ++j) {
				int c = (P[i][j] - minimal_char);
				if (T[v].next[c] == -1) {
					T[v].next[c] = int(T.size());
					T.emplace_back();
				}
				v = T[v].next[c];
			}
			T[v].finish.emplace_back(i);
			T[v].leaf = true;
			T[v].cnt++;
		}
		build_automaton();
	}
	void build_automaton() {
		queue<int>q;
		q.push(0);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			vertex v = T[u];
			for (int j = 0; j < alphabet_size; j++) {
				int x = v.next[j];
				if (x != -1) {
					int l = v.suffix_link;
					while (l != -1 && T[l].next[j] == -1) {
						l = T[l].suffix_link;
					}
					T[x].suffix_link = (l == -1 ? 0 : T[l].next[j]);
					T[x].cnt += T[T[x].suffix_link].cnt;
					T[x].exit = T[T[x].suffix_link].leaf ? T[x].suffix_link : T[T[x].suffix_link].exit;
					q.push(x);
				}
			}
		}
	}
};