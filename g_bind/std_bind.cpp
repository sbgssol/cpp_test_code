/*
 * This code just play around with std::bind
 */
#include <functional>

#include <string>
#include <iostream>

class Bar {
public:
  void bar(std::string const & s) { 
    std::cout << "bar: " << s << '\n';
  }
};

void foo(std::string const & s, int i) {
  std::cout << s << " " << i << '\n';
}

int main() {
  // 1. Bind arguments specific
  auto f1 = std::bind(&foo, "Hello world!", 2);
  f1();
  
  // 2. Bind arguments with user value
  int i = 10;
  auto f2 = std::bind(&foo, "Hello world!", i);
  i = 12;
  f2(); // i was captured by value
  auto f22 = std::bind(&foo, "Hello world!", std::ref(i));
  i = -1;
  f22();
  
  // 3. Pass argument as normal
  auto f3 = std::bind(&foo, std::placeholders::_1, std::placeholders::_2);
  f3("Hello", 3);
  f3("hello", 3, 1,12,312,31,23,123,3); // even pass more arguments as available???
  
  // 4. Change argument order
  auto f4 = std::bind(&foo, std::placeholders::_2, std::placeholders::_1);
  f4(4, "World!");
  
  //5. Bind methods
  Bar b;
  auto f5 = std::bind(&Bar::bar, b, "Hello");
  f5();
  
  return 0;
}

