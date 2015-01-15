#!/bin/bash

cd ../ftrl

echo 编译文件
g++ ftrl.cpp -O3

echo 跑CTR
./a.out -train ../data/adult/train.csv.hash -test ../data/adult/test.csv.hash -out ../data/out.csv -l2 1000 -iter 1 -l1 0 -alhpa 1

echo 测AUC
cd ../script
./auc.py
