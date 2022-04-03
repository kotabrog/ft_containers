#include <iostream>

int main()
{
    try
    {
        try
        {
            throw std::range_error("error");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}