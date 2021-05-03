#include <chrono>
#include <functional>
#include <vector>
#include <set>
#include <stack>

double execute(const std::function<void()>& func);

std::vector<std::vector<int>>* input(std::istream& input);

void output(std::ostream& output, std::vector<std::vector<int>>& graph);

bool has_path_dfs(const std::vector<std::vector<int>> &graph, int from, int to);

int main(int argc, char *argv[])
{
   
}

bool has_path_dfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
{
   if(from == to) return true;
   std::set<int> marked;
   marked.insert(from);
   std::stack<int> p;
   p.push(from);

   while(!p.empty())
   {
      const int t = p.top();
      p.pop();
      for(int j : graph[t])
      {
         if(j == to) return true;
         if(marked.count(j) != 0) continue;
         marked.insert(j);
         p.push(j);
      }
   }

   return false;
}

double execute(const std::function<void()>& func)
{
   const auto start = std::chrono::high_resolution_clock::now();
   func();
   const auto end = std::chrono::high_resolution_clock::now();
   return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start).count();
}

std::vector<std::vector<int>>* input(std::istream& input)
{
   if (input)
   {
      int n, m;
      input >> n >> m;
      auto* graph = new std::vector<std::vector<int>>(n);
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

void output(std::ostream& output, std::vector<std::vector<int>>& graph)
{
   const auto n = graph.size();
   auto m = 0;

   for (const auto& i : graph)
      m += i.size();
   m /= 2;
   output << n << " " << m << std::endl;

   std::set<int> marked;
   for (size_t i = 0; i < n; ++i)
   {
      marked.insert(i);
      const auto& e = graph.at(i);
      const auto s = e.size();
      for (size_t j = 0; j < s; ++j)
         if (marked.count(e.at(j)) == 0)
            output << i << " " << e.at(j) << std::endl;
   }
}