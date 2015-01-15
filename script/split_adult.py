#!/usr/bin/python3
import csv
from util import *

def main():
    """
    """
    f = open("../data/adult/adult.data")
    reader = csv.reader(f)

    t1 = open("../data/adult/train.csv","w")
    t2 = open("../data/adult/test.csv","w")

    w1 = csv.writer(t1)
    w2 = csv.writer(t2)

    for line in reader:
        if len(line) < 1:
            continue
        label = line[-1].strip()
        if label == "<=50K":
            label = '0'
        else:
            label = '1'
            
        line = line[:-1]
        ls = csv_format(line,label)
        if keep_train(2,1):
            w1.writerow(ls)
        else:
            w2.writerow(ls)
        

if __name__ == '__main__':
    main()
