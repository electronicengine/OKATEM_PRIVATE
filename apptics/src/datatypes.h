#ifndef DATATYPES_H
#define DATATYPES_H

#include "spidatatypes.h"
#include "ethernetdatatypes.h"





enum class Status
{

    time_out,
    error,
    ok

};

struct MOTOR_INFORMATIONS
{

    uint8_t servo_motor1_degree;
    uint8_t servo_motor1_bottom_degree;
    uint8_t servo_motor1_top_degree;

    uint8_t servo_motor2_degree;
    uint8_t servo_motor2_bottom_degree;
    uint8_t servo_motor2_top_degree;

    uint32_t step_motor1_position;
    uint32_t step_motor1_max_step;

    uint32_t step_motor2_position;
    uint32_t step_motor2_max_step;



    operator CONTROL_DATA_FORMAT()
    {
        CONTROL_DATA_FORMAT control_data;

        control_data.servo_motor1_degree = servo_motor1_degree;
        control_data.servo_motor1_bottom_degree = servo_motor1_bottom_degree;
        control_data.servo_motor1_top_degree = servo_motor1_top_degree;

        control_data.servo_motor2_degree = servo_motor2_degree;
        control_data.servo_motor2_bottom_degree = servo_motor2_bottom_degree;
        control_data.servo_motor2_top_degree = servo_motor2_top_degree;

        control_data.step_motor1_step = step_motor1_position;
        control_data.step_motor1_max_step = step_motor1_max_step;

        control_data.step_motor2_step = step_motor2_position;
        control_data.step_motor2_max_step = step_motor2_max_step;

        return control_data;

    }

    MOTOR_INFORMATIONS operator =(CONTROL_DATA_FORMAT &ControlData)
    {
        servo_motor1_degree = ControlData.servo_motor1_degree;
        servo_motor1_bottom_degree = ControlData.servo_motor1_bottom_degree;
        servo_motor1_top_degree = ControlData.servo_motor1_top_degree;

        servo_motor2_degree = ControlData.servo_motor2_degree;
        servo_motor2_bottom_degree = ControlData.servo_motor2_bottom_degree;
        servo_motor2_top_degree = ControlData.servo_motor2_top_degree;

        step_motor1_position = ControlData.step_motor1_step;
        step_motor1_max_step = ControlData.step_motor1_max_step;

        step_motor2_position = ControlData.step_motor2_step;
        step_motor2_max_step = ControlData.step_motor2_max_step;

        return *this;
    }


};



struct REMOTEMACHINE_INFORMATIONS
{
    std::string stream_ip;

    int stream_port;
    int control_port;
};


#endif // DATATYPES_H
