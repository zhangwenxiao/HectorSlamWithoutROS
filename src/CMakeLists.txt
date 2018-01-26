set(srcs hokuyo_errors.cpp
    scan_data.cpp
    sensor.cpp
    sensor_info.cpp
    )

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${Flexiport_INCLUDE_DIRS})
add_library(${PROJECT_NAME_LOWER} ${LIB_TYPE} ${srcs})
target_link_libraries(${PROJECT_NAME_LOWER} ${Flexiport_LIBRARIES})
if(HAVE_CLOCK_GETTIME)
    target_link_libraries(${PROJECT_NAME_LOWER} rt)
endif(HAVE_CLOCK_GETTIME)
set_target_properties(${PROJECT_NAME_LOWER} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})
install(TARGETS ${PROJECT_NAME_LOWER}
    EXPORT ${PROJECT_NAME_LOWER}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT library
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT library
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT library)
install(EXPORT ${PROJECT_NAME_LOWER}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    FILE ${PROJECT_NAME_LOWER}Depends.cmake)

