#include "mergesort.h"
void MergeSort::sort() { mergeSort(0, _array.size() - 1); }

int MergeSort::position(int item) {
  return std::find(_array.begin(), _array.end(), item) - _array.begin();
}

void MergeSort::mergeSort(int left, int right) {
  if (left < right) {
    int m = left + (right - left) / 2;

    _sync.lock();
    if (_isPaused) {
      _pauseCond.wait(&_sync);
    }
    _sync.unlock();

    mergeSort(left, m);
    mergeSort(m + 1, right);

    merge(left, m, right);
  }
}

void MergeSort::merge(int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  std::vector<int> L;
  std::vector<int> R;

  for (i = 0; i < n1; i++) L[i] = _array[l + i];
  for (j = 0; j < n2; j++) R[j] = _array[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    _sync.lock();
    if (_isPaused) {
      _pauseCond.wait(&_sync);
    }
    _sync.unlock();

    if (L[i] <= R[j]) {
      _array[k] = L[i];

      msleep(_sortDelay);

      _arrayAccessVariable++;
      emit arrayAccess(_arrayAccessVariable);
      emit arrayChanged(_array);

      i++;
    } else {
      _array[k] = R[j];

      msleep(_sortDelay);

      _arrayAccessVariable++;
      emit arrayAccess(_arrayAccessVariable);
      emit arrayChanged(_array);

      j++;
    }
    k++;
  }

  while (i < n1) {
    _sync.lock();
    if (_isPaused) {
      _pauseCond.wait(&_sync);
    }
    _sync.unlock();

    _array[k] = L[i];

    msleep(_sortDelay);

    _arrayAccessVariable++;
    emit arrayAccess(_arrayAccessVariable);
    emit arrayChanged(_array);

    i++;
    k++;
  }

  while (j < n2) {
    _sync.lock();
    if (_isPaused) {
      _pauseCond.wait(&_sync);
    }
    _sync.unlock();

    _array[k] = R[j];

    msleep(_sortDelay);

    _arrayAccessVariable++;
    emit arrayAccess(_arrayAccessVariable);
    emit arrayChanged(_array);

    j++;
    k++;
  }
}
