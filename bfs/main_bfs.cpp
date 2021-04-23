#include <vector>
#include <queue>
#include <set>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>


#include "../useful functions/output.h"
#include "../useful functions/input.h"
#include "../useful functions/execute.h"

/// <summary>
/// // checks if there is a way 'from' and 'to' in a 'graph' using breadth-first search
/// </summary>
/// <param name="graph"> Graph representation </param>
/// <param name="from"> start point </param>
/// <param name="to"> end point </param>
/// <returns> 1 if there is a path, otherwise 0 </returns>
bool has_path_bfs(const std::vector<std::vector<int>> &graph, int from, int to);

int main(int argc, char *argv[])
{
   auto *ss = new std::stringstream("3 3\n0 1\n0 2\n1 2\n");
   auto *os = new std::ofstream("output.txt");
   auto gr = useful_func::input(std::cin);
   const auto t = useful_func::execute([&gr]()
   {
           has_path_bfs(*gr, 0, 1);
   });
   std::cout << t << std::endl;
}

bool has_path_bfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
{
   auto *q = new std::queue<int>();
   q->push(from);
   auto *gray = new std::set<int>();
   while(!q->empty())
   {
      int v = q->front();
      q->pop();
      gray->insert(v);
      for(int j : graph[v])
      {
         if(gray->count(j) == 0) q->push(j);
         if(j == to) return true;
      }
   }

   return false;
}