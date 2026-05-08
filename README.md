# GoJo
Declarative language for parallel and distributed programs

Build GoJo package creates package directory with built dependencies parser, runtime, include files and run script:
```
./build_gojo_package.sh
```

Using GoJo:
* Set environment variable `GOJO_PATH` to package directory
* (optionally )Add `GOJO_PATH/gojo` to `PATH`
* C++ compiler with C++20 support should be installed in system with GoJo compiler. Now `clang++` and `g++` are supported.
* `gojo <input file> <output file>`, e.g. `gojo atomic_counter.gojo atomic_counter` cretes executable `atomic_counter`
* While working script creates and then remove temporary cpp file `tmp/<output_file>.cpp`. To not clear it use `--tmp` as the last argument
