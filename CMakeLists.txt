cmake_minimum_required(VERSION 3.10)
project(miniaudio_project VERSION 1.0)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(MINIAUDIO_EXAMPLES "Build miniaudio examples" ON)

# Platform-specific libraries
if(APPLE)
    find_library(CORE_AUDIO_FRAMEWORK CoreAudio REQUIRED)
    find_library(AUDIO_TOOLBOX_FRAMEWORK AudioToolbox REQUIRED)
    set(PLATFORM_LIBS ${CORE_AUDIO_FRAMEWORK} ${AUDIO_TOOLBOX_FRAMEWORK})
elseif(UNIX)
    set(PLATFORM_LIBS pthread m dl)
endif()

# Create miniaudio implementation file
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/miniaudio.c 
    "#define MINIAUDIO_IMPLEMENTATION\n#include \"${CMAKE_CURRENT_SOURCE_DIR}/miniaudio.h\"\n")

# Create miniaudio static library instead of shared
add_library(miniaudio STATIC ${CMAKE_CURRENT_BINARY_DIR}/miniaudio.c)
target_include_directories(miniaudio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT WIN32)
    target_link_libraries(miniaudio PRIVATE ${PLATFORM_LIBS})
endif()

if(MINIAUDIO_EXAMPLES)
    add_executable(audio_example main.c)
    target_link_libraries(audio_example PRIVATE miniaudio)
    if(WIN32)
        # On Windows, we need to link against these system libraries
        target_link_libraries(audio_example PRIVATE ole32 user32 winmm)
    endif()
endif()

# Installation rules
install(TARGETS miniaudio
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(FILES miniaudio.h DESTINATION include)