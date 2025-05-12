#!/bin/bash

set -e

echo ">> Cleaning and building everything..."
make clean
make libcpp_static libcpp_shared libc_static libc_shared

echo
echo ">> Testing C source linking to C++ libs:"
echo "--- Static linking:"
make prog_static && ./prog_static
echo

echo "--- Dynamic linking (implicit):"
make prog_dyn && LD_LIBRARY_PATH=. ./prog_dyn
echo

echo "--- Dynamic linking (explicit):"
make prog_explicit && ./prog_explicit
echo

echo ">> Testing C++ source linking to C libs:"
echo "--- Static linking:"
make cpp_static && ./cpp_static
echo

echo "--- Dynamic linking (implicit):"
make cpp_dyn && LD_LIBRARY_PATH=. ./cpp_dyn
echo

echo "--- Dynamic linking (explicit):"
make cpp_explicit && ./cpp_explicit
echo

echo ">> All tests ran successfully."
