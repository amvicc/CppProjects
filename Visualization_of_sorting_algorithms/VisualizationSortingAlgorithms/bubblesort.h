#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include <sortingalgorithm.h>

class BubbleSort : public SortingAlgorithm {
 public:
  BubbleSort(unsigned long ms, std::vector<double> vec)
      : SortingAlgorithm(ms, vec) {}
  void sort() override;
};

#endif  // BUBBLESORT_H
