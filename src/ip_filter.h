#pragma once

#include <cstdlib>
#include <cstring>
#include <string>

enum 
{ 
#ifdef WIN32
    BYTE_1 = 0, BYTE_2 = 1, BYTE_3 = 2, BYTE_4 = 3,
#else
    BYTE_1 = 3, BYTE_2 = 2, BYTE_3 = 1, BYTE_4 = 0,
#endif
};

struct Ipv4Descr 
{
    char repr[16];
    union 
    {
        uint32_t addr;
        u_char byte[4];
    };
    
    Ipv4Descr(const std::string &s);

    bool isFirstEqual(u_char b) const 
    {
        return byte[BYTE_1] == b;
    }

    bool isFirstAndSecondEqual(u_char b1, u_char b2) const 
    {
        return byte[BYTE_1] == b1 && byte[BYTE_2] == b2;
    }

    bool isAnyEqual(u_char b) const
    {
        return byte[BYTE_1] == b || byte[BYTE_2] == b || byte[BYTE_3] == b || byte[BYTE_4] == b;
    }
};