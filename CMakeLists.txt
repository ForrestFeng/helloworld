cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(HelloWorld)

find_package(gtest CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(HelloWorld helloworld.cpp logparser.cpp)

#target_link_libraries(HelloWorld PRIVATE fmt::fmt)
target_link_libraries(HelloWorld GTest::gtest)