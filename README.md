# Project: Parallel Bucketsort via OpenMP
Members: 
6488007 Poramee Apiradeewajeese, 
6488060 Pawita Pongpaew, 
6488098 Chanayacha Suriyasoonthorn

# Bucket Sort with OpenMP

This program demonstrates the use of OpenMP to perform parallel bucket sort. It includes both sequential and parallel implementations of the bucket sort algorithm.

# Prerequisites

- **GCC**: Ensure that you have the GCC compiler installed on your system.

# Compilation

1. Login to PuTTY and WinSCP.

2. Add the `bucket_openMP.c` file to the WinSCP directory.

3. Compile the code using the following command:

    ```bash
    gcc -fopenmp -o bucket_openMP bucket_openMP.c
    ```

# Running the Program

After compiling the code, you can run the program using the following command:

```bash
./bucket_openMP
```

By default, the code is set to sort an array of size 10,000 using 4 threads. You can modify the `arraySize` and `numThreads` variables in the `main` function of the code to change the size of the array and the number of threads used for sorting.

EXAMPLE:

For example, if you want to sort an array of 100,000 elements using 8 threads, you would set:

```c
int arraySize = 100000;
int numThreads = 8;
```

# Output

The program will output the sorted array using parallel bucket sort and the time it took for the sorting operation. If you want to see the sorted array using sequential bucket sort, you can uncomment the relevant lines in the code.

# Important Notes

- The random numbers generated for the 'arr' array should be within a reasonable range to avoid memory allocation issues.
  
- The program generates random values for the array elements, and these values may change each time you run the program.

- Be aware that sorting large arrays with a high number of threads may require more memory and can impact system performance.

- Ensure that you have OpenMP installed and configured properly on your system to run the parallel version of the code.

- You can customize the array size and the number of threads to suit your specific use case.

# License

This code is provided under the MIT License. You are free to modify and distribute it as needed. Refer to the `LICENSE` file for more details.

Please feel free to reach out if you have any questions or encounter issues.

```
You can save the above text into a file named `readme.txt` in the same directory as your code. This readme provides instructions for compiling and running your program, along with important notes and a license statement.
