#include <iostream>
#include <string>
#include <regex>

int count_word(std::string const& tString) {
  std::regex reg{R"(([a-zA-Z0-9]+))"};
  std::sregex_iterator begin {tString.begin(), tString.end(), reg};
  std::sregex_iterator end = std::sregex_iterator();
  for(auto i = begin; i != end; ++i) {
    std::cout << i->str() << '\n';
  }
  return std::distance(begin, end);
}

int main() {
  std::cout << count_word(" ..?.-=  he110 wo3ld fr0m Nowh3r3!!!!! . ") << '\n';
}
