#!/usr/bin/python

train_dir = "../data/ida/train.csv"
test_dir = "../data/ida/train.csv"

from sklearn.linear_model import SGDClassifier
from sklearn.linear_model import LogisticRegression

def parse(line):
    """
    """

    sp = line.split()
    
    label = sp[0]
    sp = sp[1:]
    x = []
    for one in sp:
        _,value = one.split(":")
        x.append(float(value))

    return float(label),x
    
    

def main():
    """
    """

    x,y = [],[]
    test,label = [],[]
    
    f = open(train_dir)
    for line in f.readlines():
        l,xs = parse(line)
        x.append(xs)
        y.append(l)

    f = open(test_dir)
    for line in f.readlines():
        l,xs = parse(line)
        test.append(xs)
        label.append(l)


    #clf = SGDClassifier(loss="log", penalty="l2",n_iter=200)
    clf = LogisticRegression(penalty='l2',dual=True,fit_intercept=True,C=2,tol=0.0001,class_weight=None, random_state=None, intercept_scaling=0.1)
    clf.fit(x,y)

    ans = clf.predict(test)

    right = 0
    
    for i in range(len(ans)):
        if ans[i] == label[i]:
            right += 1

    print right * 1.0 / len(ans)
    

if __name__ == '__main__':
    print("hello")
    main()
    
