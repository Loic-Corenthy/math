function(run_clang_tidy_on_interface TARGET_NAME LINK_TARGET_NAME FILES_TO_CHECK)
    set(CLANG_TIDY_TMP_EXE_NAME "run_clang_tidy_on_${TARGET_NAME}")
    add_executable(${CLANG_TIDY_TMP_EXE_NAME})

    set(TMP_MAIN_FILE ${CMAKE_BINARY_DIR}/tmp_${TARGET_NAME}_main.cpp)

    # Clear previous file if exists
    file(WRITE ${TMP_MAIN_FILE} "")

    # Includes headers to be checked by clang-tidy
    foreach(FILE ${FILES_TO_CHECK})
        file(APPEND ${TMP_MAIN_FILE} "#include <${FILE}>\n")
    endforeach(FILE IN ${FILES_TO_CHECK})

    # Add a minimal main to create an executable
    file(APPEND ${TMP_MAIN_FILE} "\nint main(){return 0;}\n")

    target_sources(${CLANG_TIDY_TMP_EXE_NAME} PUBLIC ${TMP_MAIN_FILE})

    target_link_libraries(${CLANG_TIDY_TMP_EXE_NAME} PRIVATE ${LINK_TARGET_NAME})

    target_compile_features(${CLANG_TIDY_TMP_EXE_NAME} PUBLIC cxx_std_20)

    set_target_properties(${CLANG_TIDY_TMP_EXE_NAME} PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(${CLANG_TIDY_TMP_EXE_NAME} PROPERTIES CXX_EXTENSIONS OFF)
    set_target_properties(${CLANG_TIDY_TMP_EXE_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")

    file(COPY_FILE ${CMAKE_SOURCE_DIR}/.clang-tidy ${CMAKE_BINARY_DIR}/.clang-tidy ONLY_IF_DIFFERENT)
endfunction()
