#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define DATA_SIZE (81920)

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
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *fcontent = malloc(size);
	fread(fcontent, 1, size, fp);
	fclose(fp);
	printf("%s", fcontent);
	return fcontent;
}

int main(int argc, char **argv)
{
	int err;  // error code returned from api calls

	float data[DATA_SIZE];     // original data set given to device
	float results[DATA_SIZE];  // results returned from device
	unsigned int correct;      // number of correct results returned

	size_t global;  // global domain size for our calculation
	size_t local;   // local domain size for our calculation

	cl_device_id device_id;     // compute device id
	cl_context context;         // compute context
	cl_command_queue commands;  // compute command queue
	cl_program program;         // compute program
	cl_kernel kernel;           // compute kernel

	cl_mem input;   // device memory used for the input array
	cl_mem output;  // device memory used for the output array

	// Fill our data set with random float values
	int i = 0;
	unsigned int count = DATA_SIZE;
	for (i = 0; i < count; i++)
		data[i] = rand() / (float)RAND_MAX;

	// Connect to a compute device
	cl_platform_id platform_id[10];
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(10, platform_id, &ret_num_platforms);
	printf("There are %i platforms\n", ret_num_platforms);
	if (ret != CL_SUCCESS) {
		return EXIT_FAILURE;
	}

	char platformName[1000];
	size_t param_value_size_ret;
	clGetPlatformInfo(platform_id[1], CL_PLATFORM_NAME, 1000, platformName, &param_value_size_ret);
	printf("Platform name is %s\n", platformName);
	ret = clGetDeviceIDs(platform_id[1], CL_DEVICE_TYPE_ALL, 1, &device_id, &ret_num_devices);
	printf("There are %i devices\n", ret_num_devices);
	if (ret != CL_SUCCESS) {
		return EXIT_FAILURE;
	}
	char deviceName[1000];
	clGetDeviceInfo(device_id, CL_DEVICE_NAME, 1000, deviceName, &param_value_size_ret);
	printf("Device name is %s\n", deviceName);

	// Create a compute context
	context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
	if (!context) {
		printf("Error: Failed to create a compute context!\n");
		return EXIT_FAILURE;
	}

	// Create a command commands
	commands = clCreateCommandQueue(context, device_id, 0, &err);
	if (!commands) {
		printf("Error: Failed to create a command commands!\n");
		return EXIT_FAILURE;
	}

	// Create the compute program
	char *KernelSource = readKernel("kernel.cl");
	program = clCreateProgramWithSource(context, 1, (const char **)&KernelSource, NULL, &err);
	if (!program) {
		printf("Error: Failed to create compute program!\n");
		return EXIT_FAILURE;
	}

	// Build the program executable
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS) {
		size_t len;
		char buffer[2048];

		printf("Error: Failed to build program executable!\n");
		printf(opencl_errstr(err));
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
		exit(1);
	}

	// Create the compute kernel in the program we wish to run
	kernel = clCreateKernel(program, "square", &err);
	if (!kernel || err != CL_SUCCESS) {
		printf("Error: Failed to create compute kernel!\n");
		exit(1);
	}

	// Create the input and output arrays in device memory for our calculation
	input = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * count, NULL, NULL);
	output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * count, NULL, NULL);
	if (!input || !output) {
		printf("Error: Failed to allocate device memory!\n");
		exit(1);
	}

	// Write our data set into the input array in device memory
	err = clEnqueueWriteBuffer(commands, input, CL_TRUE, 0, sizeof(float) * count, data, 0, NULL, NULL);
	if (err != CL_SUCCESS) {
		printf("Error: Failed to write to source array!\n");
		exit(1);
	}

	// Set the arguments to our compute kernel
	err = 0;
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &output);
	err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);
	if (err != CL_SUCCESS) {
		printf("Error: Failed to set kernel arguments! %d\n", err);
		exit(1);
	}

	// Get the maximum work group size for executing the kernel on the device
	err = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);
	if (err != CL_SUCCESS) {
		printf("Error: Failed to retrieve kernel work group info! %d\n", err);
		exit(1);
	}

	// Execute the kernel over the entire range of our 1d input data set
	// using the maximum number of work group items for this device
	global = count;
	printf("Work Group Size %i\n", local);
	err = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, &global, &local, 0, NULL, NULL);
	if (err) {
		printf(opencl_errstr(err));
		printf("Error: Failed to execute kernel!\n");
		return EXIT_FAILURE;
	}

	// Wait for the command commands to get serviced before reading back results
	clFinish(commands);

	// Read back the results from the device to verify the output
	err = clEnqueueReadBuffer(commands, output, CL_TRUE, 0, sizeof(float) * count, results, 0, NULL, NULL);
	if (err != CL_SUCCESS) {
		printf("Error: Failed to read output array! %d\n", err);
		exit(1);
	}

	// Validate our results
	correct = 0;
	for (i = 0; i < count; i++) {
		if (results[i] == data[i] * data[i])
			correct++;
	}

	// Print a brief summary detailing the results
	printf("Computed '%d/%d' correct values!\n", correct, count);

	// Shutdown and cleanup
	clReleaseMemObject(input);
	clReleaseMemObject(output);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(commands);
	clReleaseContext(context);

	return 0;
}