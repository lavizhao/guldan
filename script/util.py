import random

rand = random.random

#保留采样比例, train test分别为训练测试比例
def keep_train(train,test):
    km = train/(train+test)
    rm = rand()

    if rm < km:
        return True
    else:
        return False

#转换成libsvm的格式, 这个是全部连续的, 哈希再说
def libsvm_format(x,y=None):
    if y==None:
        y = x[0]
        x = x[1:]
        
    target = ""
    if float(y) == -1.0:
        y = '0.0'
    target += str(y)

    for indx,ele in enumerate(x):
        target += " f%s:%s"%(indx+1,ele)
        
    return [target]
        
def csv_format(x,y=None):
    if y==None:
        y = x[0]
        x = x[1:]
        
    target = []
    if float(y) == -1.0:
        y = '0.0'
    target.append(str(y))

    for indx,ele in enumerate(x):
        target.append(ele)
        
    return target
