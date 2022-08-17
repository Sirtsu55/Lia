

set (CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/LiaCore/*")

list(APPEND SRC_FILES ${SRC_C_FILES})

add_executable(LiaCore ${SRC_FILES})

target_include_directories(LiaCore PUBLIC 
	"${PROJECT_SOURCE_DIR}/Vendor/glfw/include/"
	"${PROJECT_SOURCE_DIR}/Vendor/spdlog/include/"
	"${PROJECT_SOURCE_DIR}/Vendor/glm/"
	"${PROJECT_SOURCE_DIR}/LiaCore/Source/")

target_precompile_headers(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/LiaCore/Source/Core.h")

#target_link_libraries(LiaCore "vulkan")

target_link_directories(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/Vendor/glfw/src")
target_link_libraries(LiaCore "glfw")

target_link_directories(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/Vendor/spdlog/src")
target_link_libraries(LiaCore "spdlog")
