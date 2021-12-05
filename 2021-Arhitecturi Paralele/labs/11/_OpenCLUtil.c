#include "_OpenCLUtil.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SELECTED_PLATFORM -1
#define SELECTED_DEVICE -1

#define CaseReturnString(x) \
	case x:                 \
		return #x;

// clang-format off
char *opencl_errstr(cl_int err)
{
	switch (err)
	{
		CaseReturnString(CL_SUCCESS)
		CaseReturnString(CL_DEVICE_NOT_FOUND)
		CaseReturnString(CL_DEVICE_NOT_AVAILABLE)
		CaseReturnString(CL_COMPILER_NOT_AVAILABLE)
		CaseReturnString(CL_MEM_OBJECT_ALLOCATION_FAILURE)
		CaseReturnString(CL_OUT_OF_RESOURCES)
		CaseReturnString(CL_OUT_OF_HOST_MEMORY)
		CaseReturnString(CL_PROFILING_INFO_NOT_AVAILABLE)
		CaseReturnString(CL_MEM_COPY_OVERLAP)
		CaseReturnString(CL_IMAGE_FORMAT_MISMATCH)
		CaseReturnString(CL_IMAGE_FORMAT_NOT_SUPPORTED)
		CaseReturnString(CL_BUILD_PROGRAM_FAILURE)
		CaseReturnString(CL_MAP_FAILURE)
		CaseReturnString(CL_MISALIGNED_SUB_BUFFER_OFFSET)
		CaseReturnString(CL_COMPILE_PROGRAM_FAILURE)
		CaseReturnString(CL_LINKER_NOT_AVAILABLE)
		CaseReturnString(CL_LINK_PROGRAM_FAILURE)
		CaseReturnString(CL_DEVICE_PARTITION_FAILED)
		CaseReturnString(CL_KERNEL_ARG_INFO_NOT_AVAILABLE)
		CaseReturnString(CL_INVALID_VALUE)
		CaseReturnString(CL_INVALID_DEVICE_TYPE)
		CaseReturnString(CL_INVALID_PLATFORM)
		CaseReturnString(CL_INVALID_DEVICE)
		CaseReturnString(CL_INVALID_CONTEXT)
		CaseReturnString(CL_INVALID_QUEUE_PROPERTIES)
		CaseReturnString(CL_INVALID_COMMAND_QUEUE)
		CaseReturnString(CL_INVALID_HOST_PTR)
		CaseReturnString(CL_INVALID_MEM_OBJECT)
		CaseReturnString(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
		CaseReturnString(CL_INVALID_IMAGE_SIZE)
		CaseReturnString(CL_INVALID_SAMPLER)
		CaseReturnString(CL_INVALID_BINARY)
		CaseReturnString(CL_INVALID_BUILD_OPTIONS)
		CaseReturnString(CL_INVALID_PROGRAM)
		CaseReturnString(CL_INVALID_PROGRAM_EXECUTABLE)
		CaseReturnString(CL_INVALID_KERNEL_NAME)
		CaseReturnString(CL_INVALID_KERNEL_DEFINITION)
		CaseReturnString(CL_INVALID_KERNEL)
		CaseReturnString(CL_INVALID_ARG_INDEX)
		CaseReturnString(CL_INVALID_ARG_VALUE)
		CaseReturnString(CL_INVALID_ARG_SIZE)
		CaseReturnString(CL_INVALID_KERNEL_ARGS)
		CaseReturnString(CL_INVALID_WORK_DIMENSION)
		CaseReturnString(CL_INVALID_WORK_GROUP_SIZE)
		CaseReturnString(CL_INVALID_WORK_ITEM_SIZE)
		CaseReturnString(CL_INVALID_GLOBAL_OFFSET)
		CaseReturnString(CL_INVALID_EVENT_WAIT_LIST)
		CaseReturnString(CL_INVALID_EVENT)
		CaseReturnString(CL_INVALID_OPERATION)
		CaseReturnString(CL_INVALID_GL_OBJECT)
		CaseReturnString(CL_INVALID_BUFFER_SIZE)
		CaseReturnString(CL_INVALID_MIP_LEVEL)
		CaseReturnString(CL_INVALID_GLOBAL_WORK_SIZE)
		CaseReturnString(CL_INVALID_PROPERTY)
		CaseReturnString(CL_INVALID_IMAGE_DESCRIPTOR)
		CaseReturnString(CL_INVALID_COMPILER_OPTIONS)
		CaseReturnString(CL_INVALID_LINKER_OPTIONS)
		CaseReturnString(CL_INVALID_DEVICE_PARTITION_COUNT) 
		default : return "Unknown OpenCL error code";
	}
}
// clang-format on

char *readKernel(char *filename)
{
	FILE *fp = fopen(filename, "rt");
	if (fp == NULL) {
		printf("File %s with OpenCL Kernels  not found\n", filename);
		exit(errno);
	}
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	printf("DEBUG: File size of %s is %i\n", filename, size);
	fseek(fp, 0, SEEK_SET);
	char *fcontent = malloc(size + 1);
	fread(fcontent, 1, size, fp);
	fcontent[size] = '\0';
	fclose(fp);
	return fcontent;
}

void handleError(cl_int returnValue, int lineNumber, char *fileName)
{
	if (returnValue == CL_SUCCESS)
		return;
	printf("ERROR: %s from line %i in file %s", opencl_errstr(returnValue), lineNumber, fileName);
	exit(returnValue);
}

cl_device_id initOpenCL(cl_context *context, cl_command_queue *commandQueue)
{
	cl_uint num_platforms;
	cl_int ret;
	ret = clGetPlatformIDs(0, NULL, &num_platforms);
	handleError(ret, __LINE__, __FILE__);
	printf("DEBUG: There are %i platforms\n", num_platforms);

	cl_platform_id *platform_ids = malloc(sizeof(cl_platform_id) * num_platforms);
	ret = clGetPlatformIDs(num_platforms, platform_ids, &num_platforms);
	handleError(ret, __LINE__, __FILE__);

	int selectedPlatform = 0;

	for (int i = 0; i < num_platforms; i++) {
		size_t param_value_size;
		ret = clGetPlatformInfo(platform_ids[i], CL_PLATFORM_NAME, 0, NULL, &param_value_size);
		handleError(ret, __LINE__, __FILE__);
		char *platformName = malloc(sizeof(char) * param_value_size);
		ret = clGetPlatformInfo(platform_ids[i], CL_PLATFORM_NAME, param_value_size, platformName, &param_value_size);
		handleError(ret, __LINE__, __FILE__);

		if (strncmp(platformName, "NVIDIA", 6) == 0)
			selectedPlatform = i;

		cl_uint num_devices;
		ret = clGetDeviceIDs(platform_ids[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
		handleError(ret, __LINE__, __FILE__);
		printf("DEBUG: Platform %i is %s and has %i devices\n", i, platformName, num_devices);

		cl_device_id *device_ids = malloc(sizeof(cl_device_id) * num_devices);
		ret = clGetDeviceIDs(platform_ids[i], CL_DEVICE_TYPE_ALL, num_devices, device_ids, &num_devices);
		handleError(ret, __LINE__, __FILE__);
		for (int j = 0; j < num_devices; j++) {
			ret = clGetDeviceInfo(device_ids[j], CL_DEVICE_NAME, 0, NULL, &param_value_size);
			handleError(ret, __LINE__, __FILE__);

			char *deviceName = malloc(sizeof(char) * param_value_size);
			ret = clGetDeviceInfo(device_ids[j], CL_DEVICE_NAME, param_value_size, deviceName, &param_value_size);
			handleError(ret, __LINE__, __FILE__);
			printf("DEBUG:   Device %i is %s\n", j, deviceName);
		}
	}

	printf("DEBUG: We aim to select the best GPU available (for most cases this is NVIDIA).\n");
	printf("DEBUG: If this is not the best platform/device for your system please do a manual section.\n");
	printf("DEBUG: In File _OpenCLUtil.c modify the defines at the top to match the device you want.\n");

	selectedPlatform = SELECTED_PLATFORM >= 0 ? SELECTED_PLATFORM : selectedPlatform;
	int selectedDevice = SELECTED_DEVICE >= 0 ? SELECTED_DEVICE : 0;

	size_t param_value_size;
	ret = clGetPlatformInfo(platform_ids[selectedPlatform], CL_PLATFORM_NAME, 0, NULL, &param_value_size);
	handleError(ret, __LINE__, __FILE__);
	char *platformName = malloc(sizeof(char) * param_value_size);
	ret = clGetPlatformInfo(platform_ids[selectedPlatform], CL_PLATFORM_NAME, param_value_size, platformName, &param_value_size);
	handleError(ret, __LINE__, __FILE__);

	cl_uint num_devices;
	ret = clGetDeviceIDs(platform_ids[selectedPlatform], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
	handleError(ret, __LINE__, __FILE__);

	cl_device_id *device_ids = malloc(sizeof(cl_device_id) * num_devices);
	ret = clGetDeviceIDs(platform_ids[selectedPlatform], CL_DEVICE_TYPE_ALL, num_devices, device_ids, &num_devices);
	handleError(ret, __LINE__, __FILE__);

	ret = clGetDeviceInfo(device_ids[selectedDevice], CL_DEVICE_NAME, 0, NULL, &param_value_size);
	handleError(ret, __LINE__, __FILE__);

	char *deviceName = malloc(sizeof(char) * param_value_size);
	ret = clGetDeviceInfo(device_ids[selectedDevice], CL_DEVICE_NAME, param_value_size, deviceName, &param_value_size);
	handleError(ret, __LINE__, __FILE__);
	printf("DEBUG: We selected platform %i %s and device %i %s\n", selectedPlatform, platformName, selectedDevice, deviceName);

	*context = clCreateContext(0, 1, &device_ids[selectedDevice], NULL, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);

	*commandQueue = clCreateCommandQueue(*context, device_ids[selectedDevice], 0, &ret);
	handleError(ret, __LINE__, __FILE__);
	return device_ids[selectedDevice];
}

cl_kernel getAndCompileKernel(char *fileName, char *kernelName, cl_context context, cl_device_id deviceid)
{
	cl_int ret;
	char *KernelSource = readKernel(fileName);
	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&KernelSource, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);

	ret = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (ret != CL_SUCCESS) {
		size_t len;
		char buffer[20480];

		printf("ERROR: Failed to build program executable %s from line %i in file %s", opencl_errstr(ret), __LINE__, __FILE__);
		clGetProgramBuildInfo(program, deviceid, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%i\n", (int)len);
		for (int i = 0; i < len; i++)  // we print it char by chat because we had cases when the first few chars were \0
			printf("%c", buffer[i]);
		exit(1);
	}

	// Create the compute kernel in the program we wish to run
	cl_kernel kernel = clCreateKernel(program, kernelName, &ret);
	handleError(ret, __LINE__, __FILE__);
	return kernel;
}