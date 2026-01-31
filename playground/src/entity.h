#pragma once

class Entity {
public:
  // you must do 0 so that it's a pure virtual method, having all methods a pure
  // virtual means the class becomes an abstract and can never be initiated. So
  // we will never be able to new Application() for example.
  virtual void update() = 0;
  virtual void render() = 0;
};
