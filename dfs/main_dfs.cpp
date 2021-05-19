#include <functional>
#include <iostream>
#include <vector>
#include <chrono>
#include <stack>
#include <set>

bool has_path_dfs(const std::vector<std::vector<int>> &graph, int from, int to);

double execute(const std::function<void()> &func);

std::vector<std::vector<int>> *input(std::istream &input);

void output(std::ostream &output, std::vector<std::vector<int>> &graph);

std::vector<std::vector<int>> *get_full_graph(const int size);

void move_an_edge(std::vector<std::vector<int>> &from, std::vector<std::vector<int>> &to);

void theoretical_complexity(int size);
void actual_complexity(int size);

int main(int argc, char *argv[])
{
   actual_complexity(1000);

   return 0;
}

bool has_path_dfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
{
   if(from == to) return true;
   bool marked[graph.size()];
   marked[from] = true;
   std::stack<int> p;
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

double execute(const std::function<void()> &func)
{
   const auto start = std::chrono::high_resolution_clock::now();
   func();
   const auto end = std::chrono::high_resolution_clock::now();
   return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start).count();
}

std::vector<std::vector<int>> *input(std::istream &input)
{
   if (input)
   {
      int n, m;
      input >> n >> m;
      std::vector<std::vector<int>> *graph = new std::vector<std::vector<int>>(n);
      for (int i = 0; i < m; ++i)
      {
         int a, b;
         input >> a >> b;
         graph->at(a).push_back(b);
         graph->at(b).push_back(a);
      }
      return graph;
   }
   return nullptr;
}

void output(std::ostream &output, std::vector<std::vector<int>> &graph)
{
   const auto n = graph.size();
   auto m = 0;

   for (const auto &i : graph)
      m += i.size();
   m /= 2;
   output << n << " " << m << std::endl;

   std::set<int> marked;
   for (size_t i = 0; i < n; ++i)
   {
      marked.insert(i);
      const auto &e = graph.at(i);
      const auto s = e.size();
      for (size_t j = 0; j < s; ++j)
         if (marked.count(e.at(j)) == 0)
            output << i << " " << e.at(j) << std::endl;
   }
}

std::vector<std::vector<int>> *get_full_graph(const int size)
{
   std::vector<int> v(size);
   for(int i = 0; i < size; ++i) v[i] = i;
   auto *graphs = new std::vector<std::vector<int>>(size, v);
   return graphs;
}

void move_an_edge(std::vector<std::vector<int>> &from, std::vector<std::vector<int>> &to)
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
   const auto it = std::find(t.begin(), t.end(), from_vertex);
   if(it != t.end())
      t.erase(it);
}

void theoretical_complexity(const int size)
{
   std::srand(static_cast<unsigned>(time(nullptr) / 2));

   std::vector<std::vector<int>> full_graph = *get_full_graph(size);
   std::vector<std::vector<int>> gr(size);

   const int c_edge = size * (size - 1) / 2;
   for (int i = 0; i < c_edge; ++i)
   {
      move_an_edge(full_graph, gr);

      if ((i + 1) % 100) continue;
      const auto time = execute([&gr, &size]() { has_path_dfs(gr, 1, size); });
      printf_s("%d;%lf;\n", i + 1, time);
   }
}

void actual_complexity(const int size)
{
   std::srand(static_cast<unsigned>(time(nullptr) / 2));

   std::vector<std::vector<int>> full_graph = *get_full_graph(size);
   std::vector<std::vector<int>> gr(size);

   const int c_edge = size * (size - 1) / 2;
   for (int i = 0; i < c_edge; ++i)
   {
      move_an_edge(full_graph, gr);

      if ((i + 1) % 100) continue;
      int from = rand() % size, to = rand() % size;
      const auto time = execute([&gr, &from, &to]() { has_path_dfs(gr, from, to); });
      printf_s("%d;%lf;\n", i + 1, time);
   }
}