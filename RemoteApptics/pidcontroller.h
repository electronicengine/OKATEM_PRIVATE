#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

class PIDController
{
public:
    PIDController(double P, double I, double D) : gmP(P), gmI(I), gmD(D){}

    double applyPID(double Errors);
    void clear();

private:

    double calculateD(double Error);
    double calculateI(double Error);
    double calculateP(double Error);

    clock_t gmLastTime = 0;
    double gmErrorCumulative = 0;
    double gmErrorAvarage = 0;
    double gmP, gmI, gmD;

};

#endif // PIDCONTROLLER_H
