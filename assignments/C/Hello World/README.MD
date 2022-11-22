# Hello World

Hello World is a C project that prints Hello World in the terminal.r

## How to build

See `Makefile` for the build scripts.

To build the command line example, simply run `make` or `make compile`
at the command line in the current directory.

By default, this will generate an executable called whatever `NAME`
is bound to in `Makefile` (by default, `project`).
To then run the program with Valgrind (recommended!), run

```
valgrind ./hello_world
```

in the project directory.

To compile and run the test suite, run `make test`.

## Running the example projects

The first example is `command_line_args.c`, which can be built by `make compile`,
or `make`.

As before, run 

```
valgrind ./hello_world
```

to run the program.