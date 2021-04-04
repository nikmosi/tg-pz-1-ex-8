#include <functional>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <queue>
#include <set>

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
/// <param name="file_name"> path to file or file name </param>
/// <returns> Graph representation </returns>
std::vector<std::vector<int>> *input(const char file_name[]);

/// <summary>
/// calculates the execution time of a 'func'
/// </summary>
/// <param name="func"> func or lambda </param>
/// <returns> returns the execution time 'func' in ms </returns>
double execute(std::function<void()> func);

#pragma endregion 

int main()
{
   auto *graph = input("input.txt");
   if(graph)
      std::cout << has_path_dfs(*graph, 1, 4) << std::endl;
   bool r = 0;
   const double time = execute([graph, &r]() { r = has_path_dfs(*graph, 1, 4); });
   std::cout << time << std::endl << r << std::endl;


   return 0;
}

#pragma region implementation of functions

bool has_path_dfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
{
   std::set<int> t;
   return has_path_dfs(graph, from, to, t);
}

bool has_path_dfs(const std::vector<std::vector<int>> &graph, const int from, const int to, std::set<int> &gray)
{
   if(from == to) return true;
   gray.insert(from);
   for(int j : graph[from])
   {
      if(gray.count(j) != 0) continue;
      if(has_path_dfs(graph, j, to, gray)) return true;
   }
   return false;
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

std::vector<std::vector<int>> *input(const char file_name[])
{
   auto *input = new std::ifstream(file_name);
   if(input)
   {
      int n, m;
      *input >> n >> m;
      std::vector<std::vector<int>> *graph = new std::vector<std::vector<int>>(n);
      for(int i = 0; i < m; ++i)
      {
         int a, b;
         *input >> a >> b;
         graph->at(a).push_back(b);
         graph->at(b).push_back(a);
      }
      return graph;
   }
   return nullptr;
}

double execute(const std::function<void()> func)
{
   const auto start = std::chrono::high_resolution_clock::now();
   func();
   const auto end = std::chrono::high_resolution_clock::now();
   return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start).count();
}

#pragma endregion 
