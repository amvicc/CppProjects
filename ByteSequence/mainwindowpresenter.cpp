#include "mainwindowpresenter.h"
#include <QLabel>
MainWindowPresenter::MainWindowPresenter() {
  _model = new MainWindowModel();
  connect(_model, SIGNAL(ready()), SLOT(onReady()));
}

MainWindowPresenter::~MainWindowPresenter() { delete _model; }

void MainWindowPresenter::setLinePattern(QLineEdit *linePattern) {
  _linePattern = linePattern;
}

void MainWindowPresenter::setListSequences(QListWidget *listSequences) {
  _listSequences = listSequences;
}

void MainWindowPresenter::setPbSearch(QPushButton *pbSearch) {
  _pbSearch = pbSearch;
}

void MainWindowPresenter::setLabel(QLabel *label) { _label = label; }

void MainWindowPresenter::setBunberOfSequences(QLabel *numberOfSequnces) {
  _numberOfSequnces = numberOfSequnces;
}

void MainWindowPresenter::selectDir() {
  auto OutputFolder = QFileDialog::getExistingDirectory(
      nullptr, ("Select Output Folder"), QDir::currentPath());
  _model->setDir(OutputFolder);
}

void MainWindowPresenter::search() {
  if (_model->checkData()) {
    _numberOfSequnces->setText("");
    _pbSearch->setEnabled(false);
    _label->setText("Search started!!!");
    _listSequences->clear();
    _model->search();
  } else {
    QMessageBox msg;
    msg.setText("Select directory!!!");
    msg.exec();
    return;
  }
}

void MainWindowPresenter::newPattern(QString value) {
  value = value.toUpper();
  _linePattern->setText(value);

  if (value.size() % 2 != 0) {
    _pbSearch->setEnabled(false);
  } else {
    QRegExp reg("[0-9A-F]+");

    if (value != "") {
      if (!reg.exactMatch(value)) {
        _pbSearch->setEnabled(false);
      } else {
        _pbSearch->setEnabled(true);
        _model->setPattern(value);
      }
    } else {
      _pbSearch->setEnabled(false);
    }
  }
}

void MainWindowPresenter::about() {
  QMessageBox msg;
  msg.setText(
      "Osipov Anton\nByte sequence");
  msg.exec();
}

void MainWindowPresenter::onReady() {
  auto items = _model->getItems();
  _pbSearch->setEnabled(true);
  _label->setText("");
  if (items.size() != 0) {
    _listSequences->addItems(items);
    _numberOfSequnces->setText(QString::number(items.size()));
    QMessageBox msg;
    msg.setText("Sequences founded!!");
    msg.exec();
  } else {
    QMessageBox msg;
    msg.setText("No sequnces found");
    msg.exec();
    return;
  }
}
