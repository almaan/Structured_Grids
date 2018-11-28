#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov 27 17:06:19 2018

@author: Alma Andersson

"""
import matplotlib.pyplot as plt
import numpy as np
import sys

plt.style.use('seaborn-dark')

if sys.argv[1].lower() in ['--help','-h','help']:
    print(f"script to visualize rendered grid over domain\n")
    print(f"enter name of x-coordinate bin-file as first argument")
    print(f"enter name of y-coordinate bin-file as second argument")
    sys.exit(0)

if sys.argv[1].split('.')[-1] != 'bin' or sys.argv[2].split('.')[-1] != 'bin':
    print(f'Please enter name of two bin files containing x and y coordinates')
    sys.exit(0)

try:
    with open(sys.argv[1],"rb") as fopen:
        x_vec = np.fromfile(fopen,count = -1)
        
except FileNotFoundError:
    print(f"x-vector file not found")
    sys.exit(0)

try:
    with open(sys.argv[2],"rb") as fopen:
        y_vec = np.fromfile(fopen,count = -1)
except FileNotFoundError:
    print(f"y-vector file not found")
    sys.exit(0)
    
x_vec = np.array(x_vec)
y_vec = np.array(y_vec)


plt.scatter(x_vec,y_vec, s = 10,zorder = 1,color = 'black')
plt.xlabel('x')
plt.ylabel('y')
plt.title(r'20x50 grid generated for domain $\Omega$')
plt.show()
