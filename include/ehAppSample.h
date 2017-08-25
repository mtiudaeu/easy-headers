#include "ehLogger.h"

#include <iostream>

namespace eh {

struct App {

  eh::Msg::Separator msgSeparator;
  struct Module : public eh::Logger::Module {
    virtual std::string toString() const override { return ""; }
    virtual void overrideStream(std::ostream *&os) const override {
      os = &std::cout;
    }
  } logModule;

  static const App &get() {
    static App app;
    return app;
  }

private:
  App() {}

  App(const App &) = delete;
  App &operator=(const App &) = delete;
};
}

#define LOG(...)                                                               \
  (eh::Logger::log(eh::App::get().logModule, eh::App::get().msgSeparator,      \
                   __VA_ARGS__, EH_BUILD_FILE_INFO));
