#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->listSequences->setUniformItemSizes(true);
  ui->pbSearch->setEnabled(false);

  _presenter = new MainWindowPresenter();

  _presenter->setLinePattern(ui->linePattern);
  _presenter->setListSequences(ui->listSequences);
  _presenter->setPbSearch(ui->pbSearch);
  _presenter->setLabel(ui->labelProcess);
  _presenter->setBunberOfSequences(ui->label_3);

  QObject::connect(ui->actionAbout, &QAction::triggered, this,
                   &MainWindow::onActionAbout);
  QObject::connect(ui->actionSelectDirectory, &QAction::triggered, this,
                   &MainWindow::onActionSelectDir);

  connect(ui->linePattern, SIGNAL(textChanged(const QString &)), this,
          SLOT(onLineEditTextChange(QString)));

  QObject::connect(ui->pbSearch, &QPushButton::pressed, this,
                   &MainWindow::onPbSearchClick);
}

MainWindow::~MainWindow() {
  delete ui;
  delete _presenter;
}

void MainWindow::onActionSelectDir() { _presenter->selectDir(); }

void MainWindow::onActionAbout() { _presenter->about(); }

void MainWindow::onLineEditTextChange(QString value) {
  _presenter->newPattern(value);
}

void MainWindow::onPbSearchClick() { _presenter->search(); }
