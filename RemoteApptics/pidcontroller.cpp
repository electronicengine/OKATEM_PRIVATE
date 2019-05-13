#include "pidcontroller.h"


double PIDController::applyPID(double Error)
{
    double output;
    double error;

    error = Error;

    output = calculateP(error);
    output += calculateI(error);
    output += calculateD(error);

    gmLastTime = clock();

    return output;

}

void PIDController::clear()
{
//    gmP = 0;
//    gmI = 0;
//    gmD = 0;

    gmLastTime = 0;
    gmErrorAvarage = 0;
    gmErrorCumulative = 0;
}

double PIDController::calculateD(double Error)
{
    clock_t time_now = 0;
    double time_difference = 0;

    time_now = clock();

    time_difference = (double)time_now - gmLastTime;
    time_difference =(double)time_difference / 1000;

    gmErrorAvarage = (double)Error - gmErrorAvarage;
    gmErrorAvarage = (double)gmErrorAvarage / time_difference;

//    std::cout << "D:" << std::to_string(gmErrorAvarage * gmD) << std::endl;


    return gmErrorAvarage * gmD;
}

double PIDController::calculateI(double Error)
{
    clock_t time_now;
    double time_difference;

    time_now = clock();


    time_difference = (double)time_now - gmLastTime;
    time_difference =(double)time_difference / 1000000;

    if(gmLastTime <= 0 || time_difference < 0)
        time_difference = 0;

    gmErrorCumulative += Error * time_difference;

//    std::cout << "I:" << std::to_string(gmErrorCumulative * gmI) << std::endl;


    return gmErrorCumulative * gmI;
}

double PIDController::calculateP(double Error)
{
    return Error * gmP;
}
