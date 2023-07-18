// This function represents an OpenCL kernel. The kernel will be called from
// the host application using the xcl_run_kernels call. The pointers in kernel
// parameters with the global keyword represent cl_mem objects on the FPGA
// DDR memory.
//
// Define the buffer size for vector processing (batch size)
#define BUFFER_SIZE 256

// OpenCL kernel for vector addition with double precision (doubles)
kernel __attribute__((reqd_work_group_size(1, 1, 1)))
void vector_add(global double* c,
                global const double* a,
                global const double* b,
                const int n_elements)
{
    // Temporary arrays to store a batch of elements from arrays 'a' and 'b'
    double arrayA[BUFFER_SIZE];
    double arrayB[BUFFER_SIZE];

    // Loop through the input arrays 'a' and 'b', processing data in batches
    for (int i = 0; i < n_elements; i += BUFFER_SIZE)
    {
        // Determine the actual size of the batch (last batch might have fewer elements)
        int size = BUFFER_SIZE;
        if (i + size > n_elements) size = n_elements - i;

        // Read a batch of 'size' elements from arrays 'a' and 'b' into temporary arrays
        // This is necessary because reading directly from global memory can be inefficient.
        // By reading data into local memory first, we can access it with higher bandwidth.
        readA: for (int j = 0; j < size; j++) arrayA[j] = a[i + j];
        readB: for (int j = 0; j < size; j++) arrayB[j] = b[i + j];

        // Perform vector addition on the batch and write the results to the output array 'c'
        // This loop calculates the sum of corresponding elements in 'arrayA' and 'arrayB'
        vadd_writeC: for (int j = 0; j < size; j++) c[i + j] = arrayA[j] + arrayB[j];
    }
}
