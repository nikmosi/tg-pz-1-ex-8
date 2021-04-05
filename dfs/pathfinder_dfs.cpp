#pragma once

#include "pathfinder_dfs.h"

namespace path
{
   bool has_path_dfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
   {
      std::set<int> t;
      return dfs(graph, from, to, t);
   }

   bool dfs(const std::vector<std::vector<int>> &graph, const int from, const int to, std::set<int> &gray)
   {
      gray.insert(from);
      if (from == to) return true;
      for (int j : graph[from])
      {
         if (gray.count(j) != 0) continue;
         if (dfs(graph, j, to, gray)) return true;
      }
      return false;
   }
}
