#include "shellsort.h"
void ShellSort::sort() {
  int size = static_cast<int>(_array.size());

  for (int gap = static_cast<int>(findMedian()); gap > 0; gap /= 2) {
    for (int i = gap; i < size; i++) {
      for (int j = i; j >= gap && _array[static_cast<size_t>(j)] <
                                      _array[static_cast<size_t>(j - gap)];
           j -= gap) {
        _sync.lock();
        if (_isPaused) {
          _pauseCond.wait(&_sync);
        }
        _sync.unlock();

        swap(j, j - gap);
        _arrayAccessVariable++;
        emit arrayAccess(_arrayAccessVariable);

        msleep(_sortDelay);
      }
    }
  }
}

double ShellSort::findMedian() {
  double median;
  auto scores = _array;
  size_t size = scores.size();

  std::sort(scores.begin(), scores.end());

  if (size % 2 == 0) {
    median = (scores[size / 2 - 1] + scores[size / 2]) / 2;
  } else {
    median = scores[size / 2];
  }

  return median;
}
