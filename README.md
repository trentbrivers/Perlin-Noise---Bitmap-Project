# Perlin Noise & Bitmap Project
A project begun for my Summer 2024 Data Structures coursework. The goal is to write a C++ program that implements Perlin noise and outputs a bitmap image.

## Introduction
### The Algorithm - Perlin Noise
Perlin Noise was first developed in the 1980's while Ken Perlin was working on special effects for the movie Tron. It was created to address a very specific problem: true randomness (or noise) is rarely visually appealing. Take, for example, the following image, where all of the pixels have a randomized grayscale value between black and white assigned to them.
\
![raw_noise](https://github.com/user-attachments/assets/38f5f8fd-ef90-4454-a9a6-48f15d7ae142)
\
With a so-called "random" result such as this, there is a uniformity and lack of detail to the image that makes it very unappealing to look at and almost useless for artistic purposes. It's difficult to point to where we might see this kind of uniform randomness reflected in the natural world. 

Perlin Noise was created to address the problem of how artifical and "machine-like" established noise algorithms were. The following image is an example of what Perlin Noise can produce:
\
![noiseTexture (1)](https://github.com/user-attachments/assets/635af4ca-25c8-41dd-865b-5819b19ff9a4)
\
Amidst the randomness of the image, it is possible discern shapes that resemble letters, branching strands, or even small organisms you might see under a microscope. It appears that Ken Perlin was successful in creating a noise algorithm which creates natural looking and appealing random variation. The Academy of Motion Picture Arts and Sciences indicated as much in his 1997 Technical Achievement Award: "To Ken Perlin for the development of Perlin Noise, a technique used to produce natural appearing textures on computer generated surfaces for motion picture visual effects. The development of Perlin Noise has allowed computer graphics artists to represent the complexity of natural phenomena in visual effects for the motion picture industry."<sup>1</sup>

Today, Perlin Noise is a staple of computer graphics, used to introduce variation in surfaces, geometry, volumes, and more. It's implemented in most major CG software packages, including Autodesk Maya, 3D Studio Max, Renderman, Cinema 4D, Houdini, and more.


## Workings Explained
### Perlin Noise
One of the wonderful characteristics of Perlin Noise is that, abstractly, it's a simple algorithm. Referring to his previous work in a 2002 paper, Perlin writes "[In three dimensions] Noise is determined at point (x,y,z) by computing a pseudo-random gradient at each of the eight nearest vertices on the integer cubic lattice and then doing splined interpolation." <sup>2</sup> The same principle applies in as many dimensions as one wants. For the purposes of this project, we will be discussing Perlin Noise within a 2D space, with coordinates *x* and *y*.

#### Defining a grid to form the gradient
In the case of 2D perlin noise, a 2D grid of integer points is taken as an input.\
![point_grid_1](https://github.com/user-attachments/assets/2c99bb35-3121-4915-9c75-210f10aa9595)\
A little work needs to happen with the input grid to get it ready for the algorithm. What happens is the grid has constant, pseudo-random 2-dimensional unit vectors added for every point of the grid.

#### Getting a vector
![point_grid_2](https://github.com/user-attachments/assets/0d573fe0-007f-41cb-8199-c4287ef36ddc)\

Now, for an arbitrary point with (x,y) coordinates expressed in float, there is some position within the grid where the point will sit<sup>3</sup>. \
What we need is a set of distance vectors from the nearest points corners of the grid to our selected point. This gives us two vectors for each of those four points: the distance vector to our selected point and the pseudorandom vector on that point.

#### Taking the cross product
![point_grid_3](https://github.com/user-attachments/assets/c323b3b0-df2a-4396-afda-ff5bdd58229f)

We now have two vectors for each corner. Here, we take the dot product of the two vectors, repeating the process for each corner. In order to calculate the dot product, we multiply the corresponding x and y components of the vectors together, and add them<sup>4</sup>.This looks like *dot_product* = v1[x]*v2[x] + v1[y]*v2[y]. This produces 4 dot products in total. 

NOTE: while it's not a step of the algorithm, it may be helpful to visualize what we've done here. If we repeated this process for a number of prospective points across the grid, we'd end up with a series of dot products that covered the grid, and looked something like this:

![640px-PerlinNoiseDotProducts svg](https://github.com/user-attachments/assets/3c510080-ade3-496f-8fa7-9625b7a68133)

#### Interpolating the results
The final step in the process is to interpolate the results of the dot products from the vectors. This is the step that makes Perlin Noise feel more natural than other noise algorithms. It forms a smooth gradient between the values of the graph. 
Ken Perlin's original Perlin Noise implementation used 3t<sup>2</sup>-2t<sup>3</sup> to interpolate between values. The final result looks something like the following:

![640px-PerlinNoiseInterpolated svg](https://github.com/user-attachments/assets/f9c93ea5-3ecb-49b6-b848-6d61a57dfabd)

Unfortunately, one of the downsides of Perlin Noise is that it's not very efficient. Perlin Noise has a complexity of O(2^n) where n is the number of dimensions it's operating on<sup>5</sup>. 

### The Data Structure - Bitmaps
Bitmaps are a special kind of array based data structure. At the lowest level, they are composed of red, greed, and blue values which are associated with the colors an electronic display screen can output. These can be stored in a pixel struct, an array, or a number of other solutions. However, the greater bitmap structure itself is composed of a 2-Dimensional collection of these smaller pixel values. 

My implementation of bitmaps used a vector of vectors of smaller pixel structs within C++. The pixel structs stored the three red, green, and blue values as integers from 0 to 255. Accessing the pixels can be done using (x,y) coordinates, for example pixel_grid[120][20] would be the pixel at (120, 20).

##Using the Application

References:
1. https://cs.nyu.edu/~perlin/doc/oscar.html\
2. http://mrl.nyu.edu/~perlin/paper445.pdf\
3. https://adrianb.io/2014/08/09/perlinnoise.html\
4. https://www.educative.io/answers/dot-product-of-two-vectors-in-cpp\
5. https://www.jordansavant.com/book/algorithms/perlin_noise.md\
