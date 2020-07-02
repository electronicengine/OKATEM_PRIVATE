#include "json.h"
#include <thread>



Json::Json()
{

}



Json::~Json()
{
}



int Json::init()
{

    readStreamInfo(gmRemoteMachineInformations);
    readMotorInfo(gmMotorInformations);

//    readSensorInfo(gmM);

    return SUCCESS;

}



void Json::saveStreamInfo(const REMOTEMACHINE_INFORMATIONS &RemoteMachineInfo)
{


    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    gmRemoteMachineInformations = RemoteMachineInfo;

    RemoteMachineInfo.serializeJSON(writer);

    writeFile(buffer.GetString(), FILES[FileTypes::RemoteMachineFileInfo]);
    writeFile(buffer.GetString(), FILES_BACKUP[FileTypes::RemoteMachineFileInfo]);


}



void Json::saveBoardInfo(const JSON_SENSOR_INFORMATIONS& JsonSensorData)
{

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    gmJsonSensorInformations = JsonSensorData;

    JsonSensorData.serializeJSON(writer);

    gmMutex.lock();
    writeFile(buffer.GetString(), FILES[FileTypes::SensorInfo]);
    writeFile(buffer.GetString(), FILES_BACKUP[FileTypes::SensorInfo]);

    gmMotorInformations.servo_motor1_degree =
            JsonSensorData.stm_environment_data.servo_motor1_degree;


    gmMotorInformations.servo_motor2_degree =
            JsonSensorData.stm_environment_data.servo_motor2_degree;


    gmMotorInformations.step_motor1_position = JsonSensorData.stm_environment_data.step_motor1_step;
    gmMotorInformations.step_motor2_position = JsonSensorData.stm_environment_data.step_motor2_step;

    saveMotorInfo(gmMotorInformations);
    gmMutex.unlock();

}



void Json::saveMotorInfo(const MOTOR_INFORMATIONS &MotorInfo)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    MotorInfo.serializeJSON(writer);

    gmMotorInformations = MotorInfo;

    writeFile(buffer.GetString(), FILES[FileTypes::MotorInfo]);
    writeFile(buffer.GetString(), FILES_BACKUP[FileTypes::MotorInfo]);

}



REMOTEMACHINE_INFORMATIONS Json::loadStreamInfo()
{

    REMOTEMACHINE_INFORMATIONS stream_info;

    stream_info = gmRemoteMachineInformations;

    return gmRemoteMachineInformations;

}



JSON_SENSOR_INFORMATIONS Json::loadSensorInfo()
{
    JSON_SENSOR_INFORMATIONS json_sensor_information;

    json_sensor_information = gmJsonSensorInformations;

    return json_sensor_information;
}



MOTOR_INFORMATIONS Json::loadMotorInfo()
{
    MOTOR_INFORMATIONS motor_informations;

    motor_informations = gmMotorInformations;

    return motor_informations;
}



void Json::readStreamInfo(REMOTEMACHINE_INFORMATIONS &StreamInfo)
{

    std::string json_string;
    rapidjson::Document json_document;

    json_string = readFile(FILES[FileTypes::RemoteMachineFileInfo]);

    json_document.Parse(json_string.c_str());

    if(json_document.IsObject())
    {
        StreamInfo.parseJSON(json_document);
    }
    else
    {
        json_string.clear();
        json_string = readFile(FILES_BACKUP[FileTypes::MotorInfo]);
        json_document.Parse(json_string.c_str());

        StreamInfo.parseJSON(json_document);
    }


    printAll("Json Stream Ip: ", StreamInfo.stream_ip,
             " Json Stream Port: ", StreamInfo.stream_port,
             " Json Control Port: ", StreamInfo.control_port);

}



void Json::readSensorInfo(JSON_SENSOR_INFORMATIONS &SensorInfo)
{
    std::string json_string;
    rapidjson::Document json_document;

    json_string = readFile(FILES[FileTypes::SensorInfo]);

    json_document.Parse(json_string.c_str());

    if(json_document.IsArray())
    {
        SensorInfo.parseJSON(json_document);
    }
    else
    {
        json_string.clear();
        json_string = readFile(FILES_BACKUP[FileTypes::SensorInfo]);
        json_document.Parse(json_string.c_str());

        SensorInfo.parseJSON(json_document);
    }

}



void Json::readMotorInfo(MOTOR_INFORMATIONS &MotorInfo)
{
    std::string json_string;
    rapidjson::Document json_document;

    json_string = readFile(FILES[FileTypes::MotorInfo]);

    json_document.Parse(json_string.c_str());

    if(json_document.IsObject())
    {
        MotorInfo.parseJSON(json_document);
    }
    else
    {

        json_string.clear();
        json_string = readFile(FILES_BACKUP[FileTypes::MotorInfo]);
        json_document.Parse(json_string.c_str());

        MotorInfo.parseJSON(json_document);
    }

    gmMotorInformations = MotorInfo;

    printAll("Json Servo1 Degree: ", std::to_string(MotorInfo.servo_motor1_degree));
    printAll("Json Servo1 Top Degree: ", std::to_string(MotorInfo.servo_motor1_top_degree));
    printAll("Json Servo1 Bottom Degree: ", std::to_string(MotorInfo.servo_motor1_bottom_degree));

    printAll("Json Servo2 Degree: ", std::to_string(MotorInfo.servo_motor2_degree));
    printAll("Json Servo2 Top Degree: ", std::to_string(MotorInfo.servo_motor2_top_degree));
    printAll("Json Servo2 Bottom Degree: ", std::to_string(MotorInfo.servo_motor2_bottom_degree));

    printAll("Json Step Motor1 Pos: ", std::to_string(MotorInfo.step_motor1_position));
    printAll("Json Step Motor1 Max Pos: ", std::to_string(MotorInfo.step_motor1_max_step));

    printAll("Json Step Motor2 Pos: ", std::to_string(MotorInfo.step_motor2_position));
    printAll("Json Step Motor2 Max Pos: ", std::to_string(MotorInfo.step_motor2_max_step));

}





void Json::writeFile(const std::string &Content, const std::string &File)
{

    std::ofstream myfile;
    myfile.open (File);
    myfile << Content;
    myfile.close();


}

std::string Json::readFile(const std::string &File)
{

    std::string content;
    std::ifstream myfile;

    myfile.open (File);

    myfile >> content;

    myfile.close();

    return content;

}




void Json::getPhysicalSourceUsage(float &MemUsage, float &CpuUsage)
{

    size_t previous_idle_time=0, previous_total_time=0;
    size_t idle_time, total_time;

    struct sysinfo memInfo;

    getCpuTime(idle_time, total_time);

    const float idle_time_delta = idle_time - previous_idle_time;
    const float total_time_delta = total_time - previous_total_time;

    const float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);

    previous_idle_time = idle_time;
    previous_total_time = total_time;

    sysinfo (&memInfo);
    double phys_mem_med = (double)(memInfo.totalram - memInfo.freeram) / memInfo.totalram;
    phys_mem_med *= memInfo.mem_unit;

    phys_mem_med = 1 - phys_mem_med;
    phys_mem_med *= 100;

    MemUsage = phys_mem_med;
    CpuUsage = utilization;

}



std::vector<size_t> Json::getCpuTick()
{

    std::ifstream proc_stat("/proc/stat");
    proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
    std::vector<size_t> times;
    for (size_t time; proc_stat >> time; times.push_back(time));

    return times;

}



bool Json::getCpuTime(size_t &idle_time, size_t &total_time)
{

    const std::vector<size_t> cpu_times = getCpuTick();

    if (cpu_times.size() < 4)
        return false;
    idle_time = cpu_times[3];
    total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
    return true;

}



float Json::getCpuUsage()
{

    size_t previous_idle_time=0, previous_total_time=0;
    size_t idle_time, total_time;

    getCpuTime(idle_time, total_time);

    const float idle_time_delta = idle_time - previous_idle_time;
    const float total_time_delta = total_time - previous_total_time;

    const float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);

    previous_idle_time = idle_time;
    previous_total_time = total_time;

    return utilization;

}


