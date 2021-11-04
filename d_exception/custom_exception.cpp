#include <exception>
#include <iostream>
#include <string>

class my_exception_t : public std::exception {
 public:
   my_exception_t(std::string t_Msg) : m_msg(t_Msg) {}
   virtual char const * what() const noexcept override {
     return m_msg.c_str();
   }
 private:
   std::string m_msg;
};

class invalid_argument_exp_t : public my_exception_t {
 public:
   invalid_argument_exp_t(std::string t_Msg) : my_exception_t{
     "\"" + t_Msg + "\"" + " is an invalid argument"
   }{}
};

int main() {
  try {
    throw invalid_argument_exp_t{"seed"};
  } catch (my_exception_t& t_Exp) {
    std::cout << t_Exp.what() << '\n';
  }
}
