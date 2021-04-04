#pragma once

#include <functional>
#include <chrono>
#include <vector>
#include <queue>
#include <set>

namespace path
{

#pragma region function declarations

   /// <summary>
   /// // checks if there is a way 'from' and 'to' in a 'graph' using breadth-first search
   /// </summary>
   /// <param name="graph"> Graph representation </param>
   /// <param name="from"> start point </param>
   /// <param name="to"> end point </param>
   /// <returns> 1 if there is a path, otherwise 0 </returns>
   bool has_path_bfs(const std::vector<std::vector<int>> &graph, int from, int to);

#pragma endregion

#pragma region implementation of functions

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

#pragma endregion

}
