#pragma once
void DeviceLogCback(WGPULoggingType type, const char* msg, void* userData)
{
	LOG_WARN(msg);
}
void DeviceErrorCback(WGPUErrorType type, const char* msg, void* userData)
{
	LOG_WARN(msg);
}