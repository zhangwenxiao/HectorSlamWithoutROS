# Dissect the version specified in PROJECT_VERSION, placing the major,
# minor, revision and candidate components in PROJECT_VERSION_MAJOR, etc.
# _prefix: The prefix string for the version variable names.
macro(DISSECT_VERSION)
    # Find version components
    string(REGEX REPLACE "^([0-9]+).*" "\\1"
        PROJECT_VERSION_MAJOR "${PROJECT_VERSION}")
    string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1"
        PROJECT_VERSION_MINOR "${PROJECT_VERSION}")
    string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1"
        PROJECT_VERSION_REVISION "${PROJECT_VERSION}")
    string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1"
        PROJECT_VERSION_CANDIDATE "${PROJECT_VERSION}")
endmacro(DISSECT_VERSION)

