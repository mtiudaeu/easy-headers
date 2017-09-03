#ifndef EH_MSG_H
#define EH_MSG_H

#include <sstream>
#include <string>

#define EH_BUILD_FILE_INFO eh::Msg::FileInfo(__FILE__, __LINE__)

namespace eh {
namespace Msg {

struct FileInfo {
  FileInfo(const char *filename, int linenumber)
      : m_filename(filename), m_linenumber(linenumber) {}
  const char *m_filename;
  int m_linenumber;

  friend std::ostream &operator<<(std::ostream &os, const FileInfo &fileInfo) {
    if (fileInfo.m_filename) {
      os << fileInfo.m_filename;
      os << ':';
      os << std::to_string(fileInfo.m_linenumber).c_str();
    }
    return os;
  }

  FileInfo(const FileInfo &) = delete;
  FileInfo &operator=(const FileInfo &) = delete;
};

struct Separator {
  Separator() {}
  Separator(std::string &rhs) : value(rhs) {}
  std::string value = " ";
};

template <typename T>
inline void add(const Separator, std::string &msg, const T &value) {
  std::stringstream s;
  s << value;
  msg += s.str().c_str();
}
template <>
inline void add(const Separator, std::string &msg, const std::string &value) {
  msg += value;
}
template <typename T, typename... Ts>
inline void add(const Separator &separator, std::string &msg, const T &value,
                const Ts &... args) {
  add(separator, msg, value);
  msg += separator.value;
  add(separator, msg, args...);
}

template <typename... Ts>
inline std::string build(const Separator &separator, const Ts &... args) {
  std::string msg;
  add(separator, msg, args...);
  return std::move(msg);
}
}
}

#endif
