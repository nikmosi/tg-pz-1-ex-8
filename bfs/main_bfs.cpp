#include <chrono>
#include <functional>
#include <vector>
#include <queue>
#include <ratio>
#include <set>

double execute(const std::function<void()>& func);

std::vector<std::vector<int>>* input(std::istream& input);

void output(std::ostream& output, std::vector<std::vector<int>>& graph);

bool has_path_bfs(const std::vector<std::vector<int>> &graph, int from, int to);

int main(int argc, char *argv[])
{
   
}

bool has_path_bfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
{
   std::queue<int> q;
   q.push(from);
   std::set<int> gray;
   while(!q.empty())
   {
      int v = q.front();
      q.pop();
      gray.insert(v);
      for(int j : graph[v])
      {
         if (j == to) return true;
         if(gray.count(j) == 0)
         {
            q.push(j);
            gray.insert(j);
         }
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