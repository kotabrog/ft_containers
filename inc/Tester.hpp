#ifndef TESTER_HPP
#define TESTER_HPP

#include <string>
#include <iostream>

class Tester
{
private:

public:
    /**
     * @brief The output will look like this: str/n
     * @param str 
     */
    void print(std::string str);

    /**
     * @brief The output will look like this: str v/n
     * @tparam T Classes that can flow directly to stream
     * @param str 
     * @param v 
     */
    template <typename T>
    void print(std::string str, T v)
    {
        std::cout << str << " " << v << std::endl;
    }

    /**
     * @brief Change the output depending on the authenticity of tf.
     * The output will look like this: str true_str/n or str false_str/n
     * @param str 
     * @param tf 
     * @param true_str 
     * @param false_str 
     */
    void if_print(std::string str, bool tf, std::string true_str, std::string false_str)
    {
        if (tf)
            std::cout << str << " " << true_str << std::endl;
        else
            std::cout << str << " " << false_str << std::endl;
    }
};

#endif
