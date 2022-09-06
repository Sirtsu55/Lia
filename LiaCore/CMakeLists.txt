
find_package(Vulkan REQUIRED FATAL_ERROR COMPONENTS glslangValidator)
find_program(glslangValidator NAMES glslangValidator)
set (CMAKE_CXX_STANDARD 20)
message(${glslangValidator})

#IMGUI Sources
file(GLOB IMGUI_SRC_FILES "${PROJECT_SOURCE_DIR}/Vendor/imgui/*.cpp"
"${PROJECT_SOURCE_DIR}/Vendor/imgui/backends/imgui_impl_glfw.cpp"
"${PROJECT_SOURCE_DIR}/Vendor/imgui/backends/imgui_impl_wgpu.cpp")

#list(APPEND IMGUI_SRC_FILES "${PROJECT_SOURCE_DIR}/Vendor/imgui/backends/imgui_impl_glfw.cpp${PROJECT_SOURCE_DIR}/Vendor/imgui/backends/imgui_impl_wgpu.cpp")

message(${IMGUI_SRC_FILES})
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/LiaCore/Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/LiaCore/Source/*.h")

list(APPEND SRC_FILES ${HEADER_FILES})
list(APPEND SRC_FILES ${IMGUI_SRC_FILES})

add_executable(LiaCore ${SRC_FILES})

target_include_directories(LiaCore PUBLIC 
	"${PROJECT_SOURCE_DIR}/Vendor/glfw/include/"
	"${PROJECT_SOURCE_DIR}/Vendor/spdlog/include/"
	"${PROJECT_SOURCE_DIR}/Vendor/glm/"
	"${PROJECT_SOURCE_DIR}/Vendor/Dawn/Include/"
	"${PROJECT_SOURCE_DIR}/Vendor/imgui/"
	"${PROJECT_SOURCE_DIR}/LiaCore/Source/"
)



message("$ENV{VULKAN_SDK}/Include/")

target_precompile_headers(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/LiaCore/Source/Core.h")

#target_link_libraries(LiaCore "vulkan")

target_link_directories(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/Vendor/glfw/src")
target_link_libraries(LiaCore "glfw")

target_link_directories(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/Vendor/spdlog/src")
target_link_libraries(LiaCore "spdlog")

target_link_directories(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/Vendor/Dawn")

target_link_directories(LiaCore PUBLIC "${PROJECT_SOURCE_DIR}/Vendor/Dawn/${LIA_PLATFORM}/${CMAKE_BUILD_TYPE}")
message("${PROJECT_SOURCE_DIR}/Vendor/Dawn/${LIA_PLATFORM}/${CMAKE_BUILD_TYPE}")
target_link_libraries(LiaCore "dawn_proc")
target_link_libraries(LiaCore "dawn_native")
target_link_libraries(LiaCore "dawn_platform")
target_link_libraries(LiaCore "dawncpp")

message(${CMAKE_BUILD_TYPE})




include("${PROJECT_SOURCE_DIR}/LiaCore/ShaderCompile.cmake")
include("${PROJECT_SOURCE_DIR}/LiaCore/CopySharedLib.cmake")
CompileShaders()


#Copies all depending SHARED LIBS to the executable directory
CopySharedLib("dawn_proc")
CopySharedLib("dawn_native")
CopySharedLib("dawn_platform")

