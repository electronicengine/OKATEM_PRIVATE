#ifndef DATATYPES_H
#define DATATYPES_H

#include "spidatatypes.h"
#include "ethernetdatatypes.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>

#define VARNAME(Variable) (#Variable)


enum class Status
{

    time_out,
    error,
    ok

};


struct JSON_SENSOR_INFORMATIONS
{

    SFP_DATA_FORMAT         sfp_data;
    ENVIRONMENT_DATA_FORMAT stm_environment_data;

    SFP_DATA_FORMAT         lora_sfp_data;
    ENVIRONMENT_DATA_FORMAT lora_environment_data;

    void serializeJSON(rapidjson::Writer<rapidjson::StringBuffer>& JsonWriter) const
    {
        JsonWriter.StartArray();

        JsonWriter.StartObject();

        sfp_data.serializeJson(JsonWriter);
        stm_environment_data.serializeJson(JsonWriter);

        JsonWriter.EndObject();
        JsonWriter.StartObject();

        lora_environment_data.serializeJson(JsonWriter);
        lora_sfp_data.serializeJson(JsonWriter);

        JsonWriter.EndObject();

        JsonWriter.EndArray();

    }

    void parseJSON(rapidjson::Document &JsonDocument)
    {

        if(JsonDocument.IsArray())
        {
            rapidjson::Value object = JsonDocument[0].GetObject();

            if(object.IsObject())
            {
                sfp_data.parseJson(object);
                stm_environment_data.parseJson(object);
            }

            object = JsonDocument[1].GetObject();

            if(object.IsObject())
            {
                lora_sfp_data.parseJson(object);
                stm_environment_data.parseJson(object);
            }

        }
    }
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



    operator CONTROL_DATA_FORMAT() const
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

    MOTOR_INFORMATIONS operator =(const CONTROL_DATA_FORMAT &ControlData)
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

    void serializeJSON(rapidjson::Writer<rapidjson::StringBuffer>& JsonWriter) const
    {

        JsonWriter.StartObject();

        JsonWriter.Key(VARNAME(servo_motor1_degree));
        JsonWriter.Int(servo_motor1_degree);
        JsonWriter.Key(VARNAME(servo_motor1_bottom_degree));
        JsonWriter.Int(servo_motor1_bottom_degree);
        JsonWriter.Key(VARNAME(servo_motor1_top_degree));
        JsonWriter.Int(servo_motor1_top_degree);

        JsonWriter.Key(VARNAME(servo_motor2_degree));
        JsonWriter.Int(servo_motor2_degree);
        JsonWriter.Key(VARNAME(servo_motor2_bottom_degree));
        JsonWriter.Int(servo_motor2_bottom_degree);
        JsonWriter.Key(VARNAME(servo_motor2_top_degree));
        JsonWriter.Int(servo_motor2_top_degree);

        JsonWriter.Key(VARNAME(step_motor1_position));
        JsonWriter.Int(step_motor1_position);

        JsonWriter.Key(VARNAME(step_motor1_max_step));
        JsonWriter.Int(step_motor1_max_step);

        JsonWriter.Key(VARNAME(step_motor2_position));
        JsonWriter.Int(step_motor2_position);

        JsonWriter.Key(VARNAME(step_motor2_max_step));
        JsonWriter.Int(step_motor2_max_step);

        JsonWriter.EndObject();

    }

    void parseJSON(rapidjson::Document &JsonDocument)
    {
        if(JsonDocument.IsObject())
        {
            if(JsonDocument.HasMember(VARNAME(servo_motor1_degree)));
                servo_motor1_degree =
                        JsonDocument[VARNAME(servo_motor1_degree)].GetInt();

            if(JsonDocument.HasMember(VARNAME(servo_motor1_bottom_degree)));
                servo_motor1_bottom_degree =
                        JsonDocument[VARNAME(servo_motor1_bottom_degree)].GetInt();

            if(JsonDocument.HasMember(VARNAME(servo_motor1_top_degree)));
                servo_motor1_top_degree =
                        JsonDocument[VARNAME(servo_motor1_top_degree)].GetInt();

            if(JsonDocument.HasMember(VARNAME(servo_motor2_degree)));
                servo_motor2_degree =
                        JsonDocument[VARNAME(servo_motor2_degree)].GetInt();

            if(JsonDocument.HasMember(VARNAME(servo_motor2_top_degree)));
                servo_motor2_top_degree =
                        JsonDocument[VARNAME(servo_motor2_top_degree)].GetInt();

            if(JsonDocument.HasMember(VARNAME(servo_motor2_bottom_degree)));
                servo_motor2_bottom_degree =
                        JsonDocument[VARNAME(servo_motor2_bottom_degree)].GetInt();

            if(JsonDocument.HasMember(VARNAME(step_motor1_position)));
                step_motor1_position =
                        JsonDocument[VARNAME(step_motor1_position)].GetInt();

            if(JsonDocument.HasMember(VARNAME(step_motor1_max_step)));
                step_motor1_max_step =
                        JsonDocument[VARNAME(step_motor1_max_step)].GetInt();

            if(JsonDocument.HasMember(VARNAME(step_motor2_position)));
                step_motor2_position =
                        JsonDocument[VARNAME(step_motor2_position)].GetInt();

            if(JsonDocument.HasMember(VARNAME(step_motor2_max_step)));
                step_motor2_max_step =
                        JsonDocument[VARNAME(step_motor2_max_step)].GetInt();

        }

    }

};



struct REMOTEMACHINE_INFORMATIONS
{
    std::string stream_ip;

    int stream_port;
    int control_port;

    void serializeJSON(rapidjson::Writer<rapidjson::StringBuffer>& JsonWriter) const
    {
        JsonWriter.StartObject();

        JsonWriter.Key(VARNAME(stream_ip));
        JsonWriter.String(stream_ip.c_str());

        JsonWriter.Key(VARNAME(stream_port));
        JsonWriter.Int(stream_port);

        JsonWriter.Key(VARNAME(control_port));
        JsonWriter.Int(control_port);

        JsonWriter.EndObject();
    }

    void parseJSON(rapidjson::Document &JsonDocument)
    {

        if(JsonDocument.IsObject())
        {

            if(JsonDocument.HasMember(VARNAME(stream_ip)));
                stream_ip =
                        JsonDocument[VARNAME(stream_ip)].GetString();

            if(JsonDocument.HasMember(VARNAME(stream_port)));
                stream_port =
                        JsonDocument[VARNAME(stream_port)].GetInt();

            if(JsonDocument.HasMember(VARNAME(control_port)));
                control_port =
                        JsonDocument[VARNAME(control_port)].GetInt();

        }
    }
};


#endif // DATATYPES_H
