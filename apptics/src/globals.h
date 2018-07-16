#ifndef GLOBALS_H
#define GLOBALS_H

#include "iostream"

#include <sstream>
#include <cstdarg>
#include <vector>
#include <mutex>
#include <cstdlib>


static std::mutex printMutex;


template< typename T >
inline std::string serializer(const T& t)
{

    std::stringstream string_stream;
    string_stream << t;
    return string_stream.str();

}

template< typename T, typename ... Args >
inline std::string serializer(const T& head, Args ... args)
{
    return serializer( head ) + serializer( args... );
}

 template<typename... TAIL>
void printAll(const TAIL&... tail)
{


    std::string package = serializer(tail...);

    std::cout << package << std::endl;


}

template<typename T>
std::string convertToHex(const T& Container)
{

    std::stringstream hex_string;

    if(std::is_same<T, std::string>::value)
    {
        for(int i=0; i<Container.length(); i++)
          hex_string << std::hex << static_cast<int>(Container.c_str()[i]);
    }


    if(std::is_same<T, std::vector<unsigned char>>::value)
    {
        for(int i=0;i<Container.size(); i++)
          hex_string<< std::hex << static_cast<int>(Container.data()[i]);
    }

    return hex_string.str();

}

template<typename T>
std::string convertHexToAscii(const T& Data)
{



    std::vector<unsigned char> ascii_chars;

    if (std::is_same<T, std::string>::value)
    {

        for( unsigned i = 0, uchr ; i < (Data.length() / 2) - 1; i ++ )
        {
            sscanf( Data.c_str() + i*2, "%02x", &uchr ); // conversion

            ascii_chars.push_back(uchr);

          }

        return std::string(ascii_chars.begin(), ascii_chars.end()) ;
    }


}

#endif // GLOBALS_H
