#!/bin/bash

cd ../ftrl

echo 编译文件
g++ ftrl.cpp -O3

echo 跑CTR
./a.out -train ../data/adult/train.csv.hash -test ../data/adult/test.csv.hash -out ../data/out.csv -l2 10 -iter 100 -l1 1 -alhpa 1 -verbose 2

echo 测AUC
cd ../script
./auc.py
