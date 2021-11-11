#include <memory>
class Foo {
 public:
   Foo();
   ~Foo();
   void foo();
   void bar();
 private:
   struct FooImpl;
   FooImpl* m_impl;
};