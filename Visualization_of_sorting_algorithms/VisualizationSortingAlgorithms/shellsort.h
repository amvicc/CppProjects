#ifndef SHELLSORT_H
#define SHELLSORT_H
#include <sortingalgorithm.h>
class ShellSort : public SortingAlgorithm {
 public:
  ShellSort(unsigned long ms, std::vector<double> vec)
      : SortingAlgorithm(ms, vec) {}
  void sort() override;
  double findMedian();
};

#endif  // SHELLSORT_H
