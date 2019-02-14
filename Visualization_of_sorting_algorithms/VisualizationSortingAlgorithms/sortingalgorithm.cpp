#include "sortingalgorithm.h"

SortingAlgorithm::SortingAlgorithm(unsigned long ms, std::vector<double> array)
    : QThread(nullptr) {
  _array = array;
  _sortDelay = ms;
  _arrayAccessVariable = 0;
  _isPaused = false;
}

void SortingAlgorithm::run() {
  sort();
  emit sorted();
}

void SortingAlgorithm::setSortDelay(unsigned long ms) { _sortDelay = ms; }

void SortingAlgorithm::resume() {
  _sync.lock();
  _isPaused = false;
  _sync.unlock();
  _pauseCond.wakeAll();
}

void SortingAlgorithm::pause() {
  _sync.lock();
  _isPaused = true;
  _sync.unlock();
}

void SortingAlgorithm::swap(int first, int second) {
  std::swap(_array[static_cast<size_t>(first)],
            _array[static_cast<size_t>(second)]);
  emit comparision(first, second);
}
