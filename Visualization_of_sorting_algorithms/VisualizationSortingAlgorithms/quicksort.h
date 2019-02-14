#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <sortingalgorithm.h>

class QuickSort : public SortingAlgorithm {
 public:
  QuickSort(unsigned long ms, std::vector<double> vec)
      : SortingAlgorithm(ms, vec) {}
  void sort() override;

 private:
  void quickSort(int arrayBegin, int arrayEnd);
  int quickSortPartition(int arrayBegin, int arrayEnd);
};

#endif  // QUICKSORT_H
