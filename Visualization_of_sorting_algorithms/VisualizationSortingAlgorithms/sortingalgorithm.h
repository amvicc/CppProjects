#ifndef SORTINGALGORITHM_H
#define SORTINGALGORITHM_H
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QtWidgets>

class SortingAlgorithm : public QThread {
  Q_OBJECT

 public:
  SortingAlgorithm(unsigned long, std::vector<double>);

 signals:
  void comparision(int, int);
  void sorted();
  void arrayAccess(int);
  void arrayChanged(std::vector<double>);

 protected:
  void run() override;

 public:
  virtual void sort() = 0;

  void setSortDelay(unsigned long ms);
  void resume();
  void pause();

 protected:
  std::vector<double> _array;
  unsigned long _sortDelay;
  int _arrayAccessVariable;

  QMutex _sync;
  QWaitCondition _pauseCond;
  bool _isPaused;

 protected:
  void swap(int first, int second);
};

#endif  // SORTINGALGORITHM_H
