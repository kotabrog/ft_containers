#ifndef TESTER_HPP
#define TESTER_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>

class Tester
{
private:
    struct StrTime
    {
        std::string str;
        clock_t time;
        /** Skip output when put_all_time */
        bool skip;
    };

    /** Number of hours that can be saved in time measurement */
    static const size_t TIME_BUF = 1000;

    /** Stream when outputting in batches */
    std::stringstream _ss;
    /** Saved time vector */
    std::vector<StrTime> _time_vec;

    /**
     * @brief Calculate the elapsed time from the last save time
     * @param i Index of _time_vec
     * @return double Elapsed time
     */
    double _calc_elapsed_time(size_t i);

public:
    Tester();

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
    void if_print(std::string str, bool tf, std::string true_str = "true", std::string false_str = "false");

    /**
     * @brief Filling a stream with data
     * @param data 
     */
    template <typename T>
    void set_stream(T data)
    {
        _ss << data << " ";
    }

    /**
     * @brief Output the data put in by set_stream
     */
    void put_all_stream();

    /**
     * @brief Save description and time
     * @param str
     */
    void set_time(std::string str, bool skip = false);

    /**
     * @brief Outputs the most recent measurement time
     * @param verbose 0: Time only, 1: Output with str
     */
    void put_recent_time(int verbose = 1);

    /**
     * @brief Output all measurement results
     * @param verbose 0: Time only, 1: Output with str
     */
    void put_all_time(int verbose = 1);
};

#endif
