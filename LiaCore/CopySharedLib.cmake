

function(CopySharedLib libname)
    if(WIN32)
        set(lib_path "${PROJECT_SOURCE_DIR}/Vendor/Dawn/${LIA_PLATFORM}/${CMAKE_BUILD_TYPE}/${libname}.dll")
    elseif(UNIX)
        set(lib_path "${PROJECT_SOURCE_DIR}/Vendor/Dawn/${LIA_PLATFORM}/${CMAKE_BUILD_TYPE}/${libname}.so")
    endif()
    add_custom_command(TARGET LiaCore POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
            ${lib_path}     # <--this is in-file
            $<TARGET_FILE_DIR:LiaCore>)  

endfunction()
