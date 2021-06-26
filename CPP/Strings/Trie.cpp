// Tries
//
// Space Complexity: O(total_length_of_all_strings * alphabet_size)
template<int alphabet_size = 26, char minimal_char = 'a'>
struct Trie {
	struct Vertex {
		vector<int>next;
		bool leaf = false;
		
		Vertex() {
			next.resize(alphabet_size, -1);
		}
	};
	vector<Vertex>T;
	Trie() {
		T.emplace_back();
	}
	void add(const string& S) {
		int v = 0;
		int N = int(S.size());
		for (int i = 0; i < N; ++i) {
			int c = (S[i] - minimal_char);
			if (T[v].next[c] == -1) {
				T[v].next[c] = int(T.size());
				T.emplace_back();
			}
			v = T[v].next[c];
		}
		T[v].leaf = true;
	}
};