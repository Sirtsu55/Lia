
find_package(Vulkan REQUIRED FATAL_ERROR COMPONENTS glslangValidator)
find_program(glslangValidator NAMES glslangValidator)
set (CMAKE_CXX_STANDARD 20)
message(${glslangValidator})


file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/LiaCore/Source/*")


add_executable(LiaCore ${SRC_FILES})

target_include_directories(LiaCore PUBLIC 
	"${PROJECT_SOURCE_DIR}/Vendor/glfw/include/"
	"${PROJECT_SOURCE_DIR}/Vendor/spdlog/include/"
	"${PROJECT_SOURCE_DIR}/Vendor/glm/"
	"${PROJECT_SOURCE_DIR}/Vendor/DiligentCore/Graphics/GraphicsEngineVulkan/interface/"
	"${PROJECT_SOURCE_DIR}/LiaCore/Source/"
)


message("$ENV{VULKAN_SDK}/Include/")

target_precompile_headers(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/LiaCore/Source/Core.h")

#target_link_libraries(LiaCore "vulkan")

target_link_directories(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/Vendor/glfw/src")
target_link_libraries(LiaCore "glfw")

target_link_directories(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/Vendor/spdlog/src")
target_link_libraries(LiaCore "spdlog")

include("${PROJECT_SOURCE_DIR}/LiaCore/ShaderCompile.cmake")
CompileShaders()

#Will copy the required Shared libraries to the executable directory
#add_custom_command(TARGET LiaCore POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:LiaCore> $<TARGET_FILE_DIR:LiaCore>
#  COMMAND_EXPAND_LISTS
#  )