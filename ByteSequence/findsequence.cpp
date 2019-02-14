#include "findsequence.h"

void FindSequence::run() {
  search();
  emit workEnd();
}

std::vector<char> FindSequence::HexToBytes(std::string hex) {
  std::vector<char> bytes;

  for (unsigned int i = 0; i < hex.length(); i += 2) {
    std::string byteString = hex.substr(i, 2);
    char byte = (char)strtol(byteString.c_str(), nullptr, 16);
    bytes.push_back(byte);
  }

  return bytes;
}

std::vector<char>::iterator FindSequence::find(
    std::vector<char>::iterator begin, std::vector<char>::iterator end,
    std::vector<char> sequence) {
  return std::search(begin, end, sequence.begin(), sequence.end());
}

void FindSequence::search() {
  QFileInfoList fileInfoList;

  fileInfoList = _dir.entryInfoList(QDir::Files);
  auto sequence = HexToBytes(_pattern.toStdString());

  for (auto fileInfo : fileInfoList) {
    std::ifstream ifs(fileInfo.filePath().toStdString());

    ifs.seekg(0, std::ios::end);
    std::streamsize f_size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<char> buffer(f_size);
    ifs.read(buffer.data(), f_size);

    std::vector<char>::iterator it = buffer.begin();

    while (it != buffer.end()) {
      it = find(it, buffer.end(), sequence);
      if (it != buffer.end()) {
        ptrdiff_t position = std::distance(buffer.begin(), it);

        QString st = fileInfo.absoluteFilePath() +
                     " Sequence find at position " +
                     QString::fromStdString(std::to_string(position));
        _list.push_back(st);

        std::advance(it, sequence.size());
      }
    }
  }
}

FindSequence::FindSequence(QDir dir, QString pattern) : QThread(nullptr) {
  _dir = dir;
  _pattern = pattern;
}

QStringList FindSequence::getList() { return _list; }
