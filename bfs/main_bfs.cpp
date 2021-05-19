#include <functional>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <queue>
#include <set>

using namespace std;

bool has_path_dfs(const vector<vector<size_t>> &graph, size_t from, size_t to);

double execute(const function<void()> &func);

vector<vector<size_t>> *input(istream &in);

void add_edge(vector<vector<size_t>> &graph);

void add_vertex(vector<vector<size_t>> &graph);

void output(ostream &output, vector<vector<size_t>> &graph);

void complexity(vector<vector<size_t>> &graph, size_t from, size_t to, ostream &out);

void complexity(vector<vector<size_t>> &graph, size_t c_repeat, const function<void(vector<vector<size_t>> &)> &preaction,
   const function<bool(size_t, size_t)> &predicate, const function<size_t()> &get_from,
   const function<size_t()> &get_to, ostream &out);

int main()
{
   srand(static_cast<unsigned>(time(nullptr) / 2));

   const size_t size = 500;
   vector<vector<size_t>> graph(size);

   const size_t c_edge = size * (size - 1) / 2;
   size_t freq = c_edge / 100;
   freq = freq ? freq : 1;

   ofstream out("test_actual_edge.txt");
   complexity(graph, c_edge, add_edge, [&freq](size_t /*a*/, const size_t b) { return b % freq == 0; },
      [&size]() { return rand() % size; }, [&size]() { return rand() % size; }, cout);
   out.close();

   for (auto &i : graph)
      i.clear();
   ofstream theoretical_edge("test_theoretical_edge.txt");
   complexity(graph, c_edge, add_edge, [&freq](size_t /*a*/, const size_t b) { return b % freq == 0; },
      [&size]() { return rand() % size; }, [&size]() { return size; }, theoretical_edge);
   theoretical_edge.close();

   ofstream actual_vertex("test_actual_vertex.txt");
   complexity(graph, size * 5, add_vertex, [&freq](size_t /*a*/, const size_t b) { return b % freq == 0; },
      [&size]() { return rand() % size; }, [&size]() { return rand() % size; }, actual_vertex);
   actual_vertex.close();

   ofstream theoretical_vertex("test_theoretical_vertex.txt");
   complexity(graph, size * 5, add_vertex, [&freq](size_t /*a*/, const size_t b) { return b % freq == 0; },
      [&size]() { return rand() % size; }, [&size]() { return size; }, theoretical_vertex);
   theoretical_vertex.close();

   return 0;
}

bool has_path_bfs(const vector<vector<int>> &graph, const int from, const int to)
{
   if(from == to) return true;
   queue<int> q;
   q.push(from);
   bool *gray = new bool[static_cast<int>(graph.size())];
   gray[from] = true;
   while(!q.empty())
   {
      const int v = q.front();
      q.pop();
      for(int j : graph[v])
      {
         if(j == to) return true;
         if(gray[j]) continue;
         q.push(j);
         gray[j] = true;
      }
   }

   return false;
}

double execute(const function<void()> &func)
{
   const auto start = chrono::high_resolution_clock::now();
   func();
   const auto end = chrono::high_resolution_clock::now();
   return chrono::duration_cast<chrono::duration<double, ratio<1, 1000>>>(end - start).count();
}

vector<vector<size_t>> *input(istream &in)
{
   if (!in) return nullptr;
   int n, m;
   in >> n >> m;
   vector<vector<size_t>> *graph = new vector<vector<size_t>>(n);
   for (int i = 0; i < m; ++i)
   {
      int a, b;
      in >> a >> b;
      graph->at(a).push_back(b);
      graph->at(b).push_back(a);
   }
   return graph;
}

void output(ostream &output, vector<vector<size_t>> &graph)
{
   const auto n = graph.size();
   size_t m = 0;

   for (const auto &i : graph)
      m += i.size();
   output << n << " " << (m /= 2) << endl;

   set<size_t> marked;
   for (size_t i = 0; i < n; ++i)
   {
      marked.insert(i);
      const auto &e = graph.at(i);
      const auto s = e.size();
      for (size_t j = 0; j < s; ++j)
         if (marked.count(e.at(j)) == 0)
            output << i << " " << e.at(j) << endl;
   }
}

void add_edge(vector<vector<size_t>> &graph)
{
   size_t from = rand() % graph.size();
   for (size_t i = 0; graph[from].size() == graph.size() - 1; ++i)
   {
      if (i >= graph.size())
         return;
      ++from;
      from %= graph.size();
   }

   vector<bool> gray(graph.size(), false);

   gray[from] = true;
   for (auto v : graph[from])
      gray[v] = true;

   size_t to = rand() % graph.size();
   while (gray[to])
   {
      ++to;
      to %= graph.size();
   }

   graph[from].push_back(to);
   graph[to].push_back(from);
}

void add_vertex(vector<vector<size_t>> &graph) { graph.resize(graph.size() + 1); }

void complexity(vector<vector<size_t>> &graph, size_t from, size_t to, ostream &out)
{
   size_t m = 0;
   for (auto &i : graph)
      m += i.size();
   m /= 2;

   const auto time = execute([&graph, &from, &to]() { has_path_dfs(graph, from, to); });
   // out << graph.size() << " " << m << " " << time << " " << from << " " << to << endl;
}

void complexity(vector<vector<size_t>> &graph, size_t c_repeat, const function<void(vector<vector<size_t>> &)> &preaction,
   const function<bool(size_t, size_t)> &predicate, const function<size_t()> &get_from,
   const function<size_t()> &get_to, ostream &out)
{
   for (size_t i = 0; i < c_repeat; ++i)
   {
      preaction(graph);
      if (predicate(graph.size(), i))
         complexity(graph, get_from(), get_to(), out);
   }
}
