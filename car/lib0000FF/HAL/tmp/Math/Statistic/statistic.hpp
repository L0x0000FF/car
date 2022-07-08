#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include "vector"

std::vector<float>
statisticAnalyze(const std::vector<float> &dataSet, bool variance = true, bool min = false, bool max = false,
                 bool median = false);

#endif //STATISTIC_HPP
