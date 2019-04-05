#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include "process.h"
#include "queue"
struct KalmanGain
{
    double measurement_kalman_gain = 0;
    double error_kalman_gain = 0;
};

struct EstimatedValue
{
    double estimated_measurement = 0;
    double estimated_error = 0;
};

struct KalmanContainer
{

    KalmanGain kalman_gain;
    EstimatedValue estimated_value;
    EstimatedValue pre_estimated_value;
    double error_covariance[2][2] = {{1.0, 1.0}, {1.0, 1.0}};
    double pre_error_covariance[2][2] = {{1.0, 1.0}, {1.0, 1.0}};

    double measured_value = 0;
    double measured_value_persecond = 0;
    double time_interval = 0;
    double noise_variance = 0.9;
    double error_variance = 0.9;
    double measurement_variance = 0.9;

    double now = 0;
    double last = 0;

    KalmanContainer operator =(double Value)
    {

        measured_value = Value;

        now = (double)(clock()) / 1000000;

        time_interval = now - last;

        measured_value_persecond = measured_value / 131.0;

        last = now;

        return *this;

    }

};

class KalmanFilter
{



public:
    KalmanFilter();
    cv::Point takeKalmanFilter(const cv::Point &NoisyPoint);

private:

    KalmanContainer gmPointXKalman;
    KalmanContainer gmPointYKalman;

    void calculateKalmanGain(KalmanContainer &Container); //Measurement step1
    void calculateErrorCovariance(KalmanContainer &Container); //Mesaurement step2
    void calculateEstimatedValue(KalmanContainer &Container); //Measurement step3

    void calculatePreEstimateValue(KalmanContainer &Container); //timeUpdate step1
    void calculatePreErrorCovariance(KalmanContainer &Container); //timeUpdate step2

    void timeUpdate(KalmanContainer &Container);
    void measurmentUpdate(KalmanContainer &Container);

};

#endif // KALMANFILTER_H
