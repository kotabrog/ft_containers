#include "Tester.hpp"

double Tester::_calc_elapsed_time(size_t i)
{
    return (double)(_time_vec[i].time - _time_vec[i - 1].time) / CLOCKS_PER_SEC;
}

Tester::Tester()
{
    _time_vec.reserve(TIME_BUF);
}

void Tester::print(std::string str)
{
    std::cout << str << std::endl;
}

void Tester::if_print(std::string str, bool tf, std::string true_str, std::string false_str)
{
    if (tf)
        std::cout << str << " " << true_str << std::endl;
    else
        std::cout << str << " " << false_str << std::endl;
}

void Tester::put_all_stream()
{
    std::cout << _ss.str() << std::endl;
    _ss.str("");
    _ss.clear();
}

void Tester::set_time(std::string str, bool skip)
{
    StrTime temp;
    _time_vec.push_back(temp);
    _time_vec[_time_vec.size() - 1].str = str;
    _time_vec[_time_vec.size() - 1].time = clock();
    _time_vec[_time_vec.size() - 1].skip = skip;
}

void Tester::put_recent_time(int verbose)
{
    if (_time_vec.size() < 2)
    {
        std::cout << "Use the set_time function at least twice" << std::endl;
    }
    else if (verbose == 0)
    {
        std::cout
            << _calc_elapsed_time(_time_vec.size() - 1)
            << "sec"
            << std::endl;
    }
    else if (verbose == 1)
    {
        std::cout
            << _time_vec[_time_vec.size() - 2].str
            << " to "
            << _time_vec[_time_vec.size() - 1].str
            << ": "
            << _calc_elapsed_time(_time_vec.size() - 1)
            << "sec"
            << std::endl;
    }
}

void Tester::put_all_time(int verbose)
{
    if (_time_vec.size() > 0 && verbose == 1)
    {
        std::cout
            << _time_vec[0].str
            << ": start\n";
    }
    double all_time = 0.0;
    for (size_t i = 1; i < _time_vec.size(); ++i)
    {
        if (_time_vec[i].skip)
        {
            if (verbose == 1)
                std::cout
                    << _time_vec[i].str
                    << "\n";
        }
        else
        {
            if (verbose == 1)
                std::cout
                    << "-> "
                    << _time_vec[i].str
                    << ": ";
            double elapsed_time = _calc_elapsed_time(i);
            all_time += elapsed_time;
            std::cout
                << elapsed_time
                << "sec\n";
        }
    }
    std::cout
        << "\nall time: "
        << all_time
        << "sec"
        << std::endl;
}

double Tester::get_elapsed_time(size_t index)
{
    return _calc_elapsed_time(index);
}

size_t Tester::get_saved_time_size()
{
    return _time_vec.size();
}
