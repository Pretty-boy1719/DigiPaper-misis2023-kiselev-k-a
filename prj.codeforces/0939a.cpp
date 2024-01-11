#include <iostream>
#include <vector>

bool dfs(int v, std::vector<std::vector<int>>&g, std::vector<int> &color) {
	color[v] = 1;

	for (int i = 0; i < g[v].size(); i += 1) {
		int to = g[v][i];
		if (color[to] == 0) {
			if (dfs(to,g,color)) return true;
		} 
		else if (color[to] == 1) {
			return true;
		}
	}
	color[v] = 2;
	return false;
}


int main() {
	
	int n = 0;
	std::cin >> n;

	std::vector<std::vector<int>> g(n);
	std::vector<int>color(n,0);

	for (int i = 0; i < n; i += 1) {
		int temp;
		std::cin >> temp;
		temp -= 1;

		g[i].push_back(temp);
	}
	
	bool love_triangle = false;
	for (int v = 0; v < n; v += 1) {
		if (g[g[g[v][0]][0]][0] == v) love_triangle = true;
	}

	if (love_triangle) std::cout << "YES";
	else std::cout << "NO";
	
	return 0;
}
