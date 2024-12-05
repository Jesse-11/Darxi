cmake_minimum_required(VERSION 3.16)
project(Darxi_Networking VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure CMAKE_PREFIX_PATH includes Qt installation directory
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/lib/x86_64-linux-gnu/cmake/Qt6")

function(ensure_packages_installed)
    find_program(APT_EXECUTABLE apt)
    if(NOT APT_EXECUTABLE)
        message(FATAL_ERROR "apt package manager not found. This project requires a Debian-based system.")
        return()
    endif()

    set(REQUIRED_PACKAGES
        qt6-base-dev
        build-essential
        cmake
    )

    foreach(PACKAGE ${REQUIRED_PACKAGES})
        execute_process(
            COMMAND dpkg -l ${PACKAGE}
            OUTPUT_VARIABLE PKG_CHECK
            ERROR_QUIET
        )
        
        if(NOT PKG_CHECK MATCHES "ii  ${PACKAGE}")
            message(STATUS "${PACKAGE} not found. Attempting to install...")
            execute_process(
                COMMAND sudo apt-get update
                COMMAND sudo apt-get install -y ${PACKAGE}
                RESULT_VARIABLE INSTALL_RESULT
            )
            
            if(NOT INSTALL_RESULT EQUAL 0)
                message(FATAL_ERROR "Failed to install ${PACKAGE}. Please install it manually.")
            endif()
        endif()
    endforeach()
endfunction()

# Check and install dependencies
ensure_packages_installed()

#find Qt packages
find_package(Qt6 COMPONENTS Core Network Widgets Sql REQUIRED)


#Enable automoc for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set path for resource files
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)


# Add source files
set(SOURCES
    src/main.cpp
    src/views/mainwindow.cpp
    src/views/loginview.cpp
    src/views/signupview.cpp
    src/views/dashboardview.cpp
    src/controllers/authcontroller.cpp
    src/models/user.cpp
    src/models/database/databasemanager.cpp
    src/controllers/dashboardcontroller.cpp
)

# Add header files
set(HEADERS
    src/views/mainwindow.h
    src/views/loginview.h
    src/views/signupview.h
    src/views/dashboardview.h
    src/controllers/authcontroller.h
    src/models/user.h
    src/models/database/databasemanager.h
    src/controllers/dashboardcontroller.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Qt6_INCLUDE_DIRS}
)

#link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Widgets
    Qt::Sql
)

# Output the Qt installation path for debugging
message(STATUS "Qt6 installation path: ${Qt6_DIR}")