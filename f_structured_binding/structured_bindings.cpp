/*
 * This code is used to getting started with
 * structured bindings
 */
#include <string>
#include <iostream>
#include <tuple>

struct Person{
  std::string m_name;
  size_t      m_age;
};

Person createPerson() {
  return {"Lee", 24};
}

std::tuple<std::string, size_t> createSubject() {
  return {"Math", 4};
}

int main() {
  /* 1. Binding an array
   * Each identifier in the identifier-list becomes the name of an lvalue
   * that refers to the corresponding element of the array. 
   * The number of identifiers MUST EQUAL the number of array elements. 
   */
  int arr[3] = {1,2,3};
  auto [x,y,z] = arr; // bindings by value
  std::cout << "x: " << x << ", y: " << y << ", z: " << z << '\n';
  x = -1;
  std::cout << arr[0] << '\n';
  
  auto& [rx, ry, rz] = arr; // bindings by reference
  rx *= -1;
  ry *= -1;
  rz *= -1;
  std::cout << arr[0] << ", " << arr[1] << ", " << arr[2] << '\n';
  
  /* 2. Binding a tuple-like type
   * The number of identifiers MUST EQUAL std::tuple_size<E>::value
   * Do not need to use std::get<> to get elements of a tuple
   */
  auto [subject, score] = createSubject();
  std::cout << subject << ": " << score << '\n';
  
  /* 3. Binding to data members
   * The number of identifiers MUST EQUAL 
   * the number of non-static data members. 
   */
  auto [name, age] = createPerson();
  std::cout << name << ": " << age << '\n';
  return 0;
}
