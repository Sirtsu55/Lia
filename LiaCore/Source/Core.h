// Cubica.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <unordered_set>
#include <memory>
#include <sstream>
#include <filesystem>


#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define GLFW_INCLUDE_VULKAN

#ifdef WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#elif X11
#define GLFW_EXPOSE_NATIVE_X11
#elif WAYLAND
#define GLFW_EXPOSE_NATIVE_WAYLAND
#endif //Detect Platform

//GLFW
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
//IMGUI
#include <imgui.h>
#include <backends/imgui_impl_wgpu.h>
#include <backends/imgui_impl_glfw.h>

//#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
//#include <vulkan/vulkan.hpp>
#include <webgpu/webgpu_cpp.h>
#include <dawn/native/DawnNative.h>
#include <dawn/dawn_proc.h>



//---------------------------------------
//Casting
//---------------------------------------

#define ReCast reinterpret_cast

//---------------------------------------
//Shared Pointers
//---------------------------------------

template<typename T>
using Sptr = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Sptr<T> CreateSptr(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}


//---------------------------------------
//Unique Pointers
//---------------------------------------

template<typename T>
using Uptr = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Uptr<T> CreateUptr(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}


//Returns a Sptr dereferenced, BE CAREFUL WITH THE DEREFERENCED VALUE
template<typename T1, typename T2>
constexpr T1& GetSmartPtrAsRef(const T2&  sptr) { return *(ReCast<T1*>(sptr.get())); }




//---------------------------------------
//Logging
//---------------------------------------

#define LOG 1


#if LOG
#include "Utils/Logger.h"

//CORE LOGGER
#define LOG_CRITICAL(...) ::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define LOG_ERROR(...)    ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_WARN(...)     ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_INFO(...)     ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_TRACE(...)    ::Log::GetCoreLogger()->trace(__VA_ARGS__)



#endif // LOG


#define PROFILING 1

#if PROFILING
#include "Utils/Timers.h"


#define PROFILE(Name) ScopedTimer Timer##__LINE__(Name)
#define PROFILE_NO_LOG(Name) ScopedTimer Timer##__LINE__(Name, false)

#define PROFILE_FUNCTION() ScopedTimer Timer##__LINE__(__FUNCTION__)
#define PROFILE_FUNCTION_NO_LOG() ScopedTimer Timer##__LINE__(__FUNCTION__, false)

#define PROFILE_FUNCTION_SIG() ScopedTimer Timer##__LINE__(__FUNCSIG__)
#define PROFILE_FUNCTION_SIG_NO_LOG() ScopedTimer Timer##__LINE__(__FUNCSIG__, false)

#else

#define PROFILE(Name) 
#define PROFILE_NO_LOG(Name) 

#define PROFILE_FUNCTION() 
#define PROFILE_FUNCTION_NO_LOG() 

#define PROFILE_FUNCTION_SIG()
#define PROFILE_FUNCTION_SIG_NO_LOG()
#endif // PROFILING













// TODO: Reference additional headers your program requires here.
