cmake_minimum_required(VERSION 3.22.0)

project(Lia)

if(WIN32)
	set(LIA_PLATFORM "Win32")
elseif(UNIX)
	set(LIA_PLATFORM "Unix")
endif()

add_subdirectory("LiaCore")

add_subdirectory("EditorLia")

add_subdirectory("Vendor/spdlog")

add_subdirectory("Vendor/glfw")

