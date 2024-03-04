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
#ifndef __SYMON_SERVICE_HPP
#define __SYMON_SERVICE_HPP

#include "symon_method_id.hpp"
#include "vst_message.hpp"

    
#include "symon_query.hpp"

namespace symon {

struct symon_message_processor
{
    vst::message_error_code operator()(const vst::buffer& input, vst::buffer& output);

private:
    symon_query_message_processor symon_query_msg_proc_;
    
};

} // namespace symon

#endif //__SYMON_SERVICE_HPP