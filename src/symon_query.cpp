/*
 * ------------------------------------------------------------------------------
 * Project: symon
 * Version: 0.0.1
 * Description: Tiny Command Line Interface Remote System Monitor.
 * Author: lzcdr
 * Date: 2024-03-04 10:07:41
 * ------------------------------------------------------------------------------
 * This file was automatically generated by the Bytesnap RPC (version 0.1.0) 
 * project generator.
 * ------------------------------------------------------------------------------
 */
#include "symon_query.hpp"
#include "bytesnap.hpp"
#include "request.hpp"
#include "response.hpp"

#ifdef _WIN32
#include <Pdh.h>
#include <windows.h>
#include <atomic>
#else
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/times.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#endif

namespace symon {

#ifdef _WIN32
    static PDH_HQUERY cpuQuery;
    static PDH_HCOUNTER cpuTotal;
    static std::atomic<bool> cpuQueryInited(false);
#endif

double symon_query_message_processor::get_cpu_load()
{
#ifdef _WIN32
    if (!cpuQueryInited.exchange(true)) {
        PdhOpenQuery(NULL, NULL, &cpuQuery);
        PdhAddEnglishCounter(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
        PdhCollectQueryData(cpuQuery);
    }
    PDH_FMT_COUNTERVALUE counterVal;
    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
    return counterVal.doubleValue;    
#else
    std::ifstream file("/proc/loadavg");
    std::string line;
    std::getline(file, line);
    std::istringstream ss(line);
    double loadAvg1, loadAvg5, loadAvg15;
    ss >> loadAvg1 >> loadAvg5 >> loadAvg15;
    int numCores = std::thread::hardware_concurrency();
    return (loadAvg1 / numCores) * 100.0;
#endif
}

void symon_query_message_processor::get_system_metrics(Response& response)
{
#ifdef _WIN32
    // memory
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);
    GlobalMemoryStatusEx(&memInfo);
    response.total_ram = memInfo.ullTotalPhys;
    response.free_ram = memInfo.ullAvailPhys;

    // disk
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
    GetDiskFreeSpaceEx("C:\\", &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes);
    response.total_disk_space = totalNumberOfBytes.QuadPart;
    response.free_disk_space = freeBytesAvailable.QuadPart;

    response.cpu_utilisation = this->get_cpu_load();
#else
    // memory
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("sysinfo");
        return;
    }
    response.total_ram = info.totalram;
    response.free_ram = info.freeram;

    // disk
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) {
        perror("statvfs");
        return;
    }
    response.total_disk_space = stat.f_frsize * stat.f_blocks;
    response.free_disk_space = stat.f_frsize * stat.f_bavail;

    // cpu utilisation
    response.cpu_utilisation = this->get_cpu_load();
#endif
}

vst::message_error_code symon_query_message_processor::operator()(const vst::buffer& input, vst::buffer& output)
{
    // decode request message
    Request request;
    bytesnap::reader rd(input.base());
    if (!Request::decode(request, rd)) {
        return vst::message_error_code::BAD_REQUEST_MESSAGE;
    }

    // TODO - process request, build response
    Response response;
    this->get_system_metrics(response);

    // encode response message
    output.base().clear();
    bytesnap::writer wr(output.base());
    std::size_t sz = Response::encode(response, wr);
    output.fit();

    return vst::message_error_code::OK;
}

} // namespace symon