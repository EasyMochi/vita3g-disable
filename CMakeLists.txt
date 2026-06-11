cmake_minimum_required(VERSION 3.1)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(vita3g-disable C)

include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

add_executable(${PROJECT_NAME}
        main.c
)

target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -O3
        -std=gnu99
)

target_link_options(${PROJECT_NAME} PRIVATE
        -nostdlib
        -Wl,-q
        -Wl,-e,module_start
)

target_link_libraries(${PROJECT_NAME}
        taihen_stub
        SceLibKernel_stub
)

vita_create_self(${PROJECT_NAME}.suprx ${PROJECT_NAME}
        CONFIG ${CMAKE_SOURCE_DIR}/exports.yml
)