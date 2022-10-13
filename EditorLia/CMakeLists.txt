set (CMAKE_CXX_STANDARD 20)
message(${glslangValidator})

file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/EditorLia/Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/EditorLia/Source/*.h")

list(APPEND SRC_FILES ${HEADER_FILES})
list(APPEND SRC_FILES ${IMGUI_SRC_FILES})

#add_library(LiaCore SHARED ${SRC_FILES})

add_executable(EditorLia ${SRC_FILES})

target_include_directories(EditorLia PUBLIC 
	"${PROJECT_SOURCE_DIR}/Vendor/glm/"
	"${PROJECT_SOURCE_DIR}/Vendor/imgui/"
	"${PROJECT_SOURCE_DIR}/LiaCore/Source/"
	"${PROJECT_SOURCE_DIR}/EditorLia/Source/"
)






target_link_libraries(EditorLia "LiaCore")


include("${PROJECT_SOURCE_DIR}/CopySharedLib.cmake")
#Copies all depending SHARED LIBS to the executable directory
CopySharedLibDawn("dawn_proc" EditorLia)
CopySharedLibDawn("dawn_native" EditorLia)
CopySharedLibDawn("dawn_platform" EditorLia)
