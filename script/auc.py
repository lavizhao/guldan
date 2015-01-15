#!/usr/bin/python

from sklearn import metrics
import numpy as np
from sklearn.metrics import roc_auc_score
from sklearn.metrics import log_loss
from sklearn.metrics import f1_score

def above(a,t):
    if a>t:
        return 1
    else:
        return 0

if __name__ == '__main__':
    f = open("../data/out.csv")

    label = []
    predict = []
    
    for line in f.readlines():
        sp = line.split()
        label.append(float(sp[0]))
        predict.append(float(sp[1]))

    label = np.array(label)
    predict = np.array(predict)


    
    print "auc",roc_auc_score(label, predict)

    pp = [[1-i,i] for i in predict]

    print "loglos",log_loss(y_true=label, y_pred=pp)

    pps = [above(i,0.5) for i in predict]

    print "f1",f1_score(label,pps)

    
