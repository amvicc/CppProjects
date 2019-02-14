#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H
#include <mainwindowmodel.h>
#include <QFileDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QRegExp>

class MainWindowPresenter : public QObject {
  Q_OBJECT
 private:
  MainWindowModel *_model;

  QLineEdit *_linePattern;
  QListWidget *_listSequences;
  QPushButton *_pbSearch;
  QLabel *_label;
  QLabel *_numberOfSequnces;

 public:
  MainWindowPresenter();
  ~MainWindowPresenter();
  void setLinePattern(QLineEdit *linePattern);
  void setListSequences(QListWidget *listSequences);
  void setPbSearch(QPushButton *pbSearch);
  void setLabel(QLabel *label);
  void setBunberOfSequences(QLabel *numberOfSequnces);

  void selectDir();
  void search();
  void newPattern(QString);
  void about();
 private slots:
  void onReady();
};

#endif  // MAINWINDOWPRESENTER_H
