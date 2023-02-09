cmake_minimum_required(VERSION 3.15)
project(SCZR_VoiceChangerSystem)

set(CMAKE_CXX_STANDARD 17)

# variables
set(SUPERVISOR supervisor)
set(SUPPLIER supplier)
set(VOICE_CHANGER voiceChanger)
set(CONSUMER consumer)
set(LATENCY_TEST latencyTest)

add_executable(${SUPERVISOR} src/Supervisor/main.cpp src/alsa.cpp)

add_executable(${SUPPLIER} src/Supplier/supplier.cpp src/alsa.cpp)
add_executable(${VOICE_CHANGER} src/VoiceChanger/voiceChanger.cpp src/alsa.cpp)
add_executable(${CONSUMER} src/Consumer/consumer.cpp src/alsa.cpp)
add_executable(${LATENCY_TEST} src/latencyTest.cpp src/alsa.cpp)

#linking ALSA
target_link_libraries(${SUPERVISOR} asound)
target_link_libraries(${SUPPLIER} asound)
target_link_libraries(${VOICE_CHANGER} asound)
target_link_libraries(${CONSUMER} asound)
target_link_libraries(${LATENCY_TEST} asound)