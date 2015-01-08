#!/usr/bin/python3

'''
目的: ida数据集, 随便从网上下的

========
ida数据集说明:

1. 数据都直接std转换了, 所以我都不用做了
2. 二分类, 标签-1,1
3. 没有缺值
4. 训练样本7399, 正负比近似1:1
5. 属于比较完美的训练样本

========

1. 分割数据, 训练5000,测试2300
2. 没有类别属性, 因而没有考虑哈希的问题

'''

import csv
from util import *

def main():
    """
    """

    data_dir = "../data/ida/ringnorm_data.csv"
    f = open(data_dir)

    reader = csv.reader(f)

    #正负样本
    pos = []
    neg = []

    for line in reader:
        if line[0] == '1.0':
            pos.append(line)
        else:
            neg.append(line)

    print("pos %s neg %s"%(len(pos),len(neg)))

    #分别是训练测试的样本
    train_pos = []
    test_pos = []
    train_neg = []
    test_neg = []

    for ele in pos:
        kt = keep_train(5000,2399)
        if kt == True:
            train_pos.append(ele)
        else:
            test_pos.append(ele)

    for ele in neg:
        kt = keep_train(5000,2399)
        if kt == True:
            train_neg.append(ele)
        else:
            test_neg.append(ele)

    print("train===>pos:%s neg:%s ||| test===>pos:%s neg:%s "%(len(train_pos),len(test_pos),len(train_neg),len(test_neg)))
    print("new train:%s new test:%s"%(len(train_pos)+len(train_neg), len(test_neg)+len(test_neg)))

    #然后是写
    train_dir = "../data/ida/train.csv"
    test_dir = "../data/ida/test.csv"

    t = open(train_dir,"w")
    writer = csv.writer(t)

    idpos,idneg = 0,0
    while idpos < len(train_pos) and idneg < len(train_neg):
        kt = keep_train(1,1)
        if kt == True:
            writer.writerow(libsvm_format(train_pos[idpos]))
            idpos += 1
        else:
            writer.writerow(libsvm_format(train_neg[idneg]))
            idneg += 1

    t = open(test_dir,"w")
    writer = csv.writer(t)

    idpos,idneg = 0,0
    while idpos < len(test_pos) and idneg < len(test_neg):
        kt = keep_train(1,1)
        if kt == True:
            writer.writerow(libsvm_format(test_pos[idpos]))
            idpos += 1
        else:
            writer.writerow(libsvm_format(test_neg[idneg]))
            idneg += 1

    
if __name__ == '__main__':
    main()


