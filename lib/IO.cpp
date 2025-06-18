#include "../include/IO.h"


uint8_t* loadROM(std::string filePath, int &size)
{

    std::ifstream file;
    file.open(filePath.c_str(), std::ios::binary);
    uint8_t* ROM;

    if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        int length = file.tellg();
        file.seekg(0, std::ios::beg);

        size = length; 
        ROM = new uint8_t[length];
        file.read(reinterpret_cast<char*>(ROM), length);
    }

    file.close();

    return ROM;
}



