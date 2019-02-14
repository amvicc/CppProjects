#include "heapsort.h"

void HeapSort::sort() {
  int n = static_cast<int>(_array.size());

  for (int i = n / 2 - 1; i >= 0; i--) {
    _sync.lock();
    if (_isPaused) {
      _pauseCond.wait(&_sync);
    }
    _sync.unlock();
    Heapify(n, i);
  }

  for (int i = n - 1; i >= 0; i--) {
    _sync.lock();
    if (_isPaused) {
      _pauseCond.wait(&_sync);
    }
    _sync.unlock();

    swap(0, i);
    msleep(_sortDelay);
    Heapify(i, 0);
  }
}

void HeapSort::Heapify(int n, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n &&
      _array[static_cast<size_t>(l)] > _array[static_cast<size_t>(largest)])
    largest = l;

  _arrayAccessVariable++;
  emit arrayAccess(_arrayAccessVariable);

  if (r < n &&
      _array[static_cast<size_t>(r)] > _array[static_cast<size_t>(largest)])
    largest = r;

  _arrayAccessVariable++;
  emit arrayAccess(_arrayAccessVariable);

  if (largest != i) {
    swap(i, largest);
    Heapify(n, largest);

    msleep(_sortDelay);
  }
}
