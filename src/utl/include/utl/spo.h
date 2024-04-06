#pragma once

#include <cstdint>
#include <string>

#include <spdlog/fmt/fmt.h>

namespace spo {

/*

  template <typename... Args>
  inline void warn(ToolId tool,
                   int id,
                   const std::string& message,
                   const Args&... args)
*/

extern void increaseIndentation();
extern void decreaseIndentation();
extern uint32_t currentIndentation();

template <typename... Args>
void print(const std::string& message, const Args&... args)
{
  std::string s = fmt::format(message, args...);
  printf("%*s%s\n", currentIndentation(), "", s.c_str());
}

class InvocationTracer {
public:
  template <typename... Args>
  InvocationTracer(const std::string& message, const Args&... args) {
    print(message, args...);
    increaseIndentation();
  }

  ~InvocationTracer() {
    decreaseIndentation();
  }
};

};