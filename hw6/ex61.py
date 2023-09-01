import math


def readInput(file):
    f = open(file, "r")
    allSet = f.readlines()
    allSet = list(map(lambda y: y[:-1].split(','), allSet))
    return allSet


def unique(allSet, attrNo): #get all values of attribute with number attrNo from all data set
    uniqueList = []
    for i in allSet:
        if i[attrNo] not in uniqueList:
            uniqueList.append(i[attrNo])
    return uniqueList

allSet = readInput("play-tennis.txt")
classes = unique(allSet, 0)

newList = []
#print(allSet)
for m in allSet:
    dictOfWords = { i : m[i] for i in range(0, len(m) ) }
    newList.append(dictOfWords)
allSet=newList #make data in dictionary
#print(allSet)

def countClass(classOfEl, allSet):
    return len(list(filter(lambda y: y[0] == classOfEl, allSet)))


def entropy(allSet):
    propPositive = countClass(classes[0], allSet)/len(allSet)
    #print("PROP+"+str(propPositive))
    #propPositive = countClass('recurrence-events', allSet)/len(allSet)
    propNegative = countClass(classes[1], allSet)/len(allSet)
    #print("PROP-"+str(propNegative))
    if (propPositive != 0 and propNegative != 0):
        #propNegative = countClass('no-recurrence-events', allSet)/len(allSet)
        return -propPositive*math.log2(propPositive)-propNegative*math.log2(propNegative)
    else:
        return 0


print("Entropy of all data: " + str(entropy(allSet)))

def infoGain(S, A):  # A = attrNo
    entropyS = entropy(S)
    uniqueList = unique(S, A)
    #print(uniqueList)
    for i in uniqueList:
        saver = list(filter(lambda y: y[A] == i, S))
        #print(str(i) + ' ' + str(entropy(saver)))
        entropyS -= (len(saver)/len(S)) * entropy(saver) #infoGain
    return entropyS


def ID3(allSet, node, l, res):

    if entropy(allSet) == 0:
        l.update({0:allSet[0][0]})#add class in tree
        sorted_dict = {key:l[key] for key in sorted(l.keys())}     
        res.append(sorted_dict)
        l.pop(node)
        return 
    var = {i : infoGain(allSet, i) for i in range(1, 5)}
    node = max(var, key=var.get)
    listt = unique(allSet, node)
    for i in listt:
        l.update({node:i})
        ID3(list(filter(lambda y : y[node]==i, allSet)), node, l, res)


training_set = allSet[2]

def defClass(training_set):
    l={}
    res=[]
    ID3(allSet, '', l, res)
    for i in res:
        for j in training_set:
            if j != 0 and training_set[j] in i.values() and j in i:
                i.pop(j)
        for k in res:
            if len(k) == 1:
                return k[0]
            

for training_set in allSet:
    print(str(training_set) + " ---> " + str(defClass(training_set)))

res=[]
ID3(allSet, '', {}, res)
print(res)