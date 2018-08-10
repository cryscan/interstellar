## Interstellar Car Park 3D v3.0

### Introduction
The software is the second part of VG101 Project 3.
The software demonstrates an interstellar parking lot which stops UFOs and alien spaceships. A human being driving a space car goes into the parking lot and stops his car in one of the slots. He should follow the instruction on the ground and reverse into the slot.

###	Quick Start
The program uses CMake to manage compilation and uses GCC as compiler.
To compiler the project, please make sure that you have installed the following packages in your system:
cmake, make, gcc and freeglut.
##### Compile on Windows
To compile on windows, we recommend to use CLion,
whose toolchain is mingw-64 with all required packages installed.
After loading the project root, CLion will configure CMake and after that,
just click “Compile” button to compile.
##### Compile on Linux
On linux systems you can just use CMake to compile the program.
Enter the project root and type the commands
```
mkdir build
cd build
cmake ..
make
```
The executable will be generated in the [bin](./bin) directory. Before running the program, please make sure that the
[data](./bin/data) folder is along with the executable,
or you will see nothing on the screen.
Now run the program and enjoy the future-feeling rendering!

### Controls and Features
* Hold left mouse button and drag to rotate 3D scene
* Press ESC to exit
* A large parking lot with two regions
* Highly-detailed UFOs which spin on itself while preceding in the reverse direction
* Spaceships of higher dimensional creatures whose shapes could not be observed
* A car follows the path guide and moves smoothly to an empty slot
 
###	File Structures
There are three main folders under the root directory:
[bin](./bin), [include](./include) and [src](./src).

[bin](./bin) stores the built executive and external assess required by the program.
Header files are all in [includes](./include) directory,
while source files are in the [src](./src) directory.

Files in [src](./src) and [include](./include) folders are separated in more detail.
Five subdirectories organize the code into different parts.
##### glm
GLM is an easy-to-use header only math library foe OpenGL, which provides matrix and vector manipulations as GLSL does.

In the project where we need a lot of matrix manipulations to calculate translations, curves, etc.,
we are not allowed to use external libraries.
So we implement a 'glm' library by ourselves which contains basic functions like matrix mutilations and solving systems of linear equations and so on.
It also takes the advantage of templates which make it type-independent.
However, its implementation is different from the original GLM library.

##### models
The code in [models](./src/models) directory is responsible for managing geometric and textural information of rendered objects.

[model](./include/models/model.h) is their base class.
[figures](./include/models/figures.h) defines some basic 2D shapes.
[rocket](./include/models/rocket.h) is a hard-coded rocket model (unused).
[ms3d](./include/models/ms3d.h) loads complicated models from Milk Shape 3D model files.
Note, that a model does not contain any transformation information.

##### objects
Code in [objects](./src/objects) defines objects that are actually presented in the scene.
An object usually contains a model (which determines the object's shape), along with its transformation (position, rotation, etc.).

[object](./include/objects/object.h) is their base class.
[outline](./include/objects/outline.h) is a class of special objects that uses advanced render techniques,
which is inherited by [spaceship](./include/objects/spaceship.h) to render the 'merging shinning boundary' effect.
Some object like [camera](./include/objects/camera.h) does not contain a model.
It only does the look-at transform.

##### system
Code in [system](./src/system) manages the life cycle of the program.

[window](./include/system/window.h) opens an OpenGL window and sets up callback functions.
[engine](./include/system/engine.h) controls all resources,
manages all objects in the scene and triggers all events like updating,
rendering and mouse clicking, which actually 'runs' the program (just as a car engine).
[grid](./include/system/grid.h) maintains an abstract representation of the parking lot,
along with some other functions like path finding and object generating.

##### utils
[spline](./include/utils/spline.h) in this directory implements an algorithm to solve cardinal splines,
which is used in guiding the car along a smooth curve.

### Known Bugs
* When the car begins to reversing, it will move a little bit. This may be caused by rapid changing tangent line at the turning point.

### References
Some pieces of code or thoughts relating to concrete detail techniques refer to following websites:
1. [Flyweight pattern](http://en.wikipedia.org/wiki/Flyweight_pattern)
2. [File structure of Milk Shape 3D models](http://paulbourke.net/dataformats/ms3d)
3. [Reading .bmp images and loading to OpenGL texture](https://stackoverflow.com/questions/41858408/how-to-load-texture-opengl)
4. [Look-at transform of objects](https://stackoverflow.com/questions/6992541/opengl-rotation-in-given-direction)
5. [Introduction to spline](https://blog.csdn.net/zju_fish1996/article/details/52735947)

### Copyright Information
1. The model of UFO is downloaded from [turbosqid](https://www.turbosquid.com) under the [TurboSquid Royalty Free License](https://blog.turbosquid.com/royalty-free-license/).
All other models and textures are created by ourselves and everyone can use them without permission.
2. UMJI-SJTU students are forbidden to use this code.
Any part of this code is not intended to appear in assignments, projects or examinations rather than VG101 S2018 Project 3 of Group 4.
We (VG101 S2018 Peoject 3 Group 4) are not responsible for any violations of JI Honor Code due to plagiarism.

### Contact
If you find bugs, have questions, or want to give me feedback, please contact contributors via email:\
Zhang Zhenyuan: lepetitsquarth@sjtu.edu.cn\
Hou Shuyuan: hsy1108@sjtu.edu.cn

### Contributors
Zhang Zhenyuan is he who writes the [glm](./include/glm) library.
He sets up the basic structure of the project, and designs models for the car and spaceship (poor crafting).

Hou Shuyuan is responsible for creating the layout of the parking lot as well as the path finding strategy. She also creates some basic models.

They work together on Cardinal splines for the smooth motion of the car.
