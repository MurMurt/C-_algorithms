#!/bin/bash
date
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -v  --log-file="valgrind-test.out" $1
date >> valgrind-test.out