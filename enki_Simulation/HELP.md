You need the QT5 library and its development packages to compile it.


## Enki simulator compilation under Unix (library)

Change into the enki subdirectory and type:

	qmake

and then build Enki by running:

	make

and finally install the library with
	
	sudo make install


## Compiling AI

Move into clBP/build and run "cmake .."

## Compiling/running the examples

To compile the examples you need to do again `qmake` and `make`. This uses the
previously compiled enki library.

To run it type, for example, `./playground`


## Working on source code

compiling is handled through the enkiSimulator.pro file in examples/line_follower looking through this file will show the locations of all c++ and header files. A good way to work is to download the Qt Creator IDE and open this .pro file in it. This will import al .cpp and .h files into the IDE. Don't worry about enteprise/open source version when your free trial runs out it reverts to the open source version. 

##Compile changes by running 

-make clean

-qmake

-make

-./enkisimulator 

