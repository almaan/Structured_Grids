#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov 27 17:06:19 2018

@author: hackerman1337
"""
import matplotlib.pyplot as plt
import numpy as np

pth = "/home/hackerman1337/Documents/KTH-Schoolwork/SF2565-Programkonstruktion-cpp/cpp/proj3/grid.dat"

raw_crd = []
start_read = False

with open(pth,"r+") as fopen:
    for line in fopen:
        if start_read:
            raw_crd.append(line.replace('\n',''))
        if "#" in line: start_read = True;

crd = np.array(list(map(lambda x : [float(x.split(',')[0]),float(x.split(',')[1])],raw_crd)))

plt.scatter(crd[:,0],crd[:,1], s = 10)