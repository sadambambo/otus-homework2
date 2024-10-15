#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <arpa/inet.h>
#include "ip_filter.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    auto start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

Ipv4Descr::Ipv4Descr(const std::string &s)
{
    uint32_t buff = 0;
    //if(0 >= inet_pton(AF_INET, s.c_str(), &buff))
    //    addr = 0; // not correct ipv4 
    //addr = htonl(buff);

    for (auto i : split(s, '.'))
        buff = std::stoi(i) + buff * 256;
    
    addr = buff;
    strncpy(repr, s.c_str(), sizeof(repr));
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<Ipv4Descr> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(Ipv4Descr(v.at(0)));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](auto a, auto b){ return a.addr > b.addr;});

        // output sorted
        for(auto ip : ip_pool)
            std::cout << ip.repr << std::endl;

        // filter by first byte and output
        for(auto ip : ip_pool)
            if (ip.isFirstEqual(1))
                std::cout << ip.repr << std::endl;

        // filter by first and second bytes and output
        for(auto ip : ip_pool)
            if (ip.isFirstAndSecondEqual(46, 70))
                std::cout << ip.repr << std::endl;

        // filter by any byte and output
        for(auto ip : ip_pool)
            if (ip.isAnyEqual(46))
                std::cout << ip.repr << std::endl;

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
