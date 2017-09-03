#include "ehAppSample.h"

int main() {
  std::string test = "test";
  LOG_ERROR(test, "bla", 1);
  LOG_INFO(test, "bla", 1);
  LOG_DEBUG(test, "bla", 1);
  return 0;
}
