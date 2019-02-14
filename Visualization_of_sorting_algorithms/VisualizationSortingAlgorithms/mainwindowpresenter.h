#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H
#include <mainwindowmodel.h>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QRegExp>
#include <QSlider>

class MainWindowPresenter : public QObject {
  Q_OBJECT
 private:
  QGraphicsView *_graphicsView;
  QLabel *_arrayAccesses;
  QListWidget *_sortingAlgorithms;
  QLineEdit *_newArrayElement;
  QPushButton *_loadArrayFromFile;
  QSlider *_delay;
  QPushButton *_startOrStop;
  QPushButton *_reset;
  QPushButton *_addElements;

  QGraphicsScene *_scene;
  MainWindowModel *_model;

 private:
  void updateScene();
  void clearScene();

 public:
  MainWindowPresenter();
  ~MainWindowPresenter();

  void buttonClick();
  void reset();

  void addElement();
  void loadArrayFromFile();
  void delayValueChanged();
  void about();

  void setGraphicsView(QGraphicsView *view);
  void setArrayAccesses(QLabel *label);
  void setSortingAlgorithms(QListWidget *list);
  void setNewArrayElement(QLineEdit *line);
  void setLoadFromFile(QPushButton *button);
  void setDelay(QSlider *slider);
  void setStartOrStop(QPushButton *button);
  void setReset(QPushButton *button);
  void setAddElements(QPushButton *button);
 private slots:
  void onArrayAccess(int value);
  void onUpdateWindow();
  void onArraySorted();
};

#endif  // MAINWINDOWPRESENTER_H
