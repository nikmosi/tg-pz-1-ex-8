#include <istream>
#include <vector>
#include <set>


/// <summary>
/// checks if there is a way 'from' and 'to' in a 'graph' using Depth-first search
/// </summary>
/// <param name="graph"> Graph representation </param>
/// <param name="from"> start point </param>
/// <param name="to"> end point </param>
/// <returns> 1 if there is a path, otherwise 0 </returns>
bool has_path_dfs(const std::vector<std::vector<int>> &graph, int from, int to);

/// <summary>
/// checks if there is a way 'from' and 'to' in a 'graph' using Depth-first search.
/// </summary>
/// <param name="graph"> Graph representation </param>
/// <param name="from"> start point </param>
/// <param name="to"> end point </param>
/// <param name="gray"> set of marked points </param>
/// <returns> 1 if there is a path, otherwise 0 </returns>
bool dfs(const std::vector<std::vector<int>> &graph, int from, int to, std::set<int> &gray);

/// <summary>
/// creates a graph view from an input stream
/// </summary>
/// <param name="input"></param>
/// <returns> graph representation </returns>
std::vector<std::vector<int>> *input(std::istream &input);

/// <summary>
/// creates a graph view in an output stream
/// </summary>
/// <param name="output"></param>
/// <param name="graph"> graph representation </param>
void output(std::ostream &output, std::vector<std::vector<int>> &graph);

int main(int argc, char *argv[])
{
}

bool has_path_dfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
{
   std::set<int> t;
   return dfs(graph, from, to, t);
}

bool dfs(const std::vector<std::vector<int>> &graph, const int from, const int to, std::set<int> &gray)
{
   gray.insert(from);
   if(from == to) return true;
   for(int j : graph[from])
   {
      if(gray.count(j) != 0) continue;
      if(dfs(graph, j, to, gray)) return true;
   }
   return false;
}

std::vector<std::vector<int>> *input(std::istream &input)
{
   if(input)
   {
      int n, m;
      input >> n >> m;
      std::vector<std::vector<int>> *graph = new std::vector<std::vector<int>>(n);
      for(int i = 0; i < m; ++i)
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

void output(std::ostream &output, const std::vector<std::vector<int>> *&graph)
{
   const auto n = graph->size();
   auto m = 0;

   for (const auto &i : graph)
      m += i.size();
   m /= 2;
   output << n << " " << m << std::endl;

   for (size_t i = 0; i < n; ++i)
   {
      const auto &e = graph->at(i);
      const auto s = e.size();
      for (size_t j = 0; j < s; ++j)
         output << i << e.at(j) << std::endl;
   }
}

