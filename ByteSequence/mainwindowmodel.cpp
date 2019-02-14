#include "mainwindowmodel.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

MainWindowModel::MainWindowModel() { _findsequence = nullptr; }

void MainWindowModel::setDir(QString path) { _dir = QDir(path); }

void MainWindowModel::setPattern(QString pattern) { _pattern = pattern; }

QStringList MainWindowModel::getItems() { return _list; }

bool MainWindowModel::checkData() {
  if (_dir.path() == ".") {
    return false;
  } else {
    return true;
  }
}

void MainWindowModel::search() {
  _findsequence = new FindSequence(_dir, _pattern);
  connect(_findsequence, SIGNAL(workEnd()), SLOT(onReady()));
  _findsequence->start();
}

void MainWindowModel::onReady() {
  _list = _findsequence->getList();
  _findsequence->quit();
  _findsequence = nullptr;
  emit ready();
}
