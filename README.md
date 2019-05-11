# cubeRotation

This program was made using an example from one of my teacher at Cranfield University.

## Building

It was build using Qt 5.7.0 and using Opengl core 4.2. To run it using other versions of opengl, the main.cpp and the mainview.hpp files are to be modified.

The program can be built in two different ways. Either using the .pro file and QTCreator, in which case the data folder and the shader folder will need to be moved to the build directory or with cmake.

```bash
cmake .
make
./bin/cubeRotation
```

## What is what

### The data folder

The data folder contains the information about the cube to be displayed. The file sceneCube.dat is composed as follow:

- The first 36 lines represent the data of the vertex of the cube to be drawn, every group of three lines represent a triangle
- The next two lines represent the coordinate of the line to rotate around
- The next 36 lines represent the color of the triangles
- The last two line represent the color of the rotation line

### Rotation

The line rotation menu allow to make a rotation for the cube. The rotation is made around the line that is defined by the user.

The parameters are as follow:

- The x, y, z parameters define the line relative to the center of the system
- The offsets define the offset of the line previously defined
- The angle define the by how much the cube should rotate around the line defined

### Set view

Can be used to set the view from which the user will be seeing the cube.

The parameters are as follow:

- The eye_x/y/z parameters define the position of the eye of the user
- the center_x/y/z parameters define where the user is looking
