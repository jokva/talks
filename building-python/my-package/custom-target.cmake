add_custom_target(
    my-package ALL
    VERBATIM
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${python} ${setup.py}
        build_ext --inplace
        build # setup.py build args
            --cmake-executable ${CMAKE_COMMAND}
            --generator ${CMAKE_GENERATOR}
        -- # scikit-build cmake args
            -Dcore_DIR=${LIB_BINARY_DIR}
            -DCMAKE_INSTALL_RPATH_USE_LINK_PATH=ON
            -DCMAKE_INSTALL_RPATH=$<TARGET_FILE_DIR:core>
            -DCMAKE_INSTALL_NAME_DIR=$<TARGET_FILE_DIR:core>
)
