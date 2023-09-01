import random
import math

# Активираща функция - връща стойност между 0 и 1


def sigmoid(x):
    return 1 / (1 + math.exp(-x))


def sigmoid_derivative(x):
    return sigmoid(x) * (1 - sigmoid(x))


input1 = [0, 0]
input2 = [0, 1]
input3 = [1, 0]
input4 = [1, 1]

output1 = 0
output2 = 1


def func(input, output):
    weights1 = [random.uniform(-1, 1), random.uniform(-1, 1),
                random.uniform(-1, 1), random.uniform(-1, 1)]
    weights2 = [random.uniform(-1, 1), random.uniform(-1, 1)]
    bias1 = random.uniform(-1, 1)
    bias2 = random.uniform(-1, 1)

    learning_rate = 0.1  # от него зависи обновяването на теглото
    # при по-малки стойности -> по-малко сближаване, но по-стабилно

    for epoch in range(10000):
        # Forward propagation
        # изходът на първия слой в невронната мрежа
        layer1 = [sigmoid(input[0]*weights1[0] + input[1]*weights1[1] + bias1),
                  sigmoid(input[0]*weights1[2] + input[1]*weights1[3] + bias1)]
        # изходът на втория слой в невронната мрежа
        layer2 = sigmoid(weights2[0]*layer1[0] + weights2[1]*layer1[1] + bias2)

        # Backpropagation
        layer2Error = output - layer2  # грешката между изхода и втория слой
        # изп., за да изчислим градиента
        layer2Delta = layer2Error * sigmoid_derivative(layer2)

        # грешката в първия слой
        layer1Error = layer2Delta * weights2[0] + layer2Delta * weights2[1]
        layer1Delta = [
            layer1Error * sigmoid_derivative(layer1[0]), layer1Error * sigmoid_derivative(layer1[1])]

        # Обновяване на теглата и биаса, за да се намали грешката
        #weights1[0] += (input[0] * layer1Delta[0] + input[1] * layer1Delta[1]) * learning_rate
        #weights1[1] += (input[0] * layer1Delta[0] + input[1] * layer1Delta[1]) * learning_rate
        #weights1[2] += (input[0] * layer1Delta[0] + input[1] * layer1Delta[1]) * learning_rate
        #weights1[3] += (input[0] * layer1Delta[0] + input[1] * layer1Delta[1]) * learning_rate

        weights1 = list(map(lambda w: (
            w + ((input[0] * layer1Delta[0] + input[1] * layer1Delta[1]) * learning_rate)), weights1))

        #weights2[0] += (layer1[0] * layer2Delta +  layer1[1] * layer2Delta) * learning_rate
        #weights2[1] += (layer1[0] * layer2Delta +  layer1[1] * layer2Delta) * learning_rate
        weights2 = list(map(lambda w: (
            w + ((layer1[0] * layer2Delta + layer1[1] * layer2Delta) * learning_rate)), weights2))

        bias1 += (layer1Delta[0] + layer1Delta[1]) * learning_rate
        bias2 += layer2Delta * learning_rate

    res = sigmoid(
        (weights2[0]*sigmoid(weights1[0]*input[0]+weights1[1]+input[1] + bias1)) + weights2[1]*sigmoid(weights1[2]*input[0]+weights1[3]+input[1] + bias1) + bias2)
    print("Output layer for input " + str(input) +
          " ---> " + str(res) + " ---> " + str(round(res)))


print("XOR: ")
func(input1, output1)
func(input2, output2)
func(input3, output2)
func(input4, output1)

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
