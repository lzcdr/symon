cmake_minimum_required(VERSION 3.15)


set(SYMON_SERVER_PROJECT_NAME symon_server)
project(${SYMON_SERVER_PROJECT_NAME} VERSION 0.0.1 LANGUAGES C CXX)

set(SYMON_CLIENT_PROJECT_NAME symon_client)
project(${SYMON_CLIENT_PROJECT_NAME} VERSION 0.0.1 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

if (WIN32)
  add_definitions(-D_WIN32_WINNT=0x0A00)
endif()

if(MSVC)
    message("MSVC compiler detected")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DEBUG /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    message("Non-MSVC compiler detected")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options(
            "-std=c++2a" "-Wall" "-fno-strict-aliasing" "-pthread" "-pedantic" "-ggdb3" "-O0")
    else()
        add_compile_options(
            "-std=c++2a" "-Wall" "-fno-strict-aliasing" "-pthread" "-pedantic" "-O2")
    endif()
endif()

set(BOOST_ROOT "C:/Development/boost_1_84_0")
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS system)

set(SERVER_SOURCE_FILES 
    vst_server.hpp 
    vst_io_context_pool.hpp 
    vst_connection.hpp 
    vst_message.hpp 
    vst_buffer.hpp 
    vst_log_mockup.hpp
)

set(CLIENT_SOURCE_FILES 
    vst_client.hpp 
    vst_log_mockup.hpp
)

set(SYMON_SERVER_SOURCE_FILES ${SERVER_SOURCE_FILES}
    symon_service.hpp symon_service.cpp
    symon_query.hpp symon_query.cpp
)
add_executable(${SYMON_SERVER_PROJECT_NAME} ${SYMON_SERVER_SOURCE_FILES})
if (WIN32)
target_link_libraries(${SYMON_SERVER_PROJECT_NAME} PUBLIC Boost::boost pdh)
else ()
target_link_libraries(${SYMON_SERVER_PROJECT_NAME} PUBLIC Boost::boost)
endif()

set(SYMON_CLIENT_SOURCE_FILES ${CLIENT_SOURCE_FILES}
    symon_client.hpp symon_client.cpp symon_client_test.cpp
    symon_query.hpp symon_query.cpp
)
add_executable(${SYMON_CLIENT_PROJECT_NAME} ${SYMON_CLIENT_SOURCE_FILES})
if (WIN32)
target_link_libraries(${SYMON_CLIENT_PROJECT_NAME} PUBLIC Boost::boost pdh)
else ()
target_link_libraries(${SYMON_CLIENT_PROJECT_NAME} PUBLIC Boost::boost)
endif()