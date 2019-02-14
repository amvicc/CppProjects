#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H
#include <findsequence.h>
#include <QDir>

class MainWindowModel : public QObject {
  Q_OBJECT
 private:
  QDir _dir;
  QString _pattern;
  QStringList _list;
  FindSequence *_findsequence;
 signals:
  void ready();

 public:
  MainWindowModel();
  void setDir(QString path);
  void setPattern(QString pattern);
  QStringList getItems();

  bool checkData();
  void search();
 private slots:
  void onReady();
};

#endif  // MAINWINDOWMODEL_H
