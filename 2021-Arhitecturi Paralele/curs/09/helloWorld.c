#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "_OpenCLUtil.h"

#define DATA_SIZE (1024)

int main(int argc, char **argv)
{
	// Init data
	unsigned int count = DATA_SIZE;
	float data[DATA_SIZE];
	for (int i = 0; i < count; i++)
		data[i] = rand() / (float)RAND_MAX;

	// Init OpenCL (gets platform, device, context, commandQueue, program, kernel)
	cl_context context;
	cl_command_queue commandQueue;
	cl_device_id deviceid = initOpenCL(&context, &commandQueue);
	cl_kernel kernel = getAndCompileKernel("helloWorld.cl", "square", context, deviceid);

	// Get the maximum work group size for executing the kernel on the device
	size_t max_work_group_size;
	cl_uint ret = clGetKernelWorkGroupInfo(kernel, deviceid, CL_KERNEL_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Execute kernel
	size_t work_group_size = max_work_group_size;
	size_t total_work_size = work_group_size * 2;
	printf("Total work size is %i and work group size is %i. ", (int)total_work_size, (int)work_group_size);
	printf("Total work size needs to be divisible by work group size.\n");
	ret = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &total_work_size, &work_group_size, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Wait for the command commands to get serviced before reading back results
	clFinish(commandQueue);

	clReleaseKernel(kernel);
	clReleaseCommandQueue(commandQueue);
	clReleaseContext(context);
	return 0;
}