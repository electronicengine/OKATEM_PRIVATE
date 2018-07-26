#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <sys/types.h>
#include <sys/sysinfo.h>

#include "lasertracker.h"
#include "globals.h"
#include "lorawan.h"
#include "spicom.h"
#include "controller.h"
#include "sfpmonitor.h"
#include "udpsocket.h"


clock_t now = 0;
clock_t last = 0;

SPI_RX_FORMAT stm_data;
SPI_RX_FORMAT lora_stm_data;

SPI_TX_FORMAT control_data;

SFP_DATA sfp_data;
SFP_DATA lora_sfp_data;

LoraWan lora;
Controller controller;
SfpMonitor sfp_monitor;
LaserTracker tracker(0);
UdpSocket udp_socket;

void safeLog();
void writeJson();

std::vector<size_t> get_cpu_times();
bool get_cpu_times(size_t &idle_time, size_t &total_time);

int main(int argc, char* argv[])
{

    tracker.runTracking();

    stm_data = controller.getStmEnvironment();
    sfp_data = sfp_monitor.getValues();

    lora.setLoraData(sfp_data, stm_data);

    lora.sendBeacon();

    lora.listen();

    while(1)
    {

        stm_data = controller.getStmEnvironment();
        sfp_data = sfp_monitor.getValues();

        lora.setLoraData(sfp_data, stm_data);

        lora.getLoraData(lora_sfp_data, lora_stm_data);

        control_data = udp_socket.getSocketData();


        if(control_data != FAIL )
        {
            controller.setControlData(control_data);
            control_data.clear();
        }

        now = clock();

        if(now - last > 5000000)
        {
            writeJson();
            last = now;
        }


    }

    return 0;

}



void writeJson()
{

    printAll("Environment Data: ");

    printAll("Gps:  ", stm_data.gps_string.substr(0,stm_data.gps_string.find('*')),
             " - Temperature: ", (int)stm_data.sensor_data.temperature,
             " - Altitude: ", (int)stm_data.sensor_data.altitude, " - Pressure: ", (int)stm_data.sensor_data.pressure,
             " - Compass: ", (int)stm_data.sensor_data.compass_degree, " - Wheather: ", (int)stm_data.sensor_data.wheather_condition,
             " - SFP Status: ",(sfp_data.status == 1) ? "Connected" : "Disconnected");
    printAll("\n\n\n");

    printAll("Tracker Diagonal Rate: ", tracker.getDiagonalRate());
    printAll("Tracker Edge Rate: ", tracker.getEdgeRate());
    printAll("\n\n\n");

    printAll("Lora Data: ");
    printAll("Gps:  ", lora_stm_data.gps_string.substr(0,lora_stm_data.gps_string.find('*')),
    " - Temperature: ", (int)lora_stm_data.sensor_data.temperature,
    " - Altitude: ", (int)lora_stm_data.sensor_data.altitude,
    " - Pressure: ", (int)lora_stm_data.sensor_data.pressure,
    " - Compass: ", (int)lora_stm_data.sensor_data.compass_degree,
    " - Wheather: ", (int)lora_stm_data.sensor_data.wheather_condition,
    " - Sfp status: ", (lora_sfp_data.status == 1) ? "Connected" : "Disconnected");


    printAll("\n\n\n");


    size_t previous_idle_time=0, previous_total_time=0;
    size_t idle_time, total_time;

    struct sysinfo memInfo;

    get_cpu_times(idle_time, total_time);

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


    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    writer.StartObject();

    writer.Key("terminal_status");
    writer.String((sfp_data.status == 1) ? "Connected" : "Disconnected");

    writer.Key("laser_diagonal");
    writer.Double(tracker.getDiagonalRate());

    writer.Key("laser_edge");
    writer.Double(tracker.getDiagonalRate());

    writer.Key("sfp_temp");
    writer.Double(sfp_data.temperature);

    writer.Key("sfp_vcc");
    writer.Uint(sfp_data.vcc);

    writer.Key("sfp_tx_bias");
    writer.Double(sfp_data.tx_bias);

    writer.Key("sfp_tx_power");
    writer.Double(sfp_data.tx_power);

    writer.Key("sfp_rx_power");
    writer.Double(sfp_data.rx_power);

    writer.Key("terminal_gps_string");
    writer.String(stm_data.gps_string.c_str());

    writer.Key("terminal_latitude");
    writer.Double(stm_data.gps_data.latitude);

    writer.Key("terminal_ns_indicator");
    writer.String((const char*)&stm_data.gps_data.ns_indicator);

    writer.Key("terminal_longnitude");
    writer.Double(stm_data.gps_data.longnitude);

    writer.Key("terminal_we_indicator");
    writer.String((const char*)&stm_data.gps_data.we_indicator);

    writer.Key("terminal_temperature");
    writer.Uint(stm_data.sensor_data.temperature);

    writer.Key("terminal_pressure");
    writer.Uint(stm_data.sensor_data.pressure);

    writer.Key("terminal_altitude");
    writer.Uint(stm_data.sensor_data.altitude);

    writer.Key("terminal_compass");
    writer.Uint(stm_data.sensor_data.compass_degree);

    writer.Key("cpu_usage");
    writer.Double(utilization);

    writer.Key("memory_usage");
    writer.Double(phys_mem_med);


    writer.Key("remote_terminal_status");
    writer.String((lora_sfp_data.status == 1) ? "Connected" : "Disconnected");

    writer.Key("remote_sfp_temp");
    writer.Double(lora_sfp_data.temperature);

    writer.Key("remote_sfp_vcc");
    writer.Uint(lora_sfp_data.vcc);

    writer.Key("remote_sfp_tx_bias");
    writer.Double(lora_sfp_data.tx_bias);

    writer.Key("remote_sfp_tx_power");
    writer.Double(lora_sfp_data.tx_power);

    writer.Key("remote_sfp_rx_power");
    writer.Double(lora_sfp_data.rx_power);

    writer.Key("remote_terminal_gps_string");
    writer.String(lora_stm_data.gps_string.c_str());

    writer.Key("remote_terminal_latitude");
    writer.Double(lora_stm_data.gps_data.latitude);

    writer.Key("remote_terminal_ns_indicator");
    writer.String((const char*)&lora_stm_data.gps_data.ns_indicator);

    writer.Key("remote_terminal_longnitude");
    writer.Double(lora_stm_data.gps_data.longnitude);

    writer.Key("remote_terminal_we_indicator");
    writer.String((const char*)&lora_stm_data.gps_data.we_indicator);

    writer.Key("remote_terminal_temperature");
    writer.Uint(lora_stm_data.sensor_data.temperature);

    writer.Key("remote_terminal_pressure");
    writer.Uint(lora_stm_data.sensor_data.pressure);

    writer.Key("remote_terminal_altitude");
    writer.Uint(lora_stm_data.sensor_data.altitude);

    writer.Key("remote_terminal_compass");
    writer.Uint(lora_stm_data.sensor_data.compass_degree);

    writer.EndObject();

    std::ofstream myfile;
    myfile.open ("/var/www/html/json");
    myfile << s.GetString();
    myfile.close();

}

std::vector<size_t> get_cpu_times() {
    std::ifstream proc_stat("/proc/stat");
    proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
    std::vector<size_t> times;
    for (size_t time; proc_stat >> time; times.push_back(time));
    return times;
}

bool get_cpu_times(size_t &idle_time, size_t &total_time) {
    const std::vector<size_t> cpu_times = get_cpu_times();
    if (cpu_times.size() < 4)
        return false;
    idle_time = cpu_times[3];
    total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
    return true;
}




