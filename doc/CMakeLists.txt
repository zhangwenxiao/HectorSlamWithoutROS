find_package(Doxygen)
if(DOXYGEN_FOUND)
    # Search for Sphinx
    set(SPHINX_PATH "" CACHE PATH
        "Path to the directory containing the sphinx-build program")
    find_program(SPHINX_BUILD sphinx-build PATHS ${SPHINX_PATH})
    if(NOT SPHINX_BUILD)
        message(FATAL_ERROR
            "Sphinx was not found. Set SPHINX_PATH to the directory containing the sphinx-build executable, or disable BUILD_DOCUMENTATION.")
    endif(NOT SPHINX_BUILD)

    set(html_dir "${CMAKE_CURRENT_BINARY_DIR}/html")
    set(doxygen_dir "${html_dir}/doxygen")
    file(MAKE_DIRECTORY ${html_dir})
    file(MAKE_DIRECTORY ${doxygen_dir})

    # Doxygen part
    set(doxyfile "${CMAKE_CURRENT_BINARY_DIR}/doxyfile")
    configure_file(doxyfile.in ${doxyfile})
    add_custom_target(doxygen_doc ${DOXYGEN_EXECUTABLE} ${doxyfile})

    # Sphinx part
    set(conf_dir "${CMAKE_CURRENT_BINARY_DIR}/conf")
    file(MAKE_DIRECTORY "${conf_dir}")
    file(MAKE_DIRECTORY "${conf_dir}/_static")
    set(conf_py "${conf_dir}/conf.py")
    configure_file(conf.py.in ${conf_py})
    add_custom_target(sphinx_doc ALL sphinx-build -b html -c ${conf_dir}
        ${CMAKE_CURRENT_SOURCE_DIR}/content ${CMAKE_CURRENT_BINARY_DIR}/html
        DEPENDS doxygen_doc)
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html" DESTINATION
        "share/doc/${PROJECT_NAME_LOWER}-${PROJECT_VERSION_MAJOR}"
        COMPONENT doc)
else(DOXYGEN_FOUND)
    message(FATAL_ERROR
        "Doxygen was not found. Cannot build documentation. Disable BUILD_DOCUMENTATION to continue")
endif(DOXYGEN_FOUND)

