#ifndef MERGESORT_H
#define MERGESORT_H
#include <sortingalgorithm.h>
class MergeSort : public SortingAlgorithm {
 public:
  MergeSort(unsigned long ms, std::vector<double> vec)
      : SortingAlgorithm(ms, vec) {}
  void sort() override;
  int position(int item);
  void mergeSort(int left, int right);
  void merge(int l, int m, int r);
};

#endif  // MERGESORT_H
