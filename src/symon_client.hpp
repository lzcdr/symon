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
#ifndef __SYMON_CLIENT_HPP
#define __SYMON_CLIENT_HPP

#include <vector>
#include <string>
#include <cstdint>
#include "vst_buffer.hpp"
#include "vst_client.hpp"
#include "symon_method_id.hpp"


#include "response.hpp"
#include "request.hpp"

namespace symon {

class symon_client
{
public:
    symon_client(const std::string& ip_address, const std::string& port);

    symon_client(const symon_client&) = delete;
    symon_client& operator=(const symon_client&) = delete;
    
    bool symon_query_request(const Request& request, Response& reply);

private:
    std::vector<uint8_t> request_base_;
    std::vector<uint8_t> reply_base_;
    boost::asio::io_context io_context_;
    vst::client client_;
    uint32_t key_;
};

} // namespace symon

#endif //__SYMON_CLIENT_HPP