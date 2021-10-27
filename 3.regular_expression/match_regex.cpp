/*
 * This program is used to test regular expression
 */

#include <regex>
#include <string>
#include <vector>
#include <iostream>


std::vector<std::string> get_match_regex(std::string const & str, 
                                    std::string const & regex_str) {
  std::vector<std::string> result;
  std::regex regex;
  try{
    regex =std::regex{ regex_str };
  } catch(std::exception) {
    std::cout << "regex error" << '\n';
  }
  std::smatch match;
  std::regex_match(str, match, regex);
  for(size_t i = 1; i < match.size(); ++i) {
    result.emplace_back(match[i]);
  }
  return result;
}
int main() {
  std::string str = R"(some value, first one, second one, third one, last one)";
  std::string regex_str = R"(^.[^\,]+\,(.[^,]+)\,(.[^,]+)\,(.[^,]+)\,(.[^,]+)$)";
  
  auto result = get_match_regex(str, regex_str);
  for(auto str : result) {
    std::cout << "match: " << str << '\n';
  }
}




