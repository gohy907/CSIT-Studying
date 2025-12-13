cmake_minimum_required(VERSION 3.16)

project(RoadSim C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOLUTION_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Подключаем raylib
add_subdirectory(external/raylib)
add_compile_definitions(RAYGUI_IMPLEMENTATION)

# Источники проекта
file(GLOB_RECURSE PROJECT_SOURCES
    src/*.cpp
    src/*.h
)

# Статические ресурсы
set(STATIC_RESOURCES
    ${CMAKE_SOURCE_DIR}/static/cars.png
    ${CMAKE_SOURCE_DIR}/static/HYWenHei.ttf
)

# Генерируем C-массивы с ресурсами (Linux + Windows)
set(RESOURCE_HEADER ${CMAKE_BINARY_DIR}/resources.h)
set(RESOURCE_SOURCE ${CMAKE_BINARY_DIR}/resources.c)

file(WRITE ${RESOURCE_HEADER} "#ifndef RESOURCES_H\n#define RESOURCES_H\n\n")
file(WRITE ${RESOURCE_SOURCE} "#include \"resources.h\"\n#include <raylib.h>\n\n")

foreach(resource ${STATIC_RESOURCES})
    get_filename_component(resource_name ${resource} NAME_WE)
    string(TOUPPER ${resource_name} RESOURCE_ID)
    string(REPLACE "-" "_" RESOURCE_ID ${RESOURCE_ID})
    string(REPLACE "." "_" RESOURCE_ID ${RESOURCE_ID})
    
    # Читаем файл как HEX и конвертируем в C-массив
    file(READ ${resource} resource_data HEX)
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " resource_array ${resource_data})
    
    file(APPEND ${RESOURCE_HEADER} 
        "extern const unsigned char ${RESOURCE_ID}_data[];\n"
        "extern const int ${RESOURCE_ID}_size;\n"
    )
    file(APPEND ${RESOURCE_SOURCE}
        "const unsigned char ${RESOURCE_ID}_data[] = {${resource_array}};\n"
        "const int ${RESOURCE_ID}_size = sizeof(${RESOURCE_ID}_data);\n\n"
    )
endforeach()

file(APPEND ${RESOURCE_HEADER} "\n#endif\n")

# Добавляем сгенерированные файлы
list(APPEND PROJECT_SOURCES 
    ${RESOURCE_SOURCE}
)

# Windows ресурсы (дополнительно)
if(WIN32)
    set(RESOURCE_FILE ${CMAKE_BINARY_DIR}/resources.rc)
    file(WRITE ${RESOURCE_FILE} "#include <windows.h>\n")
    foreach(resource ${STATIC_RESOURCES})
        get_filename_component(resource_name ${resource} NAME)
        file(COPY ${resource} DESTINATION ${CMAKE_BINARY_DIR})
        file(APPEND ${RESOURCE_FILE} "${resource_name} RCDATA \"${CMAKE_BINARY_DIR}/${resource_name}\"\n")
    endforeach()
    list(APPEND PROJECT_SOURCES ${RESOURCE_FILE})
endif()

# Создаем исполняемый файл
add_executable(RoadSim ${PROJECT_SOURCES})

target_include_directories(RoadSim PRIVATE 
    src 
    ${CMAKE_BINARY_DIR}  # для resources.h
)

target_link_libraries(RoadSim PRIVATE raylib)

message(STATUS "Target system: ${CMAKE_SYSTEM_NAME}")

# Платформо-зависимые настройки
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Configuring for macOS target")
    target_link_libraries(RoadSim PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreAudio"
        "-framework AudioToolbox"
    )

elseif(WIN32)
    message(STATUS "Configuring for Windows target")
    
    # Полностью статическая сборка Windows С КОНСОЛЬЮ
    target_link_options(RoadSim PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )
    
    # Windows библиотеки
    target_link_libraries(RoadSim PRIVATE
        -lopengl32
        -lgdi32
        -lwinmm
        -lole32
        -loleaut32
        -luuid
        -lversion
    )

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Configuring for Linux target")
    target_link_libraries(RoadSim PRIVATE m pthread dl)
    
    # Статическая сборка Linux (опционально)
    target_link_options(RoadSim PRIVATE -static-libgcc -static-libstdc++)
endif()
