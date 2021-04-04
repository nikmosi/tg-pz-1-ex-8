#include "pch.h"
#include "CppUnitTest.h"

#include <chrono>
#include <functional>
#include <queue>
#include <set>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

std::vector<std::vector<int>> *input(std::istream &input);
bool has_path_dfs(const std::vector<std::vector<int>> &graph, int from, int to);
bool dfs(const std::vector<std::vector<int>> &graph, int from, int to, std::set<int> &gray);
bool has_path_bfs(const std::vector<std::vector<int>> &graph, int from, int to);

const auto *GRAPHS = new std::vector<std::vector<int>>*[] // graph collection
{
   input(*new std::stringstream(
      "18\n0 1\n1 2\n2 3\n3 4\n4 5\n5 6\n6 7\n7 8\n8 9\n9 10\n10 11\n11 12\n12 13\n13 14\n14 7\n8 12\n10 14\n11 1\n5 7\n5 15\n15 13\n15 2\n16 4\n16 1\n16 13\n0 11\n")),
   input(*new std::stringstream("7\n0 1\n1 2\n2 3\n3 4\n4 5\n5 6\n6 0\n")),
   input(*new std::stringstream(
      "13\n0 1\n1 2\n1 3\n1 4\n1 6\n2 6\n6 5\n5 4\n7 8\n8 9\n8 10\n8 11\n9 10\n10 11\n11 12\n")),
   input(*new std::stringstream(
      "16\n0 1\n0 2\n0 3\n1 4\n1 5\n2 6\n2 7\n3 8\n3 9\n4 10\n4 11\n4 12\n5 13\n5 14\n6 15\n")),
};

namespace pathfinder_tests
{
   TEST_CLASS(pathfinder_bfs)
   {
   public:

      std::function<bool(std::vector<std::vector<int>>, int, int)> finder = has_path_bfs;

      TEST_METHOD(test01)
      {
         Assert::AreEqual(finder(*GRAPHS[0], 1, 11), true);
      }

      TEST_METHOD(test02)
      {
         Assert::AreEqual(finder(*GRAPHS[0], 6, 17), false);
      }

      TEST_METHOD(test03)
      {
         Assert::AreEqual(finder(*GRAPHS[0], 7, 0), true);
      }

      TEST_METHOD(test04)
      {
         Assert::AreEqual(finder(*GRAPHS[0], 7, 0), true);
      }

      TEST_METHOD(test05)
      {
         Assert::AreEqual(finder(*GRAPHS[1], 1, 4), true);
      }

      TEST_METHOD(test06)
      {
         Assert::AreEqual(finder(*GRAPHS[1], 4, 0), true);
      }

      TEST_METHOD(test07)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 1, 12), false);
      }

      TEST_METHOD(test08)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 1, 7), false);
      }

      TEST_METHOD(test09)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 1, 6), true);
      }

      TEST_METHOD(test10)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 6, 0), true);
      }

      TEST_METHOD(test11)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 10, 4), false);
      }

      TEST_METHOD(test12)
      {
         Assert::AreEqual(finder(*GRAPHS[3], 0, 15), true);
      }

      TEST_METHOD(test13)
      {
         Assert::AreEqual(finder(*GRAPHS[3], 7, 6), true);
      }
   };

   TEST_CLASS(pathfinder_dfs)
   {
   public:

      std::function<bool(std::vector<std::vector<int>>, int, int)> finder = has_path_dfs;

      TEST_METHOD(test01)
      {
         Assert::AreEqual(finder(*GRAPHS[0], 1, 11), true);
      }

      TEST_METHOD(test02)
      {
         Assert::AreEqual(finder(*GRAPHS[0], 6, 17), false);
      }

      TEST_METHOD(test03)
      {
         Assert::AreEqual(finder(*GRAPHS[0], 7, 0), true);
      }

      TEST_METHOD(test04)
      {
         Assert::AreEqual(finder(*GRAPHS[0], 7, 0), true);
      }

      TEST_METHOD(test05)
      {
         Assert::AreEqual(finder(*GRAPHS[1], 1, 4), true);
      }

      TEST_METHOD(test06)
      {
         Assert::AreEqual(finder(*GRAPHS[1], 4, 0), true);
      }

      TEST_METHOD(test07)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 1, 12), false);
      }

      TEST_METHOD(test08)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 1, 7), false);
      }

      TEST_METHOD(test09)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 1, 6), true);
      }

      TEST_METHOD(test10)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 6, 0), true);
      }

      TEST_METHOD(test11)
      {
         Assert::AreEqual(finder(*GRAPHS[2], 10, 4), false);
      }

      TEST_METHOD(test12)
      {
         Assert::AreEqual(finder(*GRAPHS[3], 0, 15), true);
      }

      TEST_METHOD(test13)
      {
         Assert::AreEqual(finder(*GRAPHS[3], 7, 6), true);
      }
   };
}


std::vector<std::vector<int>> *input(std::istream &input)
{
   if(input)
   {
      int n, m;
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

bool has_path_dfs(const std::vector<std::vector<int>> &graph, const int from, const int to)
{
   std::set<int> t;
   return dfs(graph, from, to, t);
}

bool dfs(const std::vector<std::vector<int>> &graph, const int from, const int to, std::set<int> &gray)
{
   if(from == to) return true;
   gray.insert(from);
   for(int j : graph[from])
   {
      if(gray.count(j) != 0) continue;
      if(dfs(graph, j, to, gray)) return true;
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
