#include "foo.hpp"
#include <iostream>

struct Foo::FooImpl {
 public:
   void do_foo() { std::cout << "do foo" << '\n'; }
   void do_bar() { std::cout << "do bar" << '\n'; }
   ~FooImpl() { std::cout << "~FooImpl()" << '\n'; }
 private:
   int x;
   int y;
};

Foo::Foo() : m_impl(new FooImpl()){}
Foo::~Foo() { delete m_impl; }

void Foo::foo() { m_impl->do_foo(); }
void Foo::bar() { m_impl->do_bar(); }