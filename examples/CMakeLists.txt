include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${Flexiport_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

set(BOOST_ROOT "/opt/boost")
# Laser data reader example
add_executable(${PROJECT_NAME_LOWER}_example example.cpp)
target_link_libraries(${PROJECT_NAME_LOWER}_example
    ${PROJECT_NAME_LOWER})
##add
find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME_LOWER}_example ${OpenCV_LIBS})
find_package(Boost REQUIRED COMPONENTS system thread)
target_link_libraries(${PROJECT_NAME_LOWER}_example ${Boost_LIBRARIES})
##
install(TARGETS ${PROJECT_NAME_LOWER}_example
    DESTINATION ${BIN_INSTALL_DIR}
    RUNTIME DESTINATION bin
    COMPONENT examples)

# Get laser ID sample
add_executable(${PROJECT_NAME_LOWER}_getid getid.cpp)
target_link_libraries(${PROJECT_NAME_LOWER}_getid
    ${PROJECT_NAME_LOWER})
install(TARGETS ${PROJECT_NAME_LOWER}_getid
    DESTINATION ${BIN_INSTALL_DIR}
    RUNTIME DESTINATION bin
    COMPONENT examples)

# Install example sources
install(FILES CMakeLists.txt.example
    DESTINATION ${SHARE_INSTALL_DIR}/examples
    RENAME CMakeLists.txt
    COMPONENT examples)
install(FILES example.cpp getid.cpp
    example_urg_04lx.logr example_urg_04lx.logw
    example_utm_30lx.logr example_utm_30lx.logw
    example_uxm_30lx_e.logr example_uxm_30lx_e.logw
    96-hokuyo.rules
    DESTINATION ${SHARE_INSTALL_DIR}/examples
    COMPONENT examples)
install(FILES example.readme
    DESTINATION ${SHARE_INSTALL_DIR}/examples
    RENAME README.txt
    COMPONENT examples)

# For packaging
set(EXAMPLE_EXECUTABLES ${PROJECT_NAME_LOWER}_example HokuyoAIST_Example
    ${PROJECT_NAME_LOWER}_getid GetID
    PARENT_SCOPE)

