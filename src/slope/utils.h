#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

template<typename T>
inline int
signum(T val)
{
  return (T(0) < val) - (val < T(0));
}

template<typename T>
std::vector<std::size_t>
sortIndex(const T& v, const std::string direction = "ascending")
{
  using namespace std;

  vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  if (direction == "ascending") {
    stable_sort(
      idx.begin(), idx.end(), [&v](size_t i, size_t j) { return v[i] < v[j]; });
  } else if (direction == "descending") {
    stable_sort(
      idx.begin(), idx.end(), [&v](size_t i, size_t j) { return v[i] > v[j]; });
  }

  return idx;
}

template<typename T>
void
permute(T& values, const std::vector<size_t>& ind)
{
  T out(values.size());

  auto n = values.size();

  for (decltype(n) i = 0; i < values.size(); ++i)
    out[i] = std::move(values[ind[i]]);

  values = std::move(out);
}

template<typename T>
void
inversePermute(T& values, const std::vector<size_t>& ind)
{
  T out(values.size());

  auto n = values.size();

  for (decltype(n) i = 0; i < values.size(); ++i)
    out[ind[i]] = std::move(values[i]);

  values = std::move(out);
}

template<typename T>
T
cumSum(const T& x)
{
  T out(x.size());
  std::partial_sum(x.begin(), x.end(), out.begin(), std::plus<double>());

  return out;
}

template<typename T>
T
clamp(const T& x, const T& lo, const T& hi)
{
  return x <= lo ? lo : x >= hi ? hi : x;
}

template<typename T>
void
print(const T& x)
{
  for (auto y : x) {
    std::cout << y << " ";
  }
  std::cout << std::endl;
}
