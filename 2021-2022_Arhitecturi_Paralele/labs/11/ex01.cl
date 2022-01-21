__kernel void vector_addition(__global int* input, __global int* buffer, int len)
{
	int id = get_global_id(0);
    int global_size = get_global_size(0);
    int local_val = 999;
    int left=0;
	int early_exit=0;


	//BUILD PIPELINE HERE
	if(id==0)
		printf("%2i ",i);
	printf("(%3i %2i)->%3i->", local_val, !early_exit, buffer[id + 1]);
	if(id==global_size-1)
		printf("\n");
	//BUILD PIPELINE HERE
}
