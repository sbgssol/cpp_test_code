#include <iostream>
#include <iomanip>


void access_primary_data() {
  std::cout << "\nACCESS PRIMARY DATA" << '\n';  
  int x = 1;
  int y = 2;  
  std::cout << "Address of x: " << &x << '\n';
  std::cout << "Address of y: " << &y << '\n';

  int* ptr = (int*)(&x - 1);
  std::cout << "ptr points to: " << ptr << '\n';

  *ptr = 3;
  std::cout << "value at " << ptr << ": " << (*ptr) << '\n';
  std::cout << "modified y via address: " << y << '\n';

  
}

void access_simple_struct() {
  std::cout << "\nACCESS SIMPLE STRUCT" << '\n';
  struct A{
  private:
    int   i_;
    char  c_;
    float f_;
  public:
    A(int i, char c, float f) : i_(i), c_(c), f_(f){}
    int   i() const {return i_; }
    char  c() const {return c_; }
    float f() const { return f_; }
  };

  A a{1, 'c', 3.14f};
  std::cout << "Original value: a.i=" << a.i() <<", a.c: " << a.c() << ", a.f: " << a.f() << '\n';
  int* pi = (int*)(&a);
  char* pc = (char*)(pi + 1);   // char was 4-byte aligned
  float* pf = (float*)(pc + 4); // pc now is a pointer to char => only increase single byte

  (*pi) = 2;
  (*pc) = 'z';
  (*pf) = 3.333f;

  std::cout << "Modified value: a.i=" << a.i() <<", a.c: " << a.c() << ", a.f: " << a.f() << '\n';
}

void access_interface() {
  std::cout << "\nACCESS INTERFACE" << '\n';
  struct Base {  
    int i_base{0xa};
    virtual void foo() = 0;
    virtual void bar() {}
  };

  struct Derived : public Base {
    char i_derived{'z'};
    virtual void foo() {}
  };

  Base* ptr = new Derived();
  char* pi_base = (char*)((char*)ptr + 8);  
  for(int i = 0; i < 4; ++i){
    *(pi_base+i) = 0xaa;
    //std::cout << (unsigned)*(pi_base+i);
  } //std::cout << '\n';
  std::cout << std::showbase << std::hex << ptr->i_base << '\n';
  
  char* pi_derived = (pi_base + 4);
  for(int i = 0; i < 4; ++i){
    std::cout << (unsigned char)*(pi_derived+i);
  } std::cout << '\n';
}

int main() {
  access_primary_data();
  access_simple_struct();
  access_interface();
  

  return 0;
}