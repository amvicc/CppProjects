#include "insertionsort.h"

void InsertionSort::sort() {
  int size = static_cast<int>(_array.size());
  int i, j;

  for (i = 1; i < size; i++) {
    j = i;
    _sync.lock();
    if (_isPaused) {
      _pauseCond.wait(&_sync);
    }
    _sync.unlock();

    while (j > 0 && _array[static_cast<size_t>(j)] <
                        _array[static_cast<size_t>(j - 1)]) {
      _sync.lock();
      if (_isPaused) {
        _pauseCond.wait(&_sync);
      }
      _sync.unlock();

      swap(j, j - 1);

      j -= 1;

      _arrayAccessVariable++;
      emit arrayAccess(_arrayAccessVariable);

      msleep(_sortDelay);
    }
  }
}
