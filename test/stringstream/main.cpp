#include <iostream>
#include <string>
#include <sstream>

int main()
{
    std::stringstream ss;
    std::string s;
    ss << 5;
    ss >> s;
    std::cout << s << std::endl;
    std::string s2;
    ss >> s2;
    std::cout << s2 << std::endl;
    ss << 5;
    ss.clear();
    ss >> s2;
    std::cout << s2 << std::endl;
    ss << 5;
    ss >> s2;
    std::cout << s2 << std::endl;
    ss << 5;
    std::string s3;
    ss >> s3;
    std::cout << s3 << std::endl;
    std::stringstream ss2;
    ss2 << 5;
    ss2 >> s3;
    std::cout << s3 << std::endl;
    std::stringstream ss3;
    ss3 << " " << 5 << " " << 6 << " " << 7;
    ss3 >> s3;
    std::cout << s3 << std::endl;
    std::stringstream ss4;
    std::string s4;
    ss4 << " " << 9 << " " << 6 << " " << 7;
    ss4 >> s4;
    std::cout << s4 << std::endl;
    std::stringstream ss5;
    std::string s5;
    ss5 << 9 << " " << 6 << " " << 7;
    ss5 << 4 << " " << 6 << " " << 7;
    ss5 >> s5;
    std::cout << s5 << std::endl;
    ss5 >> s5;
    std::cout << s5 << std::endl;
    ss5 >> s5;
    std::cout << s5 << std::endl;
    ss5 >> s5;
    std::cout << s5 << std::endl;
    ss5 >> s5;
    std::cout << s5 << std::endl;
    ss5 << 5;
    ss5.clear();
    ss5 << 6;
    ss5 >> s5;
    std::cout << s5 << std::endl;
}