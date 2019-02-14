#include "mainwindowpresenter.h"
#include <QObject>
MainWindowPresenter::MainWindowPresenter() {
  _scene = new QGraphicsScene();

  _model = new MainWindowModel();
  _model->setSceneHeigth(_scene->height());
  _model->setSceneWidth(_scene->width());
  connect(_model, SIGNAL(arrayAccess(int)), SLOT(onArrayAccess(int)));
  connect(_model, SIGNAL(updateWindow()), SLOT(onUpdateWindow()));
  connect(_model, SIGNAL(arraySorted()), SLOT(onArraySorted()));
}

MainWindowPresenter::~MainWindowPresenter() {
  delete _scene;
  delete _model;
}

void MainWindowPresenter::buttonClick() {
  if (_startOrStop->text() == "Start" || _startOrStop->text() == "Resume") {
    if (_sortingAlgorithms->selectedItems().empty()) {
      QMessageBox msg;
      msg.setText("Select sort!!!");
      msg.exec();
      return;
    }

    if (_model->getSorted() == true) {
      QMessageBox msg;
      msg.setText("this array is already sorted , enter new array!!!");
      msg.exec();
      return;
    }

    _addElements->setEnabled(false);
    _newArrayElement->setEnabled(false);
    _loadArrayFromFile->setEnabled(false);
    _reset->setEnabled(false);

    if (_startOrStop->text() == "Start") {
      auto sortType = _sortingAlgorithms->selectedItems()[0]->text();
      if (sortType == "Bubble sort")
        _model->setSortType(0);
      else if (sortType == "Insertion sort")
        _model->setSortType(1);
      else if (sortType == "Selection sort")
        _model->setSortType(2);
      else if (sortType == "Merge sort")
        _model->setSortType(3);
      else if (sortType == "Quick sort")
        _model->setSortType(4);
      else if (sortType == "Heap sort")
        _model->setSortType(5);
      else if (sortType == "Shell sort")
        _model->setSortType(6);
    }
    _model->startSort();
    _startOrStop->setText("Pause");
  } else {
    _startOrStop->setText("Resume");
    _reset->setEnabled(true);
    _model->pause();
  }
}

void MainWindowPresenter::reset() {
  if (_model->getSortEnable()) {
    _model->stopThread();
  }
  _model->setSorted(false);
  _arrayAccesses->setText("0");
  _newArrayElement->setEnabled(true);
  _loadArrayFromFile->setEnabled(true);
  _addElements->setEnabled(true);
  _startOrStop->setText("Start");
  _startOrStop->setEnabled(false);
  _reset->setEnabled(false);
  clearScene();
  _model->clear();
}

void MainWindowPresenter::setGraphicsView(QGraphicsView *view) {
  _graphicsView = view;
  _graphicsView->setScene(_scene);
  _model->setSceneWidth(_graphicsView->width());
  _model->setSceneHeigth(_graphicsView->height());
}

void MainWindowPresenter::setArrayAccesses(QLabel *label) {
  _arrayAccesses = label;
}

void MainWindowPresenter::setSortingAlgorithms(QListWidget *list) {
  _sortingAlgorithms = list;
}

void MainWindowPresenter::setNewArrayElement(QLineEdit *line) {
  _newArrayElement = line;
}

void MainWindowPresenter::setLoadFromFile(QPushButton *button) {
  _loadArrayFromFile = button;
}

void MainWindowPresenter::setDelay(QSlider *slider) { _delay = slider; }

void MainWindowPresenter::setStartOrStop(QPushButton *button) {
  _startOrStop = button;
}

void MainWindowPresenter::setReset(QPushButton *button) { _reset = button; }

void MainWindowPresenter::setAddElements(QPushButton *button) {
  _addElements = button;
}

void MainWindowPresenter::onArrayAccess(int value) {
  _arrayAccesses->setText(QString::number(value));
}

void MainWindowPresenter::onUpdateWindow() { updateScene(); }

void MainWindowPresenter::onArraySorted() {
  _model->setSorted(true);
  _newArrayElement->setEnabled(true);
  _loadArrayFromFile->setEnabled(true);
  _addElements->setEnabled(true);
  _startOrStop->setText("Start");
  _reset->setEnabled(true);
  QMessageBox msg;
  msg.setText("Array sorted!!!");
  msg.exec();
  return;
}

void MainWindowPresenter::updateScene() {
  clearScene();
  for (auto &p : _model->getColumns()) {
    _scene->addItem(p);
  }
}

void MainWindowPresenter::clearScene() { _scene->clear(); }

void MainWindowPresenter::addElement() {
  QString element = _newArrayElement->text();
  auto lst = element.split(" ");
  _newArrayElement->clear();

  if (element != "") {
    reset();
    for (int i = 0; i < lst.size(); i++) {
      QRegExp reg("^[1-9][0-9]*$");
      if (!reg.exactMatch(lst[i])) {
        QMessageBox msg;
        msg.setText("Wrong input!!!");
        msg.exec();
        return;
      } else {
        _model->addElement(lst[i].toDouble());
        _startOrStop->setEnabled(true);
        _reset->setEnabled(true);
      }
    }
    updateScene();
  }
}

void MainWindowPresenter::loadArrayFromFile() {
  auto filename = QFileDialog::getOpenFileName();
  QFile file(filename);
  if (file.open(QIODevice::ReadOnly)) {
    reset();
    QStringList lst;
    QList<int> numbers;

    while (!file.atEnd()) {
      QString str = file.readLine();
      lst = str.split(" ");
    }
    file.close();

    lst[lst.size() - 1] = lst[lst.size() - 1].replace("\n", "");

    for (int i = 0; i < lst.size(); i++) {
      QRegExp reg("^[1-9][0-9]*$");
      if (!reg.exactMatch(lst[i])) {
        QMessageBox msg;
        msg.setText("Wrong input in file!!!");
        msg.exec();
        return;
      } else {
        _model->addElement(lst[i].toDouble());
        _startOrStop->setEnabled(true);
        _reset->setEnabled(true);
      }
    }
    updateScene();
  }
}

void MainWindowPresenter::delayValueChanged() {
  _model->setDelay(_delay->value());
}

void MainWindowPresenter::about() {
  QMessageBox msg;
  msg.setText(
      "Oipov Anton\nVisualization sorting algorithms");
  msg.exec();
}
