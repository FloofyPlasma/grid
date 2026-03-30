#pragma once

#include <splice/splice.hpp>

struct SystemContext;

class ISystem
{
public:
  virtual ~ISystem() = default;

  virtual void on_start(SystemContext &context) { };
  virtual void on_tick(SystemContext &context) { };
  virtual void on_frame(SystemContext &context) { };
  virtual void on_shutdown(SystemContext &context) { };

  virtual int priority() const { return 50; }
};
