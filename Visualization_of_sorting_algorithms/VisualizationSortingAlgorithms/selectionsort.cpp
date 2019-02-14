#include "selectionsort.h"
void SelectionSort::sort() {
  int i, j, min_idx;
  int size = static_cast<int>(_array.size());

  for (i = 0; i < size - 1; i++) {
    _sync.lock();
    if (_isPaused) {
      _pauseCond.wait(&_sync);
    }
    _sync.unlock();

    min_idx = i;
    for (j = i + 1; j < size; j++)
      if (_array[static_cast<size_t>(j)] < _array[static_cast<size_t>(min_idx)])
        min_idx = j;

    swap(min_idx, i);
    _arrayAccessVariable++;
    emit arrayAccess(_arrayAccessVariable);

    msleep(_sortDelay);
  }
}
