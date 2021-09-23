// KMP Automaton - <O(ALPHA * |pattern|), O(|text|)>

template<int ALPHA_SIZE = 26>
struct KmpAutomaton {
	int sz, num_match;
	vector<vector<int>> nxt;

	// change this if different alphabet
	int remap(char c) { return c - 'a'; }

	KmpAutomaton(string &pat) : sz((int)pat.size()), nxt(sz + 1, vector<int>(ALPHA_SIZE)) {
		nxt[0][remap(pat[0])] = 1;
		for (int i = 1, j = 0; i <= sz; i++) {
			for (int c = 0; c < ALPHA_SIZE; c++) nxt[i][c] = nxt[j][c];
			if (i == sz) continue;
			nxt[i][remap(pat[i])] = i + 1;
			j = nxt[j][remap(pat[i])];
		}
	}

	int kmp(string &s) {
		num_match = 0;
		for (int i = 0, j = 0; i < (int)s.size(); i++) {
			j = nxt[j][remap(s[i])];
			if (j == sz) num_match++; // match: i - j + 1
		}
		return num_match;
	}
};