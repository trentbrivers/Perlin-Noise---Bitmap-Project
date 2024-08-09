# Perlin Noise & Bitmap Project
A project begun for my Summer 2024 Data Structures coursework. The goal is to write a C++ program that implements Perlin noise and outputs a bitmap image.

## Introduction

![raw_noise](https://github.com/user-attachments/assets/38f5f8fd-ef90-4454-a9a6-48f15d7ae142)\

The following image gives an example of the kind of result Perlin noise can look like:\
![noiseTexture (1)](https://github.com/user-attachments/assets/635af4ca-25c8-41dd-865b-5819b19ff9a4)\


## The Algorithm - Perlin Noise
One of the wonderful characteristics of Perlin noise is that, abstractly, it's a simple algorithm. Referring to his previous work in a 2002 paper, Perlin writes "[In three dimensions] Noise is determined at point (x,y,z) by computing a pseudo-random gradient at each of the eight nearest vertices on the integer cubic lattice and then doing splined interpolation." <sup>1</sup> The same principle applies in as many dimensions as you

Perlin Noise is cool<sup>2</sup>

References:
1. http://mrl.nyu.edu/~perlin/paper445.pdf\
2. https://rtouti.github.io/graphics/perlin-noise-algorithm
