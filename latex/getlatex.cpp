#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

string path = "../content/";

void print_file(string s, bool skip = false) {
	ifstream fin(s.c_str());
	string line;
	int count = 0;
	while (getline(fin, line)) {
		if (count++ < 2 and skip) continue;
		cout << line << endl;
	}
}

string getName(string s) {
	ifstream fin(s.c_str());
	string line;
	getline(fin, line);
	if (line[2] == ' ') return line.substr(3);
	return line.substr(2);
}

void be_careful(string s) {
	for (char c : s) {
		if (c == '^') cout << '\\';
		cout << c;
		if (c == '^') cout << "{}";
	}
}

void print_listing(string sub, string f, bool skip) {
	cout << "\\subsection{";
	if (skip) be_careful(getName(f));
	else be_careful(sub);
	cout << "}\n";
	cout << "\\begin{lstlisting}\n";
	print_file(f, skip);
	cout << "\\end{lstlisting}\n\n";
}

void go(string s, bool x = false) {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(s.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;	

		if (entry->d_type == DT_DIR) go(s+"/"+string(entry->d_name), x);
		else {
			string s2 = string(entry->d_name);
			if (!x) print_listing(s2.substr(0, s2.size()-4), s+"/"+entry->d_name, true);
			else print_listing(s2, s+"/"+entry->d_name, false);
		}
	}
}

void print_section(string s) {
	cout << "\n\n";

	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n%\n% " << s << "\n%\n";
	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n\n";

	cout << "\\section{" << s << "}\n\n";
}

int main() {
	print_file("beginning.tex");
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(path.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type != DT_DIR) continue;

		string dir(entry->d_name);
		if (dir == "Theory") continue;
		print_section(dir);
		go(path + dir);
	}

	cout << "\\pagebreak" << endl;
	print_section("Theory");
	go(path + "Theory", true);

	cout << "\\end{document}\n";
	return 0;
}
