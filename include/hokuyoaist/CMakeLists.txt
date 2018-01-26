set(hdrs hokuyoaist.h
    hokuyo_errors.h
    scan_data.h
    sensor.h
    sensor_info.h
    utils.h
    )
install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

