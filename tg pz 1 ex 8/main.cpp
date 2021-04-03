#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

bool has_path_dfs(std::vector<std::vector<int>> &gr, int fr, int to, std::set<int> &gray)
{
	if (fr == to) return true;
	gray.insert(fr);
	for (int j : gr[fr])
	{
		if (gray.count(j) != 0) continue;
		gray.insert(j);
		if (has_path_dfs(gr, j, to, gray)) return true;
		gray.erase(j);
	}
	return false;
}



bool has_path_bfs(const std::vector<std::vector<int>> &gr, int fr, int to)
{
	auto *q = new std::queue<int>();
	q->push(fr);
	auto *gray = new std::set<int>();
	while (!q->empty())
	{
		int v = q->front();
		q->pop();
		gray->insert(v);
		for (int j : gr[v])
		{
			if (gray->count(j) == 0) q->push(j);
			if (j == to) return true;
		}
	}

	return false;
}

int main(int argc, char *argv[])
{
	auto *input = new std::ifstream("input.txt");
	if (input)
	{
		int n, m;
		*input >> n >> m;
		std::vector<std::vector<int>> gr;
		gr.resize(n);
		for (int i = 0; i < m; ++i)
		{
			int a, b;
			*input >> a >> b;
			gr[a].push_back(b);
			gr[b].push_back(a);
		}
		std::set<int> bb;
		std::cout << has_path_dfs(gr, 1, 4, bb) << std::endl;
	}
}