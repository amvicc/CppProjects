#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <sortingalgorithm.h>

class HeapSort : public SortingAlgorithm {
 public:
  HeapSort(unsigned long ms, std::vector<double> vec)
      : SortingAlgorithm(ms, vec) {}
  void sort() override;
  void Heapify(int n, int i);
};

#endif  // HEAPSORT_H
