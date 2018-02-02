set(CPACK_PACKAGE_NAME "Flexiport")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Flexible communications library.")
set(CPACK_PACKAGE_VENDOR "AIST")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Flexiport")
set(CPACK_PACKAGE_FILE_NAME "Flexiport-2.0.0")
set(CPACK_RESOURCE_FILE_LICENSE "/home/zwx/mycode/hokuyoaist/build/flexiport/COPYING.LESSER")

set(CPACK_COMPONENTS_ALL library)
set(CPACK_COMPONENT_LIBRARY_DISPLAY_NAME "Flexiport library")
set(CPACK_COMPONENT_LIBRARY_DESCRIPTION
    "The Flexiport library, for use with other applications.")
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

if(WIN32)
    set(CPACK_NSIS_HELP_LINK "https://github.com/gbiggs/flexiport")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/gbiggs/flexiport")
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_PACKAGE_EXECUTABLES flexiport_porttoport)
    if(INSTALL_DOCUMENTATION)
        set(CPACK_NSIS_MENU_LINKS
            "/usr/local/share/doc/flexiport-2/html/index.html"
            "API documentation")
    endif(INSTALL_DOCUMENTATION)
    string(REPLACE "/Flexiport" "" install_prefix_root
        "/usr/local")
    file(TO_NATIVE_PATH "${install_prefix_root}" install_prefix_root)
    set(CPACK_NSIS_INSTALL_ROOT "${install_prefix_root}")
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
        "  Rename \"$INSTDIR\\share\\flexiport-2\\flexiport-config.cmake\" \"$INSTDIR\\flexiport-config.cmake\"
  Rename \"$INSTDIR\\share\\flexiport-2\\flexiport-config-version.cmake\" \"$INSTDIR\\flexiport-config-version.cmake\"")
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
        "  Delete \"$INSTDIR\\flexiport-config.cmake\"
  Delete \"$INSTDIR\\flexiport-config-version.cmake\"")
endif(WIN32)

