set(hdrs flexiport.h
    flexiport_types.h
    logfile.h
    logreaderport.h
    logwriterport.h
    port.h
    serialport.h
    tcpport.h
    timeout.h
    udpport.h
    )
install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

