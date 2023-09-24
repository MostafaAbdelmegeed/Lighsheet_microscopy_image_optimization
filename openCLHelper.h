#ifndef OPENCLHELPER_H
#define OPENCLHELPER_H


#include <CL/cl.h>
#include "exceptions.h"


void checkOpenCLError(cl_int errorCode, const std::string &functionName) {
    if (errorCode==CL_SUCCESS) {
        return;
    }
    std::string message;
    switch(errorCode) {
        case  -1: message = "CL_DEVICE_NOT_FOUND"; break;
        case  -2: message = "CL_DEVICE_NOT_AVAILABLE"; break;
        case  -3: message = "CL_COMPILER_NOT_AVAILABLE"; break;
        case  -4: message = "CL_MEM_OBJECT_ALLOCATION_FAILURE"; break;
        case  -5: message = "CL_OUT_OF_RESOURCES"; break;
        case  -6: message = "CL_OUT_OF_HOST_MEMORY"; break;
        case  -7: message = "CL_PROFILING_INFO_NOT_AVAILABLE"; break;
        case  -8: message = "CL_MEM_COPY_OVERLAP"; break;
        case  -9: message = "CL_IMAGE_FORMAT_MISMATCH"; break;
        case -10: message = "CL_IMAGE_FORMAT_NOT_SUPPORTED"; break;
        case -11: message = "CL_BUILD_PROGRAM_FAILURE"; break;
        case -12: message = "CL_MAP_FAILURE"; break;
        case -13: message = "CL_MISALIGNED_SUB_BUFFER_OFFSET"; break;
        case -14: message = "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST"; break;
        case -30: message = "CL_INVALID_VALUE"; break;
        case -31: message = "CL_INVALID_DEVICE_TYPE"; break;
        case -32: message = "CL_INVALID_PLATFORM"; break;
        case -33: message = "CL_INVALID_DEVICE"; break;
        case -34: message = "CL_INVALID_CONTEXT"; break;
        case -35: message = "CL_INVALID_QUEUE_PROPERTIES"; break;
        case -36: message = "CL_INVALID_COMMAND_QUEUE"; break;
        case -37: message = "CL_INVALID_HOST_PTR"; break;
        case -38: message = "CL_INVALID_MEM_OBJECT"; break;
        case -39: message = "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR"; break;
        case -40: message = "CL_INVALID_IMAGE_SIZE"; break;
        case -41: message = "CL_INVALID_SAMPLER"; break;
        case -42: message = "CL_INVALID_BINARY"; break;
        case -43: message = "CL_INVALID_BUILD_OPTIONS"; break;
        case -44: message = "CL_INVALID_PROGRAM"; break;
        case -45: message = "CL_INVALID_PROGRAM_EXECUTABLE"; break;
        case -46: message = "CL_INVALID_KERNEL_NAME"; break;
        case -47: message = "CL_INVALID_KERNEL_DEFINITION"; break;
        case -48: message = "CL_INVALID_KERNEL"; break;
        case -49: message = "CL_INVALID_ARG_INDEX"; break;
        case -50: message = "CL_INVALID_ARG_VALUE"; break;
        case -51: message = "CL_INVALID_ARG_SIZE"; break;
        case -52: message = "CL_INVALID_KERNEL_ARGS"; break;
        case -53: message = "CL_INVALID_WORK_DIMENSION"; break;
        case -54: message = "CL_INVALID_WORK_GROUP_SIZE"; break;
        case -55: message = "CL_INVALID_WORK_ITEM_SIZE"; break;
        case -56: message = "CL_INVALID_GLOBAL_OFFSET"; break;
        case -57: message = "CL_INVALID_EVENT_WAIT_LIST"; break;
        case -58: message = "CL_INVALID_EVENT"; break;
        case -59: message = "CL_INVALID_OPERATION"; break;
        case -60: message = "CL_INVALID_GL_OBJECT"; break;
        case -61: message = "CL_INVALID_BUFFER_SIZE"; break;
        case -62: message = "CL_INVALID_MIP_LEVEL"; break;
        case -63: message = "CL_INVALID_GLOBAL_WORK_SIZE"; break;
        case -64: message = "CL_INVALID_PROPERTY"; break;
        default: message = "Unknown OpenCL error";
    }
    throw OpenCLException("OpenCL error "
                                  + message + " when running " + functionName + ".");
}

std::string getPlatformInfoString(cl_platform_id platform, cl_platform_info infoIdentifier) {
    size_t size;
    clGetPlatformInfo(platform, infoIdentifier, 0, NULL, &size);
    char* info = (char*) malloc(sizeof(char)*size);
    clGetPlatformInfo(platform, infoIdentifier, size, info, NULL);
    return info;
}

std::string getDeviceInfo(cl_device_id device, cl_device_info infoIdentifier) {
    size_t size;
    clGetDeviceInfo(device, infoIdentifier, 0, NULL, &size);
    char* info = (char*) malloc(sizeof(char)*size);
    clGetDeviceInfo(device, infoIdentifier, size, info, NULL);
    return info;
}

template<typename T>
T getDeviceInfo(cl_device_id device, cl_device_info infoIdentifier) {
    cl_int ret;
    T info;
    ret = clGetDeviceInfo(device, infoIdentifier, sizeof(T), &info, NULL);
    return info;
}

void printDevicesInfo()
{
    cl_int ret;
    cl_uint platformCount;
    ret = clGetPlatformIDs(0, NULL, &platformCount);
    checkOpenCLError(ret, "clGetPlatformIDs");
    cl_platform_id* allPlatforms = (cl_platform_id*) malloc(sizeof(cl_platform_id)*platformCount);
    ret = clGetPlatformIDs(platformCount, allPlatforms, NULL);
    checkOpenCLError(ret, "clGetPlatformIDs");
    for(int i=0;i<platformCount;i++)
    {
        cl_platform_id curr_plat = allPlatforms[i];
        std::cout << "Platform " << i << "\t\t" << getPlatformInfoString(curr_plat, CL_PLATFORM_NAME) << std::endl;
        cl_uint deviceCount;
        ret = clGetDeviceIDs(curr_plat, CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        checkOpenCLError(ret, "clGetDeviceIDs");
        cl_device_id* allDevices = (cl_device_id*) malloc(sizeof(cl_device_id)*deviceCount);
        ret = clGetDeviceIDs(curr_plat, CL_DEVICE_TYPE_ALL, deviceCount, allDevices, NULL);
        checkOpenCLError(ret, "clGetDeviceIDs");
        for (int j=0;j<deviceCount;j++)
        {
            cl_device_id curr_dev = allDevices[j];
            cl_device_type type = getDeviceInfo<cl_device_type>(curr_dev, CL_DEVICE_TYPE);
            std::string deviceType = "";
            if (type&CL_DEVICE_TYPE_DEFAULT) { deviceType += "default "; }
            if (type&CL_DEVICE_TYPE_CPU) { deviceType += "cpu "; }
            if (type&CL_DEVICE_TYPE_GPU) { deviceType += "gpu "; }
            if (type&CL_DEVICE_TYPE_ACCELERATOR) { deviceType += "accelerator "; }
            std::cout << "\t" << "Device " << j << "\t\t" << deviceType << "\t" <<  getDeviceInfo<std::string>(curr_dev, CL_DEVICE_NAME) << std::endl;
        }
        free(allDevices);
    }
}









#endif // OPENCLHELPER_H
