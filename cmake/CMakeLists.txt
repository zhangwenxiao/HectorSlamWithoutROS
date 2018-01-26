set(PKG_DEPS flexiport)
set(PKG_LIBS "-l${PROJECT_NAME_LOWER} -lrt")
set(pkg_conf_file ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}.pc)
configure_file(${PROJECT_NAME_LOWER}.pc.in ${pkg_conf_file} @ONLY)
install(FILES ${pkg_conf_file}
    DESTINATION ${LIB_INSTALL_DIR}/pkgconfig/ COMPONENT library)

# Install CMake modules
set(cmake_config ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config.cmake)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME_LOWER}-config.cmake.in
    ${cmake_config} @ONLY)
set(cmake_version_config
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake.in
    ${cmake_version_config} @ONLY)
set(cmake_mods ${cmake_config} ${cmake_version_config})
install(FILES ${cmake_mods} DESTINATION ${SHARE_INSTALL_DIR} COMPONENT library)

