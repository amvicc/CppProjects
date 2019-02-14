#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "mainwindowpresenter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  MainWindowPresenter *_presenter;

 private slots:
  void onActionSelectDir();
  void onActionAbout();
  void onLineEditTextChange(QString);
  void onPbSearchClick();
};

#endif  // MAINWINDOW_H
