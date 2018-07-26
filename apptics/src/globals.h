#ifndef GLOBALS_H
#define GLOBALS_H

#include "iostream"

#include <sstream>
#include <cstdarg>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <fstream>

#define SUCCESS 1
#define FAIL 2

#define MAX_LOG_LINE 1000
#define LOG_FILE "/var/www/html/log.txt"

static std::mutex printMutex;


void removeLine(char* sourcefile, int line);
int countLine(char* sourcefile);



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


template< typename T>
const T currentDateTime()
{

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;

}


template <typename T = std::string>
void writeLog(const T& Log)
{

    std::string log_data;


    printMutex.lock();

    log_data = Log;



    int num_lines = 0;
    int deleted_lines = 0;

    std::ifstream logfile(LOG_FILE, std::ios_base::in);

    std::string unused;
    while ( std::getline(logfile, unused, '\n') )
       ++num_lines;

    logfile.close();

    if(num_lines > MAX_LOG_LINE)
    {

        std::ofstream tempfile("/var/www/html/temp.txt", std::ios_base::app);

        logfile.open(LOG_FILE, std::ios_base::app);

        deleted_lines =  num_lines - MAX_LOG_LINE ;

        num_lines = 0;


         while ( std::getline(logfile, unused, '\n') )
         {
             if(num_lines > deleted_lines - 1)
                tempfile << unused << std::endl;

             num_lines ++;

         }

         logfile.close();
         tempfile.close();

        system("sudo rm /var/www/html/log.txt");
        system("sudo mv /var/www/html/temp.txt /var/www/html/log.txt");

    }

    num_lines = 0;

    std::ofstream file(LOG_FILE, std::ios_base::app);
    file <<  currentDateTime<std::string>() << " : " << log_data << std::endl;
    file.close();

    printMutex.unlock();

}



template<typename... TAIL>
void printAll(const TAIL&... tail)
{


    std::string package = serializer(tail...);

    std::cout << package << std::endl;

    writeLog(package);




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
