#pragma once

#include <queue>
#include <set>

#include "pathfinder_bfs.h"

namespace path
{
   bool has_path_bfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
   {
      auto *q = new std::queue<int>();
      q->push(from);
      auto *gray = new std::set<int>();
      while (!q->empty())
      {
         int v = q->front();
         q->pop();
         gray->insert(v);
         for (int j : graph[v])
         {
            if (gray->count(j) == 0) q->push(j);
            if (j == to) return true;
         }
      }

      return false;
   }
}
