set(CPACK_PACKAGE_NAME "HokuyoAIST")
set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Hokuyo range sensor driver.")
set(CPACK_PACKAGE_VENDOR "Geoffrey Biggs, AIST")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "HokuyoAIST")
set(CPACK_PACKAGE_FILE_NAME "HokuyoAIST-3.0.2")
set(CPACK_RESOURCE_FILE_LICENSE "/home/zwx/mycode/slam_using_offical_code/COPYING.LESSER")

set(CPACK_COMPONENTS_ALL library)
set(CPACK_COMPONENT_LIBRARY_DISPLAY_NAME "HokuyoAIST library")
set(CPACK_COMPONENT_LIBRARY_DESCRIPTION
    "The HokuyoAIST library, for use with other applications.")
set(INSTALL_EXAMPLES ON)
if(INSTALL_EXAMPLES)
    set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} examples)
    set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Examples")
    set(CPACK_COMPONENT_EXAMPLES_DESCRIPTION
        "Example source files and utilities.")
    set(CPACK_COMPONENT_EXAMPLES_DEPENDS library)
endif(INSTALL_EXAMPLES)
set(INSTALL_DOCUMENTATION ON)
if(INSTALL_DOCUMENTATION)
    set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} documentation)
    set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "Documentation")
    set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION
        "API documentation")
    set(CPACK_COMPONENT_DOCUMENTATION_DEPENDS library)
endif(INSTALL_DOCUMENTATION)

IF (WIN32)
    set(CPACK_NSIS_HELP_LINK "https://github.com/gbiggs/hokuyoaist")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/gbiggs/hokuyoaist")
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_PACKAGE_EXECUTABLES hokuyoaist_example;HokuyoAIST_Example)
    if(INSTALL_DOCUMENTATION)
        set(CPACK_NSIS_MENU_LINKS
            "/usr/local/share/doc/hokuyoaist-3/html/index.html"
            "API documentation")
    endif(INSTALL_DOCUMENTATION)
    string(REPLACE "/HokuyoAIST" "" install_prefix_root
        "/usr/local")
    file(TO_NATIVE_PATH "${install_prefix_root}" install_prefix_root)
    set(CPACK_NSIS_INSTALL_ROOT "${install_prefix_root}")
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
        "  Rename \"$INSTDIR\\share\\hokuyoaist-3\\hokuyoaist-config.cmake\" \"$INSTDIR\\hokuyoaist-config.cmake\"
  Rename \"$INSTDIR\\share\\hokuyoaist-3\\hokuyoaist-config-version.cmake\" \"$INSTDIR\\hokuyoaist-config-version.cmake\"")
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
        "  Delete \"$INSTDIR\\hokuyoaist-config.cmake\"
  Delete \"$INSTDIR\\hokuyoaist-config-version.cmake\"")
ENDIF (WIN32)

