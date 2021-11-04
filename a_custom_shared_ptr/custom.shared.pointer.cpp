#include <iostream>
#include <string>

template<class T>
class MyShare{
  T*   ptr_;
  int* counter_;  // This counter is pointer because it can be increased
                  // when another shared_ptr points to its resource so
                  // it can be modified in the other's constructor
public:
  MyShare(T* ptr = nullptr) : ptr_(ptr), counter_(new int(0)){
    if(ptr_){
      ++(*this->counter_);
    }
  }
  MyShare(MyShare const & other) : ptr_(other.ptr_), counter_(other.counter_){
    ++(*this->counter_);
  }
  MyShare& operator=(MyShare const & other){
    this->~MyShare();
    this->ptr_ = other.ptr_;
    this->counter_ = other.counter_;
    ++(*this->counter_);
    
    return *this;
  }

  ~MyShare(){
    --(*counter_);
    if(*counter_ == 0){
      delete ptr_;
    }
  }

  int get_counter() const {
    return (*counter_);
  }
  
  T* operator->(){
    return ptr_;
  }

  T const& operator*(){
    return *ptr_;
  }

};

template<class T, class...Args>
MyShare<T> make_shared(Args... args){
  return MyShare<T>{new T{args...}};
}

struct A{
  int num_;
  std::string str_;

  A(int num, std::string str) : num_(num), str_(str){
    std::cout << "A(" << num << ", " << str << ")" << '\n';
  }
  ~A(){
    std::cout << "~A(" << num_ << ", " << str_ << ")" << '\n';
  }
};

int main() {
  MyShare<A> ptr1 {new A{1, "One"}};
  MyShare<A> ptr11 = ptr1;  
  std::cout << "Current counter: " << ptr11.get_counter() << '\n';
  std::cout << ptr11->num_ << ", " << ptr11->str_ << '\n';

  MyShare<A> ptr2 = make_shared<A>(2, "Two");
  MyShare<A> ptr3 = make_shared<A>(3, "Three");
  ptr2 = ptr11;

  // The destruction order would be: 3->2->1 based on the order of declaration
  // But the actual order must be: 2->3->1 based on the shared counter of ptr2

  return 0;
}
