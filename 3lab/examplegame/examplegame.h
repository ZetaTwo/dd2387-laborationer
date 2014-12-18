#pragma once

#include "game.h"

namespace lab3 {

  class ExampleGame : public Game {
    virtual void initialize() override;
    void start_message() const;
    Identifiable::identifier_t create_map();
  };
}