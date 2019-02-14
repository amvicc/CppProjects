#include "quicksort.h"

void QuickSort::sort() { quickSort(0, static_cast<int>(_array.size() - 1)); }

void QuickSort::quickSort(int arrayBegin, int arrayEnd) {
  if (arrayBegin < arrayEnd) {
    auto pi = quickSortPartition(arrayBegin, arrayEnd);

    quickSort(arrayBegin, pi - 1);
    quickSort(pi + 1, arrayEnd);
  }
}

int QuickSort::quickSortPartition(int arrayBegin, int arrayEnd) {
  auto pivot = _array[static_cast<size_t>(arrayEnd)];
  auto i = (arrayBegin - 1);

  for (auto j = arrayBegin; j <= arrayEnd - 1; j++) {
    _sync.lock();
    if (_isPaused) {
      _pauseCond.wait(&_sync);
    }
    _sync.unlock();

    if (_array[static_cast<size_t>(j)] <= pivot) {
      i++;
      swap(i, j);
    }
    _arrayAccessVariable++;
    emit arrayAccess(_arrayAccessVariable);
    msleep(_sortDelay);
  }

  swap(i + 1, arrayEnd);

  msleep(_sortDelay);
  return (i + 1);
}
