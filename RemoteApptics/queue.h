#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


template<typename T>
class Queue
{

private:
    std::vector<T> gmQueue;
    size_t gmMaxSize = 5000;

public:

    Queue()
    {

    }

    Queue(int Size) : gmMaxSize(Size)
    {
        std::cout << "Queue Max: " << std::to_string(Size) << std::endl;
    }

    long unsigned int size()
    {
        return gmQueue.size();
    }

    void clear()
    {
        gmQueue.clear();
    }

    T get_element(int Number)
    {
        return gmQueue[Number];
    }

    T pop_front()
    {

        T first_pack;

        if(!gmQueue.empty())
        {
            first_pack = gmQueue[0];
            gmQueue.erase(gmQueue.begin());
            return first_pack;
        }
        else
        {
            first_pack.clear();
            return first_pack;
        }

    }

    T pop_back()
    {
        T last_pack;

        if(!gmQueue.empty())
        {
            last_pack = gmQueue.pop_back();
            return last_pack;
        }
        else
        {
            last_pack.clear();
            return last_pack;
        }
    }

    void push_back(const T& Package)
    {
        if(gmMaxSize > gmQueue.size())
        {
            gmQueue.push_back(Package);
        }
        else
        {
            gmQueue.erase(gmQueue.begin());
            gmQueue.push_back(Package);
        }
    }

    void push_front(const T& Package)
    {
        if(gmMaxSize > gmQueue.size())
        {
            gmQueue.insert(gmQueue.begin(), Package);
        }
        else
        {
            gmQueue.pop_back();
            gmQueue.insert(gmQueue.begin(), Package);
        }
    }


};

#endif // QUEUE_H
