#include <functional>
#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
#include <ratio>
#include <set>
#include <map>

/// <summary>
/// // checks if there is a way 'from' and 'to' in a 'graph' using breadth-first search
/// </summary>
/// <param name="graph"> Graph representation </param>
/// <param name="from"> start point </param>
/// <param name="to"> end point </param>
/// <returns> 1 if there is a path, otherwise 0 </returns>
bool has_path_bfs(const std::vector<std::vector<int>> &graph, int from, int to);

/// <summary>
/// loads a graph from 'file_name'
/// </summary>
/// <param name="input">data stream</param>
/// <returns></returns>
std::vector<std::vector<int>> *input(std::istream &input);

/// <summary>
/// calculates the execution time of a 'func'
/// </summary>
/// <param name="func"> func or lambda </param>
/// <returns> returns the execution time 'func' in ms </returns>
double execute(const std::function<void()> &func);

int main()
{
   auto *graphs = new std::vector<std::vector<int>>*[] // graph collection
   {
      input(*new std::stringstream(
         "18\n0 1\n1 2\n2 3\n3 4\n4 5\n5 6\n6 7\n7 8\n8 9\n9 10\n10 11\n11 12\n12 13\n13 14\n14 7\n8 12\n10 14\n11 1\n5 7\n5 15\n15 13\n15 2\n16 4\n16 1\n16 13\n0 11\n")),
      input(*new std::stringstream("7\n0 1\n1 2\n2 3\n3 4\n4 5\n5 6\n6 0\n")),
      input(*new std::stringstream("13\n0 1\n1 2\n1 3\n1 4\n1 6\n2 6\n6 5\n5 4\n7 8\n8 9\n8 10\n8 11\n9 10\n10 11\n11 12\n")),
      input(*new std::stringstream("16\n0 1\n0 2\n0 3\n1 4\n1 5\n2 6\n2 7\n3 8\n3 9\n4 10\n4 11\n4 12\n5 13\n5 14\n6 15\n")),
   };

   

   return 0;
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

std::vector<std::vector<int>> *input(std::istream &input)
{
   if(input)
   {
      int n, m;
      input >> n >> m;
      std::vector<std::vector<int>> *graph = new std::vector<std::vector<int>>(n);
      while(!input.eof())
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

double execute(const std::function<void()> &func)
{
   const auto start = std::chrono::high_resolution_clock::now();
   func();
   const auto end = std::chrono::high_resolution_clock::now();
   return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start).count();
}
