#pragma once

#include <vector>
#include <set>

namespace path
{

#pragma region function declarations

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
   bool has_path_dfs(const std::vector<std::vector<int>> &graph, int from, int to, std::set<int> &gray);

#pragma endregion

#pragma region implementation of functions

   bool has_path_dfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
   {
      std::set<int> t;
      return has_path_dfs(graph, from, to, t);
   }

   bool has_path_dfs(const std::vector<std::vector<int>> &graph, const int from, const int to, std::set<int> &gray)
   {
      if (from == to) return true;
      gray.insert(from);
      for (int j : graph[from])
      {
         if (gray.count(j) != 0) continue;
         if (has_path_dfs(graph, j, to, gray)) return true;
      }
      return false;
   }

#pragma endregion

}
