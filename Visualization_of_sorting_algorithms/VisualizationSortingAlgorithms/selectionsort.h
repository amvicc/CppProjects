#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H
#include <sortingalgorithm.h>
class SelectionSort : public SortingAlgorithm {
 public:
  SelectionSort(unsigned long ms, std::vector<double> vec)
      : SortingAlgorithm(ms, vec) {}
  void sort() override;
};

#endif  // SELECTIONSORT_H
