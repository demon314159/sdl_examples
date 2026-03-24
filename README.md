These examples use the SDL2 or SDL3 libraries and also the GLEW library.
The builds are targeted for the x64 architecture.

The files SDL2.dll, SDL2_mixer.dll, SDL3.dll, glew32.dll must be added to c:Windows/System32.
(The proper versions are collected in the folder DLLS_to_include_in_System32)

The Makefile include path must point to SDL2, SDL3 and glew folders in order to build these.

The first examples incrementally get control of the SDL system, and the remaining examples are more interesting.

Example0: Initialize the SDL system and then quit.

Example1: Open a Window for a few seconds and then quit.

Example2: Open a Window and display a Bitmapped image for a few seconds and then quit.

Example3: Open a Window, display bitmap and remain open until user closes Window by clicking upper right corner.

Example4: OpenGL color test, display three different colors then close.

Example5: Standard OpenGL example of rotating colored triangle.

Example6: Display colored cubes.

All of the remaining examples use the 'Q' key to exit the program.

Example7: A study in animation with various rotating cubes

Example8: Another study in animation with a Slot Car simulation

Example9: Another study in animation with various rotating spheres

ExampleA: Preliminary work on a pinball concept. Left and right shift keys operate the flippers.

ExampleB: A fully operational Pinball Machine.  Press C to use credits and press L to launch the ball.
          The left and right shift keys operate the flippers.
          This is an exact clone of the 1970's Joker Poker machine.

ExampleC: An excellent puzzle game called Hexominos.  There are 48 increasingly challenging puzzles

ExampleD: A marble game that is not finished.

ExampleE: An excellent building game using bricks and doors and windows

ExampleF: A viewer to look at 3D objects exported in the STL format

There is an executable in each example compiled for Windows x64

