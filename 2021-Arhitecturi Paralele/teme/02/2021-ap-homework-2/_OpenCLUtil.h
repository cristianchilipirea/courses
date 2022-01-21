
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

void handleError(cl_int returnValue, int lineNumber, char *fileName);
cl_device_id initOpenCL(cl_context *context, cl_command_queue *commandQueue);
cl_kernel getAndCompileKernel(char *fileName, char *kernelName, cl_context context, cl_device_id deviceid);