#!/bin/bash
export LD_LIBRARY_PATH=../src/:$LD_LIBRARY_PATH
echo "\n*********************FILE tests**************************\n"
./safefile
echo "\n*********************FMT TESTS**************************\n"
./safefmt
echo "\n*********************IO TESTS**************************\n"
./safeio
echo "\n*********************STR TESTS**************************\N"
./safestr
echo "\n*********************Time TESTS**************************\n"
./safetime