#!/bin/bash
echo "Test staeted at: "
date
valgrind --tool=memcheck --leak-check=full -v  --log-file="valgrind-test.out" $1
