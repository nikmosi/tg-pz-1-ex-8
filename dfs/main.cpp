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
