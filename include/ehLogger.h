#ifndef EH_LOGGER_H
#define EH_LOGGER_H

#include "ehMsg.h"

namespace eh {
namespace Logger {

struct Module {
  virtual ~Module() {}
  virtual std::string toString() const { return ""; }
  friend std::ostream &operator<<(std::ostream &os, const Module &module) {
    os << module.toString();
    return os;
  }
  virtual void overrideStream(std::ostream *&) const {}
  virtual bool isActive() const { return true; }
};

template <typename... Ts>
inline void log(const Module &module, const eh::Msg::Separator &separator,
                const Ts &... args) {
  std::ostream *os = nullptr;

  if (!module.isActive()) {
    return;
  }
  module.overrideStream(os);
  if (!os) {
    return;
  }

  (*os) << eh::Msg::build(separator, module, args...) << '\n';
}
}
}

#endif
