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
#include "symon_service.hpp"
#include "vst_buffer.hpp"
#include "vst_server.hpp"
#include <thread>

namespace symon {

vst::message_error_code symon_message_processor::operator()(const vst::buffer& input, vst::buffer& output)
{
    switch (input.method_type_id()) {
        case static_cast<uint32_t>(symon_method_id::QUERY):
            return symon_query_msg_proc_(input, output);
        
        default:
            return vst::message_error_code::MESSAGE_PROCESSOR_NOT_FOUND;
    }
}

} // namespace symon

static const uint32_t MAX_MESSAGE_SIZE = 1024;

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cout << "Usage: provide two arguments - ip-address (127.0.0.1) and port" << std::endl;
        return 1;
    }
    std::string address = argv[1];
    std::string port = argv[2];

    vst::server<symon::symon_message_processor> srv(
        std::thread::hardware_concurrency(),
        MAX_MESSAGE_SIZE
    );
    srv.run(address, port);

    return 0;
}