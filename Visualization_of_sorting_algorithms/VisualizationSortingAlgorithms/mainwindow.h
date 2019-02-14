#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <mainwindowpresenter.h>
#include <QMainWindow>
#include <QSlider>

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
  void onLoadArrayFromFileClicked();
  void onStartStopClicked();
  void onResetClicked();
  void onDelayValueChanged(int);
  void newArrayElement();
  void onActionAbout();
};

#endif  // MAINWINDOW_H
