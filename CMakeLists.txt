
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set (CMAKE_CXX_STANDARD 20)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

cmake_minimum_required (VERSION 3.8)

project ("CorE_Tests")

find_package(Vulkan REQUIRED) 
#target_link_libraries(CorE_Tests Vulkan::Vulkan)

add_compile_definitions(CORENGINE_USE_PLATFORM_WIN32)

add_executable (CorE_Tests "CorE_Tests.cpp")
#target_link_libraries(CorE_Tests CorEngine)

target_include_directories(CorE_Tests PUBLIC 
"../CorEngine/out/install/x64-debug/include"
)
target_link_directories(CorE_Tests PUBLIC "../CorEngine/out/install/x64-debug/lib")

list(APPEND CMAKE_PREFIX_PATH "../CorEngine/out/install/x64-debug/cmake")
message("███████████████████████████████████████████")
message("${CMAKE_PREFIX_PATH}")

find_package(CorEngine REQUIRED)

target_link_libraries(CorE_Tests PUBLIC CorE::CorEngine)
