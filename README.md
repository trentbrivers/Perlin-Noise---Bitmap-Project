# Perlin Noise & Bitmap Project
A project begun for my Summer 2024 Data Structures coursework. The goal is to write a C++ program that implements Perlin noise and outputs a bitmap image.

## Introduction
Perlin Noise was first developed in the 1980's while Ken Perlin was working on special effects for the movie Tron. It was created to address a very specific problem: true randomness (or noise) is rarely visually appealing. Take, for example, the following image, where all of the pixels have a randomized grayscale value between black and white assigned to them.
\
![raw_noise](https://github.com/user-attachments/assets/38f5f8fd-ef90-4454-a9a6-48f15d7ae142)
\
With a so-called "random" result such as this, there is a uniformity and lack of detail to the image that makes it very unappealing to look at and almost useless for artistic purposes. It's difficult to point to where we might see this kind of uniform randomness reflected in the natural world. 

Perlin Noise was created to address the problem of how artifical and "machine-like" established noise algorithms were. The following image is an example of what Perlin Noise can look produce:
\
![noiseTexture (1)](https://github.com/user-attachments/assets/635af4ca-25c8-41dd-865b-5819b19ff9a4)
\
Amidst the randomness of the image, it is possible discern shapes that resemble letters, branching strands, or even small organisms you might see under a microscope. It appears that Ken Perlin was successful in creating a noise algorithm which creates natural looking and appealing random variation. The Academy of Motion Picture Arts and Sciences indicated as much in his 1997 Technical Achievement Award: "To Ken Perlin for the development of Perlin Noise, a technique used to produce natural appearing textures on computer generated surfaces for motion picture visual effects. The development of Perlin Noise has allowed computer graphics artists to represent the complexity of natural phenomena in visual effects for the motion picture industry."<sup>1</sup>

Today, Perlin Noise is a staple of computer graphics, used to introduce variation in surfaces, geometry, volumes, and more. It's implemented in most major CG software packages, including Autodesk Maya, 3D Studio Max, Renderman, Cinema 4D, Houdini, and more.


## The Algorithm - Perlin Noise
One of the wonderful characteristics of Perlin Noise is that, abstractly, it's a simple algorithm. Referring to his previous work in a 2002 paper, Perlin writes "[In three dimensions] Noise is determined at point (x,y,z) by computing a pseudo-random gradient at each of the eight nearest vertices on the integer cubic lattice and then doing splined interpolation." <sup>2</sup> The same principle applies in as many dimensions as you

Perlin Noise is cool<sup>3</sup>

References:
1.https://cs.nyu.edu/~perlin/doc/oscar.html
2. http://mrl.nyu.edu/~perlin/paper445.pdf\
3. https://rtouti.github.io/graphics/perlin-noise-algorithm
