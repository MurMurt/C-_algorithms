#!/bin/bash
echo "Test staeted: "
valgrind --tool=memcheck --leak-check=full -v  --log-file="valgrind-test.out" ./cmake-build-debug/$1
echo
echo "Results at valgrind-test.out"
