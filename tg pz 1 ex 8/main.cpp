#include <chrono>
#include <iostream>
#include <functional>
#include <ratio>
#include <vector>




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
double execute(std::function<void()> func);

int main()
{
   


   return 0;
}

std::vector<std::vector<int>> *input(std::istream &input)
{
   if (input)
   {
      int n, m;
      input >> n >> m;
      std::vector<std::vector<int>> *graph = new std::vector<std::vector<int>>(n);
      for (int i = 0; i < m; ++i)
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

double execute(const std::function<void()> func)
{
   const auto start = std::chrono::high_resolution_clock::now();
   func();
   const auto end = std::chrono::high_resolution_clock::now();
   return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start).count();
}
