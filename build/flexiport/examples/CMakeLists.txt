include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)

# Serial port example
add_executable(${PROJECT_NAME_LOWER}_serial_example serial_example.cpp)
target_link_libraries(${PROJECT_NAME_LOWER}_serial_example
    ${PROJECT_NAME_LOWER})
install(TARGETS ${PROJECT_NAME_LOWER}_serial_example
    DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT examples)

# TCP port example
add_executable(${PROJECT_NAME_LOWER}_tcp_example tcp_example.cpp)
target_link_libraries(${PROJECT_NAME_LOWER}_tcp_example
    ${PROJECT_NAME_LOWER})
install(TARGETS ${PROJECT_NAME_LOWER}_tcp_example
    DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT examples)

# UDP port example
add_executable(${PROJECT_NAME_LOWER}_udp_example udp_example.cpp)
target_link_libraries(${PROJECT_NAME_LOWER}_udp_example
    ${PROJECT_NAME_LOWER})
install(TARGETS ${PROJECT_NAME_LOWER}_udp_example
    DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT examples)

# BT port example
add_executable(${PROJECT_NAME_LOWER}_rfcomm_example rfcomm_example.cpp)
target_link_libraries(${PROJECT_NAME_LOWER}_rfcomm_example
    ${PROJECT_NAME_LOWER})
install(TARGETS ${PROJECT_NAME_LOWER}_rfcomm_example
    DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT examples)

# PortToPort utility
if(NOT WIN32)
    add_executable(${PROJECT_NAME_LOWER}_porttoport porttoport.cpp)
    target_link_libraries(${PROJECT_NAME_LOWER}_porttoport
        ${PROJECT_NAME_LOWER})
    install(TARGETS ${PROJECT_NAME_LOWER}_porttoport
        DESTINATION ${BIN_INSTALL_DIR}
        COMPONENT examples)
    set(porttoport_eg porttoport.cpp)
endif(NOT WIN32)

# Install example sources
install(FILES CMakeLists.txt.example
    DESTINATION ${SHARE_INSTALL_DIR}/examples
    RENAME CMakeLists.txt
    COMPONENT examples)
install(FILES serial_example.cpp tcp_example.cpp
    udp_example.cpp example.logr example.logw ${porttoport_eg}
    DESTINATION ${SHARE_INSTALL_DIR}/examples
    COMPONENT examples)
install(FILES example.readme
    DESTINATION ${SHARE_INSTALL_DIR}/examples
    RENAME README.txt
    COMPONENT examples)

# For packaging
set(EXAMPLE_EXECUTABLES ${PROJECT_NAME_LOWER}_serial_example SerialExample
    ${PROJECT_NAME_LOWER}_tcp_example TCPExample
    ${PROJECT_NAME_LOWER}_udp_example UDPExample
    PARENT_SCOPE)
if(NOT WIN32)
    set(EXAMPLE_EXECUTABLES ${EXAMPLE_EXECUTABLES}
        ${PROJECT_NAME_LOWER}_porttoport PARENT_SCOPE)
endif(NOT WIN32)

