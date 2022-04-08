#ifndef TESTER_HPP
#define TESTER_HPP

#include <string>
#include <iostream>
#include <sstream>

class Tester
{
private:
    std::stringstream ss;
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
     * @brief The output will look like this: str v1 v2/n
     * @tparam T Classes that can flow directly to stream
     * @param str 
     * @param v1 
     * @param v2 
     */
    template <typename T1, typename T2>
    void print(std::string str, T1 v1, T2 v2)
    {
        std::cout << str << " " << v1 << " " << v2 << std::endl;
    }

    /**
     * @brief Change the output depending on the authenticity of tf.
     * The output will look like this: str true_str/n or str false_str/n
     * @param str 
     * @param tf 
     * @param true_str 
     * @param false_str 
     */
    void if_print(std::string str, bool tf, std::string true_str = "true", std::string false_str = "false")
    {
        if (tf)
            std::cout << str << " " << true_str << std::endl;
        else
            std::cout << str << " " << false_str << std::endl;
    }

    /**
     * @brief Filling a stream with data
     * @param data 
     */
    template <typename T>
    void set_stream(T data)
    {
        ss << data << " ";
    }

    /**
     * @brief Output the data put in by set_stream
     */
    void put_all_stream()
    {
        std::cout << ss.str() << std::endl;
        ss.str("");
        ss.clear();
    }
};

#endif
