#ifndef TESTING_H
#define TESTING_H

class Testing
{
public:
  static Testing* getInstance()
  {
    static Testing instance;
    return &instance;
  }
  static void runAllTests();

private:
  Testing() = default;
  ~Testing() = default;
};
#endif
