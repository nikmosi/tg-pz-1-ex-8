#pragma once

#include "pathfinder_dfs.h"

namespace path
{
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
}
