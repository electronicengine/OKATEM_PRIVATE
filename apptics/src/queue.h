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

public:

    Queue()
    {

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
        gmQueue.push_back(Package);
    }

    void push_front(const T& Package)
    {
        gmQueue.insert(gmQueue.begin(), Package);
    }


};

#endif // QUEUE_H
