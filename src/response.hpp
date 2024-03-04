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

// response.hpp

#ifndef __RESPONSE_HPP
#define __RESPONSE_HPP
 
#include "bytesnap.hpp"



namespace symon {

struct Response
{
    uint32_t signature = 3735928559;
    uint64_t total_ram;
    uint64_t free_ram;
    uint64_t total_disk_space;
    uint64_t free_disk_space;
    double cpu_utilisation;

    Response() {}

    template <typename T = bytesnap::writer> static size_t encode(const Response& source, T& writer) {
        size_t before = writer.size();

        writer.write_uint32_t(source.signature);
        writer.write_uint64_t(source.total_ram);
        writer.write_uint64_t(source.free_ram);
        writer.write_uint64_t(source.total_disk_space);
        writer.write_uint64_t(source.free_disk_space);
        writer.write_double(source.cpu_utilisation);

        size_t after = writer.size();
        return after - before;
    }

    template <typename T = bytesnap::reader> static bool decode(Response& target, T& reader) {
        std::optional<uint32_t> signature = reader.read_uint32_t();
        if (!signature) return false;
        target.signature = signature.value();
        std::optional<uint64_t> total_ram = reader.read_uint64_t();
        if (!total_ram) return false;
        target.total_ram = total_ram.value();
        std::optional<uint64_t> free_ram = reader.read_uint64_t();
        if (!free_ram) return false;
        target.free_ram = free_ram.value();
        std::optional<uint64_t> total_disk_space = reader.read_uint64_t();
        if (!total_disk_space) return false;
        target.total_disk_space = total_disk_space.value();
        std::optional<uint64_t> free_disk_space = reader.read_uint64_t();
        if (!free_disk_space) return false;
        target.free_disk_space = free_disk_space.value();
        std::optional<double> cpu_utilisation = reader.read_double();
        if (!cpu_utilisation) return false;
        target.cpu_utilisation = cpu_utilisation.value();

        return true;
    }

};

} // namespace symon

#endif // __RESPONSE_HPP