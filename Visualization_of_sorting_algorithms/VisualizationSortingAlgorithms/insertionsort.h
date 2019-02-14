#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include <sortingalgorithm.h>

class InsertionSort : public SortingAlgorithm {
 public:
  InsertionSort(unsigned long ms, std::vector<double> vec)
      : SortingAlgorithm(ms, vec) {}
  void sort() override;
};
#endif  // INSERTIONSORT_H
