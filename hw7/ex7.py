import random
import matplotlib.pyplot as plt
import glob
import os


def readInput(file):
    f = open(file, "r")
    allSet = f.readlines()
    allSet = list(map(lambda y: y[:-1].split(' '), allSet))
    return allSet


file = readInput(".\\normal\\normal.txt")
#file = readInput(".\\unbalance\\unbalance.txt")
file = list(map(lambda x: list(map(float, x)), file))


def plotAll():
    first = list(map(lambda y: y[0], file))
    second = list(map(lambda y: y[1], file))
    plt.plot(first, second, "o")
    plt.show()


def euclideanDist(p1, p2):
    return (p2[0]-p1[0])**2 + (p2[1]-p1[1])**2


def plotPoint(listData, centroids, numIt, summ):
    index = 0
    for i in listData:
        s = plt.plot(centroids[index][0],
                     centroids[index][1], "x", markersize=30)
        colors = s[0].get_color()
        plt.plot(list(map(lambda y: y[0], i)), list(
            map(lambda y: y[1], i)), "o", color=colors)
        index = index + 1
    plt.title("Iteration" + str(numIt) + "; IntraClusterDistance=" + str(summ))
    plt.savefig("result\\fig" + str(numIt) + ".jpg")
    # plt.show()


def intraCluster(cluster, cent):
    sum = 0
    for i in cluster:
        sum = sum + euclideanDist(i, cent)
    return sum


def listIntraCluster(listData, centroids):
    index = 0
    saver = []
    for i in listData:
        saver.append(intraCluster(i, centroids[index]))
        index = index + 1
    return saver


def avg(lst):
    return sum(lst) / len(lst)


def mainCent(listData):

    res = []
    for i in listData:
        res.append([avg(list(map(lambda j: j[0], i))),
                   avg(list(map(lambda j: j[1], i)))])
    return res


def kMeans(K, numIt, centroids):
    # listData = []#K sublist
    listData = [[] for x in range(K)]

    for i in file:
        data = list(map(lambda y: euclideanDist(y, i), centroids))
        minValue = min(data)
        minIndex = [i for i, val in enumerate(data) if val == minValue]
        listData[minIndex[0]].append(i)

    summ = sum(listIntraCluster(listData, centroids))
    plt.clf()
    plotPoint(listData, centroids, numIt, summ)
    return summ, listData


def main(K):
    length = len(file)
    centroids = []
    useIndex = []
    i = 0
    while i < K:
        index = random.randint(0, length-1)
        if index not in useIndex:
            useIndex.append(index)
            centroids.append(file[index])
            i = i + 1

    centro = []
    curr, listData = kMeans(K, 0, centroids)
    it = 1
    centro = mainCent(listData)
    while it < 30:
        min, newList = kMeans(K, it, centro)
        if curr == min:
            return
        centro = mainCent(newList)
        it = it + 1
        curr = min


files = glob.glob("E:\\4course\\II\\c++\\.vscode\\hw7\\result\\*")
for f in files:
    os.remove(f)

main(3)
