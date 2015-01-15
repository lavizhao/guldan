#!/bin/bash

cd ../ftrl

echo 编译文件
g++ ftrl.cpp -O3

echo 跑CTR
./a.out -train ../data/ida/train.csv -test ../data/ida/test.csv -out ../data/out.csv -l2 10000 -iter 2

echo 测AUC
cd ../script
./auc.py
