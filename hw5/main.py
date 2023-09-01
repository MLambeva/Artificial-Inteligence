import math

f = open(".vscode\hw5\house-votes-84.data", "r")
x = f.readlines()
x = list(map(lambda y: y[:-1].split(','), x))


def totalLenClass(classOfEl, allData):  # return count of republicans or democrats
    return len(list(filter(lambda y: (y[0] == classOfEl), allData)))


def probClass(classOfEl, allData):  # P(Class = classOfEl)
    return totalLenClass(classOfEl, allData)/len(allData)
    # return len(list(filter(lambda y: (y[0] == classOfEl), allData)))/len(allData)


def function(training_set, learning_set, classOfEl, i):
    value = training_set[i]
    #if (value != '?'):
    return len(list(filter(lambda y: (y[i+1] == value and y[0] == classOfEl), learning_set)))/totalLenClass(classOfEl, learning_set)
    #else:
     #   return 0

#print(x)
learning_set = [['republican', 'n', 'y', 'n', 'y', 'y', 'y', 'n', 'n', 'n', 'y', '?', 'y', 'y', 'y', 'n', 'y'],
                ['republican', 'n', 'y', 'n', 'y', 'y', 'y', 'n',
                    'n', 'n', 'n', 'n', 'y', 'y', 'y', 'n', '?'],
                ['democrat', '?', 'y', 'y', '?', 'y', 'y', 'n', 'n', 'n', 'n', 'y', 'n', 'y', 'y', 'n', 'n']]
training_set = [ 'n', 'y', 'n', 'y', 'y', 'y', 'n', 'n', 'n', 'y', 'n', 'y', 'y', 'y', 'n', 'y']


def func(training_set, learning_set, classOfEl):
    i = 0
    res = 1
    while (i < 16):
        res *= function(training_set, learning_set, classOfEl, i)
        i = i + 1
    res *= probClass(classOfEl, learning_set)
    return res


print(func(training_set, x[1:], 'democrat'))

print(func(training_set, x[1:], 'republican'))

print(max(func(training_set, x, 'democrat'), func(training_set, x, 'republican')))
