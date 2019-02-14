#ifndef FINDSEQUENCE_H
#define FINDSEQUENCE_H
#include <QDir>
#include <QString>
#include <QStringList>
#include <QThread>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
class FindSequence : public QThread {
  Q_OBJECT

 signals:
  void workEnd();

 private:
  void run() override;

  std::vector<char> HexToBytes(std::string hex);
  std::vector<char>::iterator find(std::vector<char>::iterator begin,
                                   std::vector<char>::iterator end,
                                   std::vector<char> sequence);

  void search();

  QDir _dir;
  QString _pattern;
  QStringList _list;

 public:
  FindSequence(QDir dir, QString pattern);
  QStringList getList();
};

#endif  // FINDSEQUENCE_H
