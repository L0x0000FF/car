#include "statistic.hpp"
#include "algorithm"

std::vector<float> statisticAnalyze(const std::vector<float> &dataSet, bool variance, bool min, bool max, bool median) {
  using namespace std;
  vector<float> result;
  int n = dataSet.size();
  if (n == 0)return result;
  //Mean
  float Mean = 0;
  for (int i = 0; i < n; i++)Mean += dataSet[i];
  Mean /= n;
  result.push_back(Mean);
  //variance
  if (variance) {
    float Variance = 0;
    for (int i = 0; i < n; i++)Variance += (dataSet[i] - Mean) * (dataSet[i] - Mean);
    Variance /= (n - 1);
    result.push_back(Variance);
  }
  //min
  if (min) {
    result.push_back(*min_element(dataSet.begin(), dataSet.end()));
  }
  //max
  if (max) {
    result.push_back(*max_element(dataSet.begin(), dataSet.end()));
  }
  //median
  if (median) {
    vector<float> tmp = dataSet;
    std::sort(tmp.begin(), tmp.end());
    result.push_back(tmp[n / 2]);
  }
  return result;
}

