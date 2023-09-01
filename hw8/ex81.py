import random
import math

# Активираща функция - връща стойност между 0 и 1


def sigmoid(x):
    return 1 / (1 + math.exp(-x))


def sigmoid_derivative(x):
    return x * (1 - x)


input1 = [0, 0]
input2 = [0, 1]
input3 = [1, 0]
input4 = [1, 1]

output1 = 0
output2 = 1


def func(input, output):
    weights = [random.uniform(-1, 1), random.uniform(-1, 1)]
    bias = random.uniform(-1, 1)

    learning_rate = 0.1  # от него зависи обновяването на теглото
    # при по-малки стойности -> по-малко сближаване, но по-стабилно

    for epoch in range(1000):

        layer = sigmoid(weights[0]*input[0] + weights[1]*input[1] + bias)

        layerError = output - layer 
        layerDelta = layerError * sigmoid_derivative(layer)
        weights = list(map(lambda w : (w + ((input[0] * layerDelta + input[1] * layerDelta) * learning_rate)), weights))

        bias += layerDelta * learning_rate

    res = sigmoid(weights[0]*input[0]+weights[1]+input[1] + bias)
    print("Output layer for input " + str(input) +
          " ---> " + str(res) + " ---> " + str(round(res)))


print("AND: ")
func(input1, output1)
func(input2, output1)
func(input3, output1)
func(input4, output2)

print("OR: ")
func(input1, output1)
func(input2, output2)
func(input3, output2)
func(input4, output2)
