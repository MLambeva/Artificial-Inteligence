import math
import sys
import random

sys.setrecursionlimit(1000000)


def readInput(file):
    f = open(file, "r")
    allSet = f.readlines()
    allSet = list(map(lambda y: y[:-1].split(','), allSet))
    return allSet


def unique(allSet, attrNo):
    uniqueList = []
    for i in allSet:
        if i[attrNo] not in uniqueList:
            uniqueList.append(i[attrNo])
    return uniqueList


allSet = readInput("breast-cancer.data")
classes = unique(allSet, 0)

newList = []
for m in allSet:
    dictOfWords = {i: m[i] for i in range(0, len(m))}
    newList.append(dictOfWords)
allSet = newList


def countClass(classOfEl, allSet):
    return len(list(filter(lambda y: y[0] == classOfEl, allSet)))


def entropy(allSet):
    propPositive = countClass(classes[0], allSet)/len(allSet)
    # print("PROP+"+str(propPositive))
    propNegative = countClass(classes[1], allSet)/len(allSet)
    # print("PROP-"+str(propNegative))
    if (propPositive != 0 and propNegative != 0):
        return -propPositive*math.log2(propPositive)-propNegative*math.log2(propNegative)
    else:
        return 0


def infoGain(S, A):  # A = attrNo
    entropyS = entropy(S)
    uniqueList = unique(S, A)
    for i in uniqueList:
        saver = list(filter(lambda y: y[A] == i, S))
        entropyS -= (len(saver)/len(S)) * entropy(saver)
    return entropyS


def ID3(allSet, node, l, res):

    if entropy(allSet) == 0:
        l.update({0: allSet[0][0]})
        sorted_dict = {key: l[key] for key in sorted(l.keys())}
        res.append(sorted_dict)
        l.pop(node)
        return
    var = {i: infoGain(allSet, i) for i in range(1, 10)}
    node = var[1]
    index = 1
    for i in var:
        if var[i] > node:
            node = var[i]
            index = i
    if node == 0:
        return
    listt = unique(allSet, index)
    for i in listt:
        l.update({index: i})
        ID3(list(filter(lambda y: y[index] == i, allSet)), index, l, res)


def defClass(training_set):
    l = {}
    res = []

    ID3(allSet, '', l, res)
    for i in res:
        for j in training_set:
            if j != 0 and training_set[j] in list(i.values()) and j in i:
                i.pop(j)
        for k in res:
            if len(k) == 1:
                return k[0]
    return []


def split10fold(allSet):
    saver = list()
    count = math.floor(len(allSet)/10)
    for i in range(10):
        saver.append(random.sample(allSet, count))
    return saver


def findResultClasses(training_set):
    resultClassList = list()
    for i in training_set:
        resultClassList.append(i[0])
    return resultClassList


def acurrancy():
    acc = 0
    splits = split10fold(allSet)
    for i in range(10):
        training_set = splits[i]
        currentClassList = list()
        for j in training_set:
            currentClassList.append(defClass(j))
        resultClasses = findResultClasses(training_set)
        res = 0
        for i in range(len(training_set)):
            res = res + (resultClasses[i] == currentClassList[i])
        acc += res/len(training_set)
    return (acc/10)*100


print("Accurancy: " + str(acurrancy()))
