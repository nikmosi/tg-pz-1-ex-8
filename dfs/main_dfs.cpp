#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <stack>
#include <set>

using namespace std;

bool has_path_dfs(const vector<vector<int>> &graph, int from, int to);

double execute(const function<void()> &func);

vector<vector<int>> *input(istream &in);

void output(ostream &output, vector<vector<int>> &graph);

vector<vector<int>> *get_full_graph(int size);

void move_an_edge(vector<vector<int>> &from, vector<vector<int>> &to);

void theoretical_complexity(int size);
void actual_complexity(int size);

int main(int argc, char *argv[])
{
   actual_complexity(1000);

   return 0;
}

bool has_path_dfs(const vector<vector<int>> &graph, const int from, const int to)
{
   if(from == to) return true;
   bool marked[static_cast<int>(graph.size())];
   marked[from] = true;
   stack<int> p;
   p.push(from);

   while(!p.empty())
   {
      const int t = p.top();
      p.pop();
      for(int j : graph[t])
      {
         if(j == to) return true;
         if(marked[j]) continue;
         marked[j] = true;
         p.push(j);
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

vector<vector<int>> *input(istream &in)
{
   if(in)
   {
      int n, m;
      in >> n >> m;
      vector<vector<int>> *graph = new vector<vector<int>>(n);
      for(int i = 0; i < m; ++i)
      {
         int a, b;
         in >> a >> b;
         graph->at(a).push_back(b);
         graph->at(b).push_back(a);
      }
      return graph;
   }
   return nullptr;
}

void output(ostream &output, vector<vector<int>> &graph)
{
   const auto n = graph.size();
   auto m = 0;

   for(const auto &i : graph)
      m += i.size();
   m /= 2;
   output << n << " " << m << endl;

   set<size_t> marked;
   for(size_t i = 0; i < n; ++i)
   {
      marked.insert(i);
      const auto &e = graph.at(i);
      const auto s = e.size();
      for(size_t j = 0; j < s; ++j)
         if(marked.count(e.at(j)) == 0)
            output << i << " " << e.at(j) << endl;
   }
}

vector<vector<int>> *get_full_graph(const int size)
{
   vector<int> v(size);
   for(int i = 0; i < size; ++i) v[i] = i;
   auto *graphs = new vector<vector<int>>(size, v);
   return graphs;
}

void move_an_edge(vector<vector<int>> &from, vector<vector<int>> &to)
{
   size_t from_vertex = rand() % from.size();
   for(size_t i = 0; from[from_vertex].empty(); ++i)
   {
      if(i > from.size())
         return;
      ++from_vertex;
      from_vertex %= from.size();
   }
   auto &fr = from[from_vertex];
   const size_t to_vertex = rand() % fr.size();

   if(to.size() > from_vertex)
      to[from_vertex].push_back(fr[to_vertex]);
   fr.erase(fr.begin() + to_vertex);

   auto t = from[to_vertex];
   const auto it = find(t.begin(), t.end(), from_vertex);
   if(it != t.end())
      t.erase(it);
}

void theoretical_complexity(const int size, ostream &out)
{
   srand(static_cast<unsigned>(time(nullptr) / 2));

   vector<vector<int>> full_graph = *get_full_graph(size);
   vector<vector<int>> gr(size);

   const int c_edge = size * (size - 1) / 2;
   for (int i = 0; i < c_edge; ++i)
   {
      move_an_edge(full_graph, gr);

      if ((i + 1) % (c_edge / 101)) continue;
      int from = rand() % size;
      const auto time = execute([&from, &gr, &size]() { has_path_dfs(gr, from, size); });
      out << i + 1 << ";" << time << endl;
   }
}

void actual_complexity(const int size, ostream &out)
{
   srand(static_cast<unsigned>(time(nullptr) / 2));

   vector<vector<int>> full_graph = *get_full_graph(size);
   vector<vector<int>> gr(size);

   const int c_edge = size * (size - 1) / 2;
   const int freq = c_edge / 101;
   for (int i = 0; i < c_edge; ++i)
   {
      move_an_edge(full_graph, gr);

      if ((i + 1) % freq) continue;
      int from = rand() % size, to = rand() % size;
      const auto time = execute([&gr, &from, &to]() { has_path_dfs(gr, from, to); });
      out << i + 1 << ";" << time << endl;
   }
}