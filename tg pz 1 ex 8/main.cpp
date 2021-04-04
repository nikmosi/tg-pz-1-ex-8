#include <functional>
#include <iostream>
#include <chrono>
#include <vector>
#include <queue>
#include <ratio>
#include <set>

bool has_path_bfs(const std::vector<std::vector<int>> &graph, int from, int to);

std::vector<std::vector<int>> *input(std::istream &input);

double execute(const std::function<void()> &func);

void print_test(std::string test_name, bool result, bool excepted_result, double time);

int main()
{
   std::function<bool(std::vector<std::vector<int>>, int, int)> finder = has_path_bfs;
   auto *graphs = new std::vector<std::vector<int>>*[] // graph collection
   {
      input(*new std::stringstream(
         "18\n0 1\n1 2\n2 3\n3 4\n4 5\n5 6\n6 7\n7 8\n8 9\n9 10\n10 11\n11 12\n12 13\n13 14\n14 7\n8 12\n10 14\n11 1\n5 7\n5 15\n15 13\n15 2\n16 4\n16 1\n16 13\n0 11\n")),
      input(*new std::stringstream("7\n0 1\n1 2\n2 3\n3 4\n4 5\n5 6\n6 0\n")),
      input(*new std::stringstream(
         "13\n0 1\n1 2\n1 3\n1 4\n1 6\n2 6\n6 5\n5 4\n7 8\n8 9\n8 10\n8 11\n9 10\n10 11\n11 12\n")),
      input(*new std::stringstream(
         "16\n0 1\n0 2\n0 3\n1 4\n1 5\n2 6\n2 7\n3 8\n3 9\n4 10\n4 11\n4 12\n5 13\n5 14\n6 15\n")),
   };

   bool result = false;
   double time = -1;

   time = execute([&result, graphs, &finder]() { result = finder(*graphs[0], 1, 11); });
   print_test("1", result, true, time);

   std::cout << "\n";
   print_test("2", result, false, execute([&result, graphs, &finder]() { result = finder(*graphs[0], 6, 17); }));

   std::cout << "\n";
   print_test("3", result, true, execute([&result, graphs, &finder]() { result = finder(*graphs[0], 7, 0); }));

   std::cout << "\n";
   print_test("4", result, true, execute([&result, graphs, &finder]() { result = finder(*graphs[0], 7, 0); }));

   std::cout << "\n";
   print_test("5", result, true, execute([&result, graphs, &finder]() { result = finder(*graphs[1], 1, 4); }));

   std::cout << "\n";
   print_test("6", result, true, execute([&result, graphs, &finder]() { result = finder(*graphs[1], 4, 0); }));

   std::cout << "\n";
   print_test("7", result, false, execute([&result, graphs, &finder]() { result = finder(*graphs[2], 1, 12); }));

   std::cout << "\n";
   print_test("8", result, false, execute([&result, graphs, &finder]() { result = finder(*graphs[2], 1, 7); }));

   std::cout << "\n";
   print_test("9", result, true, execute([&result, graphs, &finder]() { result = finder(*graphs[2], 1, 6); }));

   std::cout << "\n";
   print_test("10", result, true, execute([&result, graphs, &finder]() { result = finder(*graphs[2], 6, 0); }));

   std::cout << "\n";
   print_test("11", result, false, execute([&result, graphs, &finder]() { result = finder(*graphs[2], 10, 4); }));

   std::cout << "\n";
   print_test("12", result, true, execute([&result, graphs, &finder]() { result = finder(*graphs[3], 0, 15); }));

   std::cout << "\n";
   print_test("13", result, true, execute([&result, graphs, &finder]() { result = finder(*graphs[3], 7, 6); }));

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
      int n;
      input >> n;
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

void print_test(const std::string test_name, const bool result, const bool excepted_result, const double time)
{
   std::string test_result = "failed";
   if(result == excepted_result)
      test_result = "passed";

   std::cout << test_name << ": " << test_result << std::endl;
   std::cout << "result: " << std::to_string(result) << std::endl;
   std::cout << "excepted_result: " << excepted_result << std::endl;
   std::cout << "time: " << time << " ms" << std::endl;
}
