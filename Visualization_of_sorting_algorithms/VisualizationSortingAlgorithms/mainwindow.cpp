#include "mainwindow.h"
#include <thread>
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  _presenter = new MainWindowPresenter();

  ui->pbStartStop->setEnabled(false);
  ui->pbReset->setEnabled(false);

  _presenter->setGraphicsView(ui->graphicsView);
  _presenter->setArrayAccesses(ui->labelArrayAccessesVar);
  _presenter->setSortingAlgorithms(ui->listSortingAlgorithms);
  _presenter->setNewArrayElement(ui->lineEnterArrayElement);
  _presenter->setLoadFromFile(ui->pbLoadArrayFromFile);
  _presenter->setDelay(ui->sliderDelay);
  _presenter->setStartOrStop(ui->pbStartStop);
  _presenter->setReset(ui->pbReset);
  _presenter->setAddElements(ui->pbAddElements);

  ui->sliderDelay->setMinimum(1);
  ui->sliderDelay->setMaximum(100);

  QObject::connect(ui->actionAbout, &QAction::triggered, this,
                   &MainWindow::onActionAbout);

  QObject::connect(ui->pbReset, &QPushButton::pressed, this,
                   &MainWindow::onResetClicked);

  QObject::connect(ui->pbLoadArrayFromFile, &QPushButton::pressed, this,
                   &MainWindow::onLoadArrayFromFileClicked);
  QObject::connect(ui->pbStartStop, &QPushButton::pressed, this,
                   &MainWindow::onStartStopClicked);
  QObject::connect(ui->pbAddElements, &QPushButton::pressed, this,
                   &MainWindow::newArrayElement);

  connect(ui->sliderDelay, SIGNAL(sliderMoved(int)),
          SLOT(onDelayValueChanged(int)));
}

MainWindow::~MainWindow() {
  delete ui;
  delete _presenter;
}

void MainWindow::onLoadArrayFromFileClicked() {
  _presenter->loadArrayFromFile();
}

void MainWindow::onStartStopClicked() { _presenter->buttonClick(); }

void MainWindow::onResetClicked() { _presenter->reset(); }

void MainWindow::onDelayValueChanged(int) { _presenter->delayValueChanged(); }

void MainWindow::newArrayElement() { _presenter->addElement(); }

void MainWindow::onActionAbout() { _presenter->about(); }
