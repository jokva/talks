add_custom_target(
    my-package ALL
    SOURCES ${setup.py}
    DEPENDS ${setup.py}
    VERBATIM
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${python} ${setup.py}
        build_ext --inplace
        build # setup.py build args
            --cmake-executable ${CMAKE_COMMAND}
            --generator ${CMAKE_GENERATOR}
            ${PYTHON_BUILD_TYPE}
        -- # scikit-build cmake args
            -Dcore_DIR=${LIB_BINARY_DIR}
            -DCMAKE_INSTALL_RPATH_USE_LINK_PATH=ON
            -DCMAKE_INSTALL_RPATH=$<TARGET_FILE_DIR:core>
            -DCMAKE_INSTALL_NAME_DIR=$<TARGET_FILE_DIR:core>
)
add_dependencies(my-package core)
