#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Draw a square maze based on input
# This is from Erik Sweet and Bill Basener

import sys
import numpy as np
from matplotlib import cm as cm
from matplotlib import pyplot as plt

if len(sys.argv) != 3:
    print("usage: drawer ROW COL", file=sys.stderr)
    exit(1)

num_rows = int(sys.argv[1]) # number of rows
num_cols = int(sys.argv[2]) # number of columns

# The array M is going to hold the array information for each cell.
# The first four coordinates tell if walls exist on those sides 
# M(UP, RIGHT, DOWN, LEFT)
M = np.zeros((num_rows,num_cols,4), dtype=np.uint8)

# Read M from stdin
for i in range(num_rows):
    for j in range(num_cols):
        for k in range(4):
            x = int(input())
            M[i,j,k] = x;

# The array image is going to be the output image to display
image = np.zeros((num_rows*10,num_cols*10), dtype=np.uint8)

# Generate the image for display
for row in range(0,num_rows):
    for col in range(0,num_cols):
        cell_data = M[row,col]
        for i in range(10*row+1,10*row+9):
            image[i,range(10*col+1,10*col+9)] = 255
            if cell_data[0] == 1: image[10*row,range(10*col+1,10*col+9)] = 255
            if cell_data[1] == 1: image[range(10*row+1,10*row+9),10*col+9] = 255
            if cell_data[2] == 1: image[10*row+9,range(10*col+1,10*col+9)] = 255
            if cell_data[3] == 1: image[range(10*row+1,10*row+9),10*col] = 255

# Display the image
plt.imshow(image, cmap = cm.Greys_r, interpolation='none')
plt.show()
