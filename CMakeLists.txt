cmake_minimum_required(VERSION 3.6)
project(cpp_gkrellm)

set(CMAKE_CXX_STANDARD 14)


#Example Lib
set(ExampleSrc src_sensor/Example.cpp src_sensor/Example.hpp)
add_library(Example SHARED ${ExampleSrc})
target_include_directories(Example PUBLIC modules)
set_target_properties(Example
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "~/.sensor/"
        )

#UserInfo Lib
set(userInfoModule src_sensor/UserInfo.cpp)
add_library(UserInfo SHARED ${userInfoModule})
target_include_directories(UserInfo PUBLIC modules)
set_target_properties(UserInfo
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "~/.sensor/"
        )

#NetworkInfo Lib
set(networkInfoModule src_sensor/NetworkModule.cpp)
add_library(NetworkInfo SHARED ${networkInfoModule})
target_include_directories(NetworkInfo PUBLIC modules)
set_target_properties(NetworkInfo
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "~/.sensor/"
        )

#EntropyInfo Lib
set(EntropyInfoModule src_sensor/EntropyModule.cpp)
add_library(EntropyInfo SHARED ${EntropyInfoModule})
target_include_directories(EntropyInfo PUBLIC modules)
set_target_properties(EntropyInfo
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "~/.sensor/"
        )

#CpuInfo Lib
set(cpuInfoModule src_sensor/CpuInfo.cpp)
add_library(CpuInfo SHARED ${cpuInfoModule})
target_include_directories(CpuInfo PUBLIC modules)
set_target_properties(CpuInfo
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "~/.sensor/"
        )

#Fly Lib
set(flyModule src_sensor/FlyModule.cpp)
add_library(FlyModule SHARED ${flyModule})
target_include_directories(FlyModule PUBLIC modules)
set_target_properties(FlyModule
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "~/.sensor/"
        )

#CPU Freq Lib
set(CpuFreqModuleSrc src_sensor/FrequencyPourcentage.hpp src_sensor/FrequencyPourcentage.cpp)
add_library(CpuFreqProcessesModule SHARED ${CpuFreqModuleSrc})
target_include_directories(CpuFreqProcessesModule PUBLIC modules)
set_target_properties(CpuFreqProcessesModule
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "~/.sensor/"
        )

#Sysinfo Lib
set(SysinfoModuleSrc src_sensor/SysinfoModule.hpp src_sensor/SysinfoModule.cpp)
add_library(SysinfoModule SHARED ${SysinfoModuleSrc})
target_include_directories(SysinfoModule PUBLIC modules)
set_target_properties(SysinfoModule
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "~/.sensor/"
        )

#CPUUSAGE Lib
set(CpuUsageModuleSrc src_sensor/CpuUsage.cpp src_sensor/CpuUsage.hpp)
add_library(CpuUsageModule SHARED ${CpuUsageModuleSrc})
target_include_directories(CpuUsageModule PUBLIC modules)
set_target_properties(CpuUsageModule
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "~/.sensor/"
        )

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-deprecated-declarations")
set(SOURCE_FILES utils/DynamicLibrary.cpp utils/DynamicLibrary.hpp utils/DirectoryStream.cpp utils/DirectoryStream.hpp)
set(SOURCE_FILES ${SOURCE_FILES} main.cpp)
set(SOURCE_FILES ${SOURCE_FILES} core/Core.cpp core/Core.hpp)
set(SOURCE_FILES ${SOURCE_FILES} modules/IMonitorModule.hpp modules/AMonitorModule.hpp)
set(SOURCE_FILES ${SOURCE_FILES} displays/IMonitorDisplay.hpp displays/Ressource.hpp displays/Ressource.hh)
set(SOURCE_FILES ${SOURCE_FILES} displays/SfmlDisplay.cpp displays/SfmlDisplay.hpp)
set(SOURCE_FILES ${SOURCE_FILES} displays/NcursesDisplay.cpp displays/NcursesDisplay.hpp displays/NcursesWindow.cpp displays/NcursesWindow.hpp)

add_executable(cpp_gkrellm ${SOURCE_FILES})
target_include_directories(cpp_gkrellm PUBLIC modules utils displays)
target_link_libraries(cpp_gkrellm dl ncurses sfml-graphics sfml-window sfml-system)

set(SOURCE_TEST_DATE src_sensor/DateModule.cpp src_sensor/DateModule.hpp unit_test/testDateModule.cpp modules/AMonitorModule.hpp modules/IMonitorModule.hpp)
add_executable(testsDate ${SOURCE_TEST_DATE})
target_include_directories(testsDate PUBLIC modules utils src_sensor)

set(SOURCE_TEST_OS src_sensor/UserInfo.hpp src_sensor/UserInfo.cpp unit_test/testOsModule.cpp modules/AMonitorModule.hpp modules/IMonitorModule.hpp)
add_executable(testsOS ${SOURCE_TEST_OS})
target_include_directories(testsOS PUBLIC modules utils src_sensor)

set(SOURCE_TEST_NETWORK src_sensor/NetworkModule.hpp src_sensor/NetworkModule.cpp unit_test/testNetworkModule.cpp modules/AMonitorModule.hpp modules/IMonitorModule.hpp)
add_executable(testsNETWORK ${SOURCE_TEST_NETWORK})
target_include_directories(testsNETWORK PUBLIC modules utils src_sensor)

set(SOURCE_TEST_CPU modules/AMonitorModule.hpp modules/IMonitorModule.hpp unit_test/testCpuInfoModule.cpp src_sensor/CpuInfo.hpp src_sensor/CpuInfo.cpp)
add_executable(testsCPU ${SOURCE_TEST_CPU})
target_include_directories(testsCPU PUBLIC modules utils src_sensor)

set(SOURCE_TEST_CPU_FREQ modules/AMonitorModule.hpp modules/IMonitorModule.hpp unit_test/testFreqPercent.cpp src_sensor/FrequencyPourcentage.hpp src_sensor/FrequencyPourcentage.cpp)
add_executable(testsCPU_FREQ ${SOURCE_TEST_CPU_FREQ})
target_include_directories(testsCPU_FREQ PUBLIC modules utils src_sensor)

set(SOURCE_TEST_FLY modules/AMonitorModule.hpp modules/IMonitorModule.hpp unit_test/testFlyModule.cpp src_sensor/FlyModule.hpp src_sensor/FlyModule.cpp)
add_executable(testsFLY ${SOURCE_TEST_FLY})
target_include_directories(testsFLY PUBLIC modules utils src_sensor)

set(SOURCE_CPU_USAGE modules/AMonitorModule.hpp modules/IMonitorModule.hpp unit_test/testCpuUsage.cpp src_sensor/CpuUsage.hpp src_sensor/CpuUsage.cpp)
add_executable(testsCPUUSAGE ${SOURCE_CPU_USAGE})
target_include_directories(testsCPUUSAGE PUBLIC modules utils src_sensor)

set_target_properties( testsCPUUSAGE testsFLY testsCPU testsCPU_FREQ testsNETWORK testsOS testsDate
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin_tests"
        )