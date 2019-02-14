#include "bubblesort.h"

void BubbleSort::sort() {
  int size = static_cast<int>(_array.size());
  for (auto i = 0; i < size; i++)
    for (auto j = 0; j < size - 1; j++) {
      _sync.lock();
      if (_isPaused) {
        _pauseCond.wait(&_sync);
      }
      _sync.unlock();

      if (_array[static_cast<size_t>(j)] > _array[static_cast<size_t>(j + 1)]) {
        swap(j, j + 1);
        _arrayAccessVariable++;
        emit arrayAccess(_arrayAccessVariable);
      }
      msleep(_sortDelay);
    }
}
