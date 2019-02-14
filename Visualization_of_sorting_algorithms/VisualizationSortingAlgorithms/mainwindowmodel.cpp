#include "mainwindowmodel.h"
#include <QMetaType>
#include <QWaitCondition>

MainWindowModel::MainWindowModel() {
  _sortPtr = nullptr;
  _delay = 1;
  _sortEnable = false;
  _sorted = false;
}

std::vector<double> MainWindowModel::getColumnsHeight() {
  return _columnsHeight;
}

std::vector<QGraphicsRectItem *> MainWindowModel::getColumns() {
  return _columns;
}

void MainWindowModel::updateColumnsArray() {
  _columns.clear();

  auto amountOfColumns = _columnsHeight.size();
  _columns.resize(static_cast<unsigned>(amountOfColumns));
  double columnsWidth;
  double maxHeight;

  if (_columns.size() == 1) {
    columnsWidth = _sceneWidth / 5;
  } else {
    columnsWidth = _sceneWidth / amountOfColumns;
  }
  maxHeight = *std::max_element(_columnsHeight.begin(), _columnsHeight.end());

  auto j = 0;
  auto k = 0.0;
  for (auto &p : _columns) {
    p = new QGraphicsRectItem;
    auto columnHeight = _columnsHeight[j] * _sceneHeigth / maxHeight;
    p->setRect(k, _sceneHeigth - columnHeight, columnsWidth, columnHeight);
    p->setBrush(QBrush(QColor(0, 0, 255)));

    if (amountOfColumns <= 200)
      p->setPen(QPen(Qt::black, 2));
    else if (amountOfColumns > 200 && amountOfColumns <= 300)
      p->setPen(QPen(Qt::black, 1));
    else
      p->setPen(Qt::NoPen);

    j++;
    k += columnsWidth;
  }
}

void MainWindowModel::addElement(double columnHeight) {
  _columnsHeight.push_back(columnHeight);
  _columns.clear();

  auto amountOfColumns = _columnsHeight.size();
  _columns.resize(static_cast<unsigned>(amountOfColumns));
  double columnsWidth;
  double maxHeight;

  if (_columns.size() == 1) {
    columnsWidth = _sceneWidth / 5;
  } else {
    columnsWidth = _sceneWidth / amountOfColumns;
  }

  maxHeight = *std::max_element(_columnsHeight.begin(), _columnsHeight.end());

  auto j = 0;
  auto k = 0.0;
  for (auto &p : _columns) {
    p = new QGraphicsRectItem;
    auto columnHeight = _columnsHeight[j] * _sceneHeigth / maxHeight;
    p->setRect(k, _sceneHeigth - columnHeight, columnsWidth, columnHeight);
    p->setBrush(QBrush(QColor(0, 0, 255)));

    if (amountOfColumns <= 200)
      p->setPen(QPen(Qt::black, 2));
    else if (amountOfColumns > 200 && amountOfColumns <= 300)
      p->setPen(QPen(Qt::black, 1));
    else
      p->setPen(Qt::NoPen);

    j++;
    k += columnsWidth;
  }
}

void MainWindowModel::setSortType(int value) { _sortType = value; }

bool MainWindowModel::getSorted() { return _sorted; }

void MainWindowModel::setSorted(bool sorted) { _sorted = sorted; }

void MainWindowModel::setSceneWidth(double value) { _sceneWidth = value; }

void MainWindowModel::setSceneHeigth(double value) { _sceneHeigth = value; }

void MainWindowModel::setDelay(int value) {
  _delay = value;
  if (_sortPtr != nullptr) {
    _sortPtr->setSortDelay(value);
  }
}

void MainWindowModel::clear() {
  _columns.clear();
  _columnsHeight.clear();
}

void MainWindowModel::stopThread() {
  _sortPtr->quit();
  _sortPtr = nullptr;
  _sortEnable = false;
}

bool MainWindowModel::getSortEnable() { return _sortEnable; }

void MainWindowModel::startSort() {
  _sortEnable = true;

  switch (_sortType) {
    case 0:
      if (_sortPtr == nullptr) {
        _sortPtr = new BubbleSort(_delay, _columnsHeight);
        connect(_sortPtr, SIGNAL(arrayAccess(int)), SLOT(onArrayAccess(int)));
        connect(_sortPtr, SIGNAL(comparision(int, int)),
                SLOT(onComparision(int, int)));
        connect(_sortPtr, SIGNAL(sorted()), SLOT(onSortDone()));
        _sortPtr->start();
      } else {
        _sortPtr->resume();
      }
      break;
    case 1:
      if (_sortPtr == nullptr) {
        _sortPtr = new InsertionSort(_delay, _columnsHeight);
        connect(_sortPtr, SIGNAL(arrayAccess(int)), SLOT(onArrayAccess(int)));
        connect(_sortPtr, SIGNAL(comparision(int, int)),
                SLOT(onComparision(int, int)));
        connect(_sortPtr, SIGNAL(sorted()), SLOT(onSortDone()));
        _sortPtr->start();
      } else {
        _sortPtr->resume();
      }
      break;
    case 2:
      if (_sortPtr == nullptr) {
        _sortPtr = new SelectionSort(_delay, _columnsHeight);
        connect(_sortPtr, SIGNAL(arrayAccess(int)), SLOT(onArrayAccess(int)));
        connect(_sortPtr, SIGNAL(comparision(int, int)),
                SLOT(onComparision(int, int)));
        connect(_sortPtr, SIGNAL(sorted()), SLOT(onSortDone()));
        _sortPtr->start();
      } else {
        _sortPtr->resume();
      }
      break;
    case 3:
      if (_sortPtr == nullptr) {
        qRegisterMetaType<forMergeSort>("forMergeSort");
        _sortPtr = new MergeSort(_delay, _columnsHeight);
        connect(_sortPtr, SIGNAL(arrayAccess(int)), SLOT(onArrayAccess(int)));
        connect(_sortPtr, SIGNAL(arrayChanged(forMergeSort)),
                SLOT(update(forMergeSort)));
        connect(_sortPtr, SIGNAL(sorted()), SLOT(onSortDone()));
        _sortPtr->start();
      } else {
        _sortPtr->resume();
      }
      break;
    case 4:
      if (_sortPtr == nullptr) {
        _sortPtr = new QuickSort(_delay, _columnsHeight);
        connect(_sortPtr, SIGNAL(arrayAccess(int)), SLOT(onArrayAccess(int)));
        connect(_sortPtr, SIGNAL(comparision(int, int)),
                SLOT(onComparision(int, int)));
        connect(_sortPtr, SIGNAL(sorted()), SLOT(onSortDone()));
        _sortPtr->start();
      } else {
        _sortPtr->resume();
      }
      break;
    case 5:
      if (_sortPtr == nullptr) {
        _sortPtr = new HeapSort(_delay, _columnsHeight);
        connect(_sortPtr, SIGNAL(arrayAccess(int)), SLOT(onArrayAccess(int)));
        connect(_sortPtr, SIGNAL(comparision(int, int)),
                SLOT(onComparision(int, int)));
        connect(_sortPtr, SIGNAL(sorted()), SLOT(onSortDone()));
        _sortPtr->start();
      } else {
        _sortPtr->resume();
      }
      break;
    case 6:
      if (_sortPtr == nullptr) {
        _sortPtr = new ShellSort(_delay, _columnsHeight);
        connect(_sortPtr, SIGNAL(arrayAccess(int)), SLOT(onArrayAccess(int)));
        connect(_sortPtr, SIGNAL(comparision(int, int)),
                SLOT(onComparision(int, int)));
        connect(_sortPtr, SIGNAL(sorted()), SLOT(onSortDone()));
        _sortPtr->start();
      } else {
        _sortPtr->resume();
      }
      break;
  }
}

void MainWindowModel::pause() { _sortPtr->pause(); }

void MainWindowModel::onComparision(int n, int k) {
  std::swap(_columnsHeight[n], _columnsHeight[k]);
  updateColumnsArray();

  emit updateWindow();
}

void MainWindowModel::onArrayAccess(int value) { emit arrayAccess(value); }

void MainWindowModel::update(forMergeSort vec) {
  _columnsHeight.clear();
  _columnsHeight = vec;
  updateColumnsArray();
  emit updateWindow();
}

void MainWindowModel::onSortDone() {
  stopThread();
  emit arraySorted();
}
