//__kernel void square(__global float* input, __global float* output, const unsigned int count)
__kernel void square()
{
	int I = get_global_id(0);
	int i = get_local_id(0);
	int wg_size = get_local_size(0);
	if(i%128==0)
		printf("Hello work item %4i in work group %2i, of size %4i and %6i global id \n", i, I/wg_size, wg_size, I);
}
