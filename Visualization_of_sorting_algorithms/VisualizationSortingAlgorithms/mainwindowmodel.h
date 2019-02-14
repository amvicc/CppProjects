#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H
#include <bubblesort.h>
#include <heapsort.h>
#include <insertionsort.h>
#include <mergesort.h>
#include <quicksort.h>
#include <selectionsort.h>
#include <shellsort.h>
#include <sortingalgorithm.h>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QMetaType>
#include <QPen>
#include <iostream>
#include <vector>

typedef std::vector<double> forMergeSort;

class MainWindowModel : public QObject {
  Q_OBJECT
 private:
  std::vector<double> _columnsHeight;
  std::vector<QGraphicsRectItem *> _columns;

  double _sceneWidth;
  double _sceneHeigth;
  int _delay;

  int _sortType;

  SortingAlgorithm *_sortPtr;
  bool _sortEnable;
  bool _sorted;

  void updateColumnsArray();

 public:
  MainWindowModel();
  std::vector<double> getColumnsHeight();
  std::vector<QGraphicsRectItem *> getColumns();
  void addElement(double columnHeight);

  void setSortType(int value);

  bool getSorted();
  void setSorted(bool);

  void setSceneWidth(double value);
  void setSceneHeigth(double value);
  void setDelay(int value);
  void clear();
  void stopThread();
  bool getSortEnable();
  void startSort();
  void pause();
 private slots:
  void onComparision(int, int);
  void onSortDone();
  void onArrayAccess(int);
  void update(forMergeSort);
 signals:
  void arrayAccess(int);
  void updateWindow();
  void arraySorted();
};

#endif  // MAINWINDOWMODEL_H
