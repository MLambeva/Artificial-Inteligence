import math

def readInput():
    f = open(".vscode\hw5\house-votes-84.data", "r")
    allSet = f.readlines()
    allSet = list(map(lambda y: y[:-1].split(','), allSet))
    return allSet


def totalLenClass(classOfEl, allData):  # return count of republicans or democrats
    return len(list(filter(lambda y: (y[0] == classOfEl), allData)))


def probClass(classOfEl, allData, lmbd):  # P(Class = classOfEl)
    return math.log((totalLenClass(classOfEl, allData)+lmbd)/(len(allData) + 2*lmbd))


def condProb(training_set, learning_set, classOfEl, i, lmbd):# P(x1=aj/value/|class=classOfEl)
    value = training_set[i]
    countSection = len(list(filter(lambda y: (y[i] == value and y[0] == classOfEl), learning_set)))
    return math.log((countSection + lmbd)/(totalLenClass(classOfEl, learning_set) + (len(training_set)-1)*lmbd))

def findProb(training_set, learning_set, classOfEl, lmbd):# P(class=classOfEl|x1,...,xn)
    i = 1
    res = 0
    while (i < 16):
        res += condProb(training_set, learning_set, classOfEl, i, lmbd)
        i = i + 1
    res += probClass(classOfEl, learning_set, lmbd)
    return res

def defineClass(training_set, learning_set, lmbd):
    dem = findProb(training_set, learning_set, 'democrat', lmbd)
    rep = findProb(training_set, learning_set, 'republican', lmbd)
    if(dem > rep):
        return 'democrat'
    else:
        return 'republican'


#x = readInput()
#print("\nLaplace:\nDemocrat: " + str(2**findProb(x[0], x[1:], 'democrat', 1)))
#print("Republican: " + str(2**findProb(x[0], x[1:], 'republican', 1)))
#print("MAX:", defineClass(x[0], x[1:], 1))

#print("\nOrdinary:\nDemocrat: " + str(2**findProb(x[0], x[1:], 'democrat', 0)))
#print("Republican: " + str(2**findProb(x[0], x[1:], 'republican', 0)))
#print("MAX:", defineClass(x[0], x[1:], 0))

# ---------------------------------------------------------------------------TEST---------------------------------------------------------------------------------#

def split10fold(allSet):
    saver = list()
    count = math.floor(len(allSet)/10)
    for i in range(0, len(allSet), count):
        saver.append(allSet[i:i+count])
    return saver

def concatLearningList(learning_set):
    newLearningList = list()
    for i in learning_set:
        newLearningList += i
    return newLearningList

def findResultClasses(training_set):
    resultClassList = list()
    for i in training_set:
        resultClassList.append(i[0])
    return resultClassList

def acurrancy(lmbd):
    allSet = readInput()
    acc = 0
    splits = split10fold(allSet)
    for i in range(10):
        training_set = splits[i]
        learning_set = splits[0:i]+splits[i+1:10]
        newLearningList = concatLearningList(learning_set)
        currentClassList = list()
        for j in training_set:
            currentClassList.append(defineClass(j, newLearningList, lmbd))
        resultClasses = findResultClasses(training_set)
        res = 0
        for i in range(43):
            res = res + (resultClasses[i] == currentClassList[i])
        acc += res/len(training_set)
    return (acc/10)*100
    
print(acurrancy(1))
