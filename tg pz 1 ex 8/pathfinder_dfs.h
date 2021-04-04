#pragma once

#include <vector>
#include <set>

namespace path
{
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
}


