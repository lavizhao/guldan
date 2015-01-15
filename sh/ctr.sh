#!/bin/bash

cd ../ftrl

rm a.out

echo 编译文件
g++ ftrl.cpp -O3

echo 跑CTR
./a.out -train ../../CTR/data/new_train.csv.hash -test ../../CTR/data/new_train.csv.hash -out ../data/out.csv -l2 1 -l1 0 -iter 10 -alpha 0.1 -beta 1 -verbose 200 -stop 2

echo 测AUC
cd ../script
./auc.py

