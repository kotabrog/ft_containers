#include <iostream>
#include <string>
#include <algorithm>

template <class X, class Y>
void compare_test(const X& x, const Y& y)
{
  if (std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end())) {
    std::cout << "x less than y" << std::endl;
  }
  else {
    std::cout << "x not less than y" << std::endl;
  }

  // 比較演算のカスタマイズバージョン
  if (std::lexicographical_compare(x.begin(), x.end(),
                                   y.begin(), y.end(), std::greater<char>())) {
    std::cout << "x less than y" << std::endl;
  }
  else {
    std::cout << "x not less than y" << std::endl;
  }
}

int main()
{
  // 同じ長さの文字列比較
  {
    std::string x = "heilo";
    std::string y = "hello";

    std::cout << "same length string compare:" << std::endl;
    compare_test(x, y);
  }
  std::cout << std::endl;

  // 異なる長さの文字列比較
  {
    std::string x = "hell";
    std::string y = "hello";

    std::cout << "not same length string compare:" << std::endl;
    compare_test(x, y);
  }
}