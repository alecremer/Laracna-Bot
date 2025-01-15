cmake_minimum_required(VERSION 3.16)

# Nome do projeto de testes
project(test_my_module)

# Adiciona o caminho do ESP-IDF
set(IDF_PATH "/home/ale/esp/esp-idf")
set(MAIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../main")
set(MOVEMENT_DIR "${MAIN_DIR}/movement")

# Adicionar arquivos de código fonte
set(SOURCES
    test_ik.cpp
    ${MOVEMENT_DIR}/ik.cpp
)


include_directories("${IDF_PATH}/components/unity/unity/src" ${MOVEMENT_DIR} ${MAIN_DIR})
add_library(unity STATIC "${IDF_PATH}/components/unity/unity/src/unity.c")

add_executable(test_runner ${SOURCES})

# Linkar com o ESP-IDF
target_link_libraries(test_runner PRIVATE pthread unity)