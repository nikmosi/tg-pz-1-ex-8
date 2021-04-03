#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

bool has_path_dfs(const std::vector<std::vector<int>> &gr, const int fr, const int to, std::set<int> &gray)
{
	if (fr == to) return true;
	gray.insert(fr);
	for (int j : gr[fr])
	{
		if (gray.count(j) != 0) continue;
		if (has_path_dfs(gr, j, to, gray)) return true;
	}
	return false;
}



bool has_path_bfs(const std::vector<std::vector<int>> &gr, const int fr, const int to)
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

std::vector<std::vector<int>> *input(const char file_name[])
{
	auto *input = new std::ifstream(file_name);
	if (input)
	{
		int n, m;
		*input >> n >> m;
		std::vector<std::vector<int>> *gr = new std::vector<std::vector<int>>(n);
		for (int i = 0; i < m; ++i)
		{
			int a, b;
			*input >> a >> b;
			gr->at(a).push_back(b);
			gr->at(b).push_back(a);
		}
		return gr;
	}
	return nullptr;
}

int main()
{
	auto *gr = input("input.txt");
	if (gr)
	{
		std::set<int> bb;
		std::cout << has_path_dfs(*gr, 1, 4, bb) << std::endl;
	}

	return 0;
}
