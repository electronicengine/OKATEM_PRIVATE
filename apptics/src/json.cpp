#include "json.h"
#include <thread>

Json::Json()
{


}

Json::Json(int Mode)
{

}


Json::~Json()
{
}

int Json::init()
{


    std::string json;

    int counter = 0;

    rapidjson::Document document;


    json = readFile();

    do
    {
        counter++;

        document.Parse(json.c_str());

        if(document.IsObject())
        {
            if(document.HasMember("servo_motor1_degree"))
                gmServoMotor1Degree = document["servo_motor1_degree"].GetInt();

            if(document.HasMember("servo_motor2_degree"))
                gmServoMotor2Degree = document["servo_motor2_degree"].GetInt();

            if(document.HasMember("stream_ip"))
                gmStreamIp = document["stream_ip"].GetString();

            if(document.HasMember("stream_port"))
                gmStreamPort = document["stream_port"].GetInt();

            if(document.HasMember("control_port"))
                gmControlPort = document["control_port"].GetInt();

        }

        if(counter >= 3)
            break;


    }while(!document.IsObject() && counter++ <= 3);

    if(!document.IsObject())
    {
        printAll("json informations have not loaded into buffer! Check Json Object");

        return FAIL;
    }
    else
    {
        std::thread postJson(&Json::writeJson, this);
        postJson.detach();

        return SUCCESS;

    }

}

void Json::saveMotorPositions(CONTROL_DATA_FORMAT &ControlData)
{
    gmMutex.lock();

    if(ControlData.servo_motor1_degree != 0)
        gmServoMotor1Degree = ControlData.servo_motor1_degree;

    if(ControlData.servo_motor2_degree != 0)
        gmServoMotor2Degree = ControlData.servo_motor2_degree;

    gmMutex.unlock();

}

int Json::loadStreamInfo(std::string &StreamIp, int &StreamPort, int &ControlPort)
{


    int counter = 0;

    std::string json_string;

    json_string = readFile();

    rapidjson::Document document;

    do{

        counter++;

        document.Parse(json_string.c_str());

        if(document.IsObject())
        {
            if(document.HasMember("stream_ip"))
                StreamIp = document["stream_ip"].GetString();

            if(document.HasMember("stream_port"))
                StreamPort = document["stream_port"].GetInt();

            if(document.HasMember("control_port"))
                ControlPort = document["control_port"].GetInt();
        }

        if(counter >= 3)
            break;

    }while(!document.IsObject() && counter++ <= 4);

    if(!document.IsObject())
    {
        printAll("Stream Info have not loaded! Check Json Object");
        return FAIL;
    }
    else
    {
        return SUCCESS;
    }

}

void Json::saveEnvironmentData(ENVIRONMENT_DATA_FORMAT &StmData, SFP_DATA_FORMAT &SfpData)
{

    gmMutex.lock();

    gmSfpData = SfpData;
    gmStmData = StmData;

    gmMutex.unlock();

}



void Json::saveLoraData(ENVIRONMENT_DATA_FORMAT &LoraStmData, SFP_DATA_FORMAT &LoraSfpData)
{

    gmMutex.lock();

    gmLoraSfpData = LoraSfpData;
    gmLoraStmData = LoraStmData;

    gmMutex.unlock();

}



int Json::loadMotorPositions(CONTROL_DATA_FORMAT &ControlData)
{

    std::string json;
    rapidjson::Document document;
    int counter;

    json = readFile();

    do{
        document.Parse(json.c_str());

        counter++;

        if(document.IsObject())
        {

            if(document.HasMember("servo_motor1_degree"))
                ControlData.servo_motor1_degree = document["servo_motor1_degree"].GetInt();

            if(document.HasMember("step_motor1_position"))
                ControlData.step_motor1_direction = document["step_motor1_position"].GetInt();

            if(document.HasMember("servo_motor2_degree"))
                ControlData.servo_motor2_degree = document["servo_motor2_degree"].GetInt();

            if(document.HasMember("step_motor2_position"))
                ControlData.step_motor2_direction = document["step_motor2_position"].GetInt();

        }

        if(counter >= 3)
            break;


    }while(!document.IsObject());

    if(!document.IsObject())
    {
        printAll("Motor Positions have not loaded into buffer! Check Json Object");
        return FAIL;
    }
    else
    {
        return SUCCESS;
    }



}



void Json::writeJson()
{


    while(1)
    {
        float cpu_usage;
        float mem_usage;

        rapidjson::StringBuffer s;
        rapidjson::Writer<rapidjson::StringBuffer> writer(s);

        getPhysicalSourceUsage(mem_usage, cpu_usage);

        writer.StartObject();

        writer.Key("terminal_status");
        writer.String("Connected");

        writer.Key("terminal_status");
        writer.String((gmSfpData.status == 1) ? "Connected" : "Disconnected");

    //    writer.Key("laser_diagonal");
    //    writer.Double(tracker.getDiagonalRate());

    //    writer.Key("laser_edge");
    //    writer.Double(tracker.getDiagonalRate());

        writer.Key("sfp_temp");
        writer.Double(gmSfpData.temperature);

        writer.Key("sfp_vcc");
        writer.Uint(gmSfpData.vcc);

        writer.Key("sfp_tx_bias");
        writer.Double(gmSfpData.tx_bias);

        writer.Key("sfp_tx_power");
        writer.Double(gmSfpData.tx_power);

        writer.Key("sfp_rx_power");
        writer.Double(gmSfpData.rx_power);

        writer.Key("terminal_gps_string");
        writer.String(gmStmData.gps_string.c_str());

        writer.Key("terminal_latitude");
        writer.Double(gmStmData.gps_data.latitude);

        writer.Key("terminal_ns_indicator");
        writer.String((const char*)&gmStmData.gps_data.ns_indicator);

        writer.Key("terminal_longnitude");
        writer.Double(gmStmData.gps_data.longnitude);

        writer.Key("terminal_we_indicator");
        writer.String((const char*)&gmStmData.gps_data.we_indicator);

        writer.Key("terminal_temperature");
        writer.Uint(gmStmData.sensor_data.temperature);

        writer.Key("terminal_pressure");
        writer.Uint(gmStmData.sensor_data.pressure);

        writer.Key("terminal_altitude");
        writer.Uint(gmStmData.sensor_data.altitude);

        writer.Key("terminal_compass");
        writer.Uint(gmStmData.sensor_data.compass_degree);

        writer.Key("servo_motor1_degree");
        writer.Uint(gmServoMotor1Degree);

        writer.Key("servo_motor2_degree");
        writer.Uint(gmServoMotor2Degree);

        writer.Key("step_motor1_position");
        writer.Uint(gmStepMotor1Position);

        writer.Key("step_motor2_position");
        writer.Uint(gmStepMotor2Position);

        writer.Key("cpu_usage");
        writer.Double(cpu_usage);

        writer.Key("memory_usage");
        writer.Double(mem_usage);


        writer.Key("remote_terminal_status");
        writer.String((gmLoraSfpData.status == 1) ? "Connected" : "Disconnected");

        writer.Key("remote_sfp_temp");
        writer.Double(gmLoraSfpData.temperature);

        writer.Key("remote_sfp_vcc");
        writer.Uint(gmLoraSfpData.vcc);

        writer.Key("remote_sfp_tx_bias");
        writer.Double(gmLoraSfpData.tx_bias);

        writer.Key("remote_sfp_tx_power");
        writer.Double(gmLoraSfpData.tx_power);

        writer.Key("remote_sfp_rx_power");
        writer.Double(gmLoraSfpData.rx_power);

        writer.Key("remote_terminal_gps_string");
        writer.String(gmLoraStmData.gps_string.c_str());

        writer.Key("remote_terminal_latitude");
        writer.Double(gmLoraStmData.gps_data.latitude);

        writer.Key("remote_terminal_ns_indicator");
        writer.String((const char*)&gmLoraStmData.gps_data.ns_indicator);

        writer.Key("remote_terminal_longnitude");
        writer.Double(gmLoraStmData.gps_data.longnitude);

        writer.Key("remote_terminal_we_indicator");
        writer.String((const char*)&gmLoraStmData.gps_data.we_indicator);

        writer.Key("remote_terminal_temperature");
        writer.Uint(gmLoraStmData.sensor_data.temperature);

        writer.Key("remote_terminal_pressure");
        writer.Uint(gmLoraStmData.sensor_data.pressure);

        writer.Key("remote_terminal_altitude");
        writer.Uint(gmLoraStmData.sensor_data.altitude);

        writer.Key("remote_terminal_compass");
        writer.Uint(gmLoraStmData.sensor_data.compass_degree);

        writer.Key("stream_ip");
        writer.String(gmStreamIp.c_str());

        writer.Key("stream_port");
        writer.Uint(gmStreamPort);

        writer.Key("control_port");
        writer.Uint(gmControlPort);

        writer.EndObject();

        writeFile(s.GetString());

        sleep(1);
    }


}


int Json::writeFile(const std::string &Content)
{

    std::ofstream myfile;
    myfile.open ("/var/www/html/json.save");
    myfile << Content;
    myfile.close();

    usleep(50000);


    system("cp /var/www/html/json.save /var/www/html/json");

}

std::string Json::readFile()
{

    std::string content;
    std::ifstream myfile;

    myfile.open ("/var/www/html/json");

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


