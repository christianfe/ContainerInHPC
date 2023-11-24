# HPLinpack

This repository contains the Linpack benchmark obtained from [netlib](http://www.netlib.org/benchmark/linpackc.new).

## To run the benchmark on Docker

-   `docker build --tag=linpack .`
-   `docker run -it --rm linpack`

## To run the benchmark with gcc

`gcc -o linpack -O3 -march=native -lm linpack.c`

## Example

Here are some sample results:

```
Enter array size (q to quit) [200]:
Memory required:  315K.


LINPACK benchmark, Double precision.
Machine precision:  15 digits.
Array size 200 X 200.
Average rolled and unrolled performance:

    Reps Time(s) DGEFA   DGESL  OVERHEAD    KFLOPS
----------------------------------------------------
    1024   0.56  66.07%   1.79%  32.14%  3700771.930
    2048   1.28  74.22%   0.78%  25.00%  2929777.778
    4096   2.17  75.58%   3.23%  21.20%  3289575.049
    8192   4.94  68.83%   4.25%  26.92%  3116439.520
   16384   9.33  67.95%   4.07%  27.97%  3348317.460
   32768  18.81  67.36%   2.71%  29.93%  3414369.246

```
