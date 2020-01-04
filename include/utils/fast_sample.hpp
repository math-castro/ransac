#pragma once

#include <vector>
#include <stdexcept>
#include <algorithm>

/*
*Builds a sample of size n of pop in O(n) (modifies pop)
*/
template<class T>
std::vector<T> fast_sample(std::vector<T> &pop, int n) {
  using namespace std;

  if(n > (int)pop.size())
    throw invalid_argument("The sample cannot be larger than the population");

  for(int i = 0; i < n; i++) {
    int j = i+rand()%(pop.size()-i);
    swap(pop[i], pop[j]);
  }

  vector<T> r;
  r.reserve(n);
  for(int i = 0; i < n; i++)
    r.emplace_back(pop[i]);

  return r;
}