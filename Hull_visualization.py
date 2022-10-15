from matplotlib import pyplot as plt
import numpy as np
import matplotlib.animation as animation
import time
import random


def check_points(list1, list2):
    new_list = all(item in list2 for item in list1)
    if new_list is True:
        return True
    else:
        return False


def remove(list1, list2):
    for i in list2:
        list1.remove(i)


def plot_points(x_test, y_test, x_solve, y_solve):
    x_final = []
    y_final = []

    for i in range(len(x_test)-1):
        xpoints = [x_test[i], x_test[i+1]]
        ypoints = [y_test[i], y_test[i + 1]]

        plt.plot(xpoints, ypoints)
        plt.plot(x_value, y_value, 'o')
        plt.plot(x_final, y_final)

        if check_points(xpoints, x_solve):
            x_final = x_final + xpoints
            y_final = y_final + ypoints
            remove(x_solve, xpoints)
            remove(y_solve, ypoints)

        plt.draw()
        plt.pause(1)
        plt.clf()


points1 = 'testpoints.txt'
points2 = 'outerpoints.txt'
new1 = points1.split(',')
new2 = points2.split(',')

x_test = []
y_test = []
x_solve = []
y_solve = []

for i in new1:
    test = i.split(' ')
    x_test.append(int(test[0]))
    y_test.append(int(test[1]))

for i in new2:
    test = i.split(' ')
    x_solve.append(int(test[0]))
    y_solve.append(int(test[1]))

plot_points(x_test, y_test, x_solve, y_solve)