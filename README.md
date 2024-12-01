# seq/par quick sort

Comparison of sequenntal and parallel quick sort using OpenCilk for parallelization.

## structure

`src` contains sequental and parallel implementation of quick sort.

`test` contains basic tests for both implementations.

`bench` contains simple benchmarking of two implementations.

## build-and-run

You can build and run with `make`. You may need to modify `CILKINSTALLATION` variable in `Makefile` to make it work correctly.

```sh
# build test and bench binaries
make all 

# build only test binary
make build-test

# build only bench binary
make build-bench

# build and run tests
make run-test

#build and run bench
make run-bench
```

## results of benchmarking

```
Run #1
	sequental: 8078ms
	parallel: 2594ms
	acceleration: 3.1141094834232845

Run #2
	sequental: 8023ms
	parallel: 2553ms
	acceleration: 3.1425773599686644

Run #3
	sequental: 8126ms
	parallel: 2683ms
	acceleration: 3.028699217294074

Run #4
	sequental: 8078ms
	parallel: 2869ms
	acceleration: 2.815615196932729

Run #5
	sequental: 8190ms
	parallel: 3244ms
	acceleration: 2.524660912453761

sequental avg time: 8099ms
parallel avg time: 2788ms
parallel 2.9043247507709964 times faster than sequental⏎
```
