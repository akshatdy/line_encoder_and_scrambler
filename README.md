# Overview:

This project implements a Line Encoder and Scrambler for digital communication systems. The Line Encoder converts binary data into various encoding schemes like NRZ, Manchester, AMI, etc., while the Scrambler introduces randomness to ensure data integrity and reduce synchronization issues during transmission.

# Requirements:

1. freeglut 2.8.1-1.mp for MSVC
2. glew 1.11.0

# How to run the code:

1. After installing the above packages, open the solution in Visual Studio 2022.
2. Open properties page. 
3. Under C/C++ option, click on General. Then, in Addition include directories, change the path according to your path of installation of freeglut and glew.
4. Similarly, go to Linker option, and click on General. For Addition Library directories, change the path accordingly.
5. Now, just build and run the solution for your custom testcase.