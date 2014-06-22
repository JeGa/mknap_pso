cmake_minimum_required(VERSION 2.8.11)
project(mknap_pso)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++11 -Wall -g")

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "E:/Programs/Qt/5.3/mingw482_32" "E:/Programs/Qwt-6.1.0")
find_package(Qt5Widgets REQUIRED)
find_package(Qwt REQUIRED)

file(GLOB_RECURSE ui_FORMS "ui/*.ui")
file(GLOB_RECURSE qrc_RESOURCES "res/*.qrc")
qt5_wrap_ui(ui_SOURCES ${ui_FORMS})
qt5_add_resources(qrc_SOURCES ${qrc_RESOURCES})

file(GLOB_RECURSE mknap_pso_SOURCES "src/*.cpp")
file(GLOB_RECURSE mknap_pso_HEADERS "src/*.h")

set(mknap_pso_INCLUDE_DIRS "")
foreach (_headerFile ${mknap_pso_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND mknap_pso_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES mknap_pso_INCLUDE_DIRS)

include_directories(${mknap_pso_INCLUDE_DIRS})
include_directories("include")
include_directories(${QWT_INCLUDE_DIR})

add_executable(mknap_pso ${mknap_pso_SOURCES} ${ui_SOURCES} ${qrc_SOURCES})

if(WIN32)
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    else(CMAKE_COMPILER_IS_GNUCXX)
        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not GCC)")
    endif(CMAKE_COMPILER_IS_GNUCXX)
endif(WIN32)

target_link_libraries(mknap_pso ${QT_QTMAIN_LIBRARY} Qt5::Widgets ${QWT_LIBRARY})
