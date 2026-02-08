cmake_minimum_required(VERSION 3.16)
project(lvgl_demon C)

set(CMAKE_C_STANDARD 99)

# 设置 SDL2 路径
set(SDL2_PATH ${CMAKE_CURRENT_SOURCE_DIR}/SDL2)
set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
set(SDL2_LIBRARY "${SDL2_PATH}/lib/libSDL2.dll.a")

# 包含目录
include_directories(${SDL2_INCLUDE_DIR})

# 设置 LVGL 路径
set(LVGL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lvgl)
set(LVGL_SRC_DIR ${LVGL_DIR}/src)

# 包含 LVGL 目录
include_directories(${LVGL_DIR})
include_directories(${LVGL_SRC_DIR})
include_directories(${LVGL_SRC_DIR}/core)
include_directories(${LVGL_SRC_DIR}/misc)
include_directories(${LVGL_SRC_DIR}/widgets)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# 查找 LVGL 源文件
file(GLOB_RECURSE LVGL_SOURCES
    "${LVGL_SRC_DIR}/*.c"
    "${LVGL_SRC_DIR}/core/*.c"
    "${LVGL_SRC_DIR}/misc/*.c"
    "${LVGL_SRC_DIR}/widgets/*.c"
)

# 添加你的源文件
file(GLOB_RECURSE SOURCES "src/*.c")

# 创建可执行文件
add_executable(lvgl_demon ${SOURCES} ${LVGL_SOURCES})

# 链接 SDL2 库
target_link_libraries(lvgl_demon ${SDL2_LIBRARY})

# 关键：移除 -mwindows 标志，使用控制台子系统
set_target_properties(lvgl_demon PROPERTIES
    LINK_FLAGS "-Wl,-subsystem,console"
)

# 复制 DLL 文件到输出目录
if(EXISTS "${SDL2_PATH}/bin/SDL2.dll")
    add_custom_command(TARGET lvgl_demon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_PATH}/bin/SDL2.dll"
            "$<TARGET_FILE_DIR:lvgl_demon>"
        COMMENT "Copying SDL2.dll to output directory"
    )
endif()