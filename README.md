# Toy compiler

The goal of this compiler is to learn the basics of compilation,
intermediate representation and ELF file format.

## Layout

This project aims to be structured following the pitchfork layout (plf).

## Makefile targets

| Target        | Description                                               |
| ------------- | --------------------------------------------------------- |
| `gcc-compile` | Compile a target using `gcc` with no optimization in ASM. |
| `format`      | Format project files using clang-format.                  |
| `valgrind`    | Memory check                                              |
| `build`       | Build the compiler                                        |