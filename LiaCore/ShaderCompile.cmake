
function(CompileShaders)



    file(GLOB_RECURSE GLSL_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/Resources/Shaders/*"
        )

    foreach(GLSL ${GLSL_SOURCE_FILES})
        message("Compiling ${GLSL}")

      get_filename_component(FILE_NAME ${GLSL} NAME)
      set(SPIRV "${PROJECT_BINARY_DIR}/Resources/Shaders/${FILE_NAME}.spv")
      add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/Resources/Shaders/"
        COMMAND ${glslangValidator} -V ${GLSL} -o ${SPIRV}
        DEPENDS ${GLSL})
      list(APPEND SPIRV_BINARY_FILES ${SPIRV})
    endforeach(GLSL)

    add_custom_target(
        Shaders 
        DEPENDS ${SPIRV_BINARY_FILES}
        )

    add_dependencies(LiaCore Shaders)

#    add_custom_command(TARGET LiaCore POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:LiaCore>/Shaders/"
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#            "${PROJECT_BINARY_DIR}/Shaders"
#            "${PROJECT_SOURCE_DIR}/LiaCore/Shaders/"
#            )
endfunction()