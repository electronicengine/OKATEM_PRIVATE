#include "kalmanfilter.h"



KalmanFilter::KalmanFilter()
{

}



cv::Point KalmanFilter::takeKalmanFilter(const cv::Point &NoisyPoint)
{

    gmPointXKalman = (double)NoisyPoint.x;
    gmPointYKalman = (double)NoisyPoint.y;

    timeUpdate(gmPointXKalman);
    timeUpdate(gmPointYKalman);

    measurmentUpdate(gmPointXKalman);
    measurmentUpdate(gmPointYKalman);

    return cv::Point(gmPointXKalman.estimated_value.estimated_measurement,
                     gmPointYKalman.estimated_value.estimated_measurement);

}



void KalmanFilter::calculatePreEstimateValue(KalmanContainer &Container)
{


    Container.estimated_value.estimated_measurement = Container.pre_estimated_value.estimated_measurement +
             Container.time_interval*(Container.measured_value_persecond - Container.pre_estimated_value.estimated_error);

    Container.estimated_value.estimated_error = Container.pre_estimated_value.estimated_error;
}



void KalmanFilter::calculatePreErrorCovariance(KalmanContainer &Container)
{

    Container.error_covariance[0][0] += Container.time_interval*(Container.time_interval*Container.pre_error_covariance[1][1]
            - Container.pre_error_covariance[0][1] - Container.pre_error_covariance[1][0] + Container.measurement_variance);
    Container.error_covariance[0][1] -= Container.time_interval*Container.pre_error_covariance[1][1];

    Container.error_covariance[1][0] -= Container.time_interval*Container.pre_error_covariance[1][1];
    Container.error_covariance[1][1] += Container.time_interval*Container.measurement_variance;

}



void KalmanFilter::calculateEstimatedValue(KalmanContainer &Container)
{

//    std::cout << "estimated_error: " << std::to_string(Container.estimated_value.estimated_measurement);
//    std::cout << " - error_kalman_gain:" << std::to_string(Container.pre_estimated_value.estimated_measurement);
//    std::cout << " - estimated_error:" << std::to_string(Container.pre_estimated_value.estimated_error) << std::endl;

    Container.estimated_value.estimated_measurement += Container.kalman_gain.measurement_kalman_gain *
                                                    (Container.measured_value - Container.estimated_value.estimated_measurement);

    Container.estimated_value.estimated_error += Container.kalman_gain.error_kalman_gain *
                                                    (Container.measured_value - Container.estimated_value.estimated_measurement);

    Container.pre_estimated_value.estimated_measurement = Container.estimated_value.estimated_measurement;
    Container.pre_estimated_value.estimated_error = Container.estimated_value.estimated_error;

}



void KalmanFilter::calculateKalmanGain(KalmanContainer &Container)
{

    Container.kalman_gain.measurement_kalman_gain = (double)Container.error_covariance[0][0]
            / (Container.error_covariance[0][0] + Container.noise_variance);

    Container.kalman_gain.error_kalman_gain = (double)Container.error_covariance[1][0]
            / (Container.error_covariance[0][0] + Container.noise_variance);

}



void KalmanFilter::calculateErrorCovariance(KalmanContainer &Container)
{
    Container.error_covariance[0][0] -=
            (Container.kalman_gain.measurement_kalman_gain*Container.error_covariance[0][0]);

    Container.error_covariance[0][1] -=
            (Container.kalman_gain.measurement_kalman_gain*Container.error_covariance[0][1]);

    Container.error_covariance[1][0] -=
            (Container.kalman_gain.error_kalman_gain*Container.error_covariance[0][0]);

    Container.error_covariance[1][1] -=
            (Container.kalman_gain.error_kalman_gain*Container.error_covariance[0][1]);


    for(int i=0; i<2; i++)
        for(int k=0; k<2; k++)
            Container.pre_error_covariance[i][k] = Container.error_covariance[i][k];
}



void KalmanFilter::timeUpdate(KalmanContainer &Container)
{

    calculatePreEstimateValue(Container); // step 1
    calculatePreErrorCovariance(Container); //step 2

}



void KalmanFilter::measurmentUpdate(KalmanContainer &Container)
{

    calculateKalmanGain(Container); // step1

    calculateErrorCovariance(Container); // step2

    calculateEstimatedValue(Container); // step3


}


