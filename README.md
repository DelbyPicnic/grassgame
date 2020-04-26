# A GrassGame
Canonical sequel to Space Game.  
This is a base project that has been adapted from a coursework project from university.  
Space Game was a 2D horizontal space shooter i made in highschool to test game mechanics and engine fundimentals, waaaay before I knew how to use version control. I have a copy of it somewhere I think.

# About
This is a WIP orthographical game, written in C++ using the SFML graphics framework.
The included graphics are taken from www.opengameart.org and the tilesets will be modified as required.

# Download and Compile
Required packages: [git, make, cmake, clang++ or g++]

The project files should be cloned from the master branch of this repository. As SFML has been added as a dependancy, you should use  
```git clone --recurse-submodules https://github.com/DelbyPicnic/grassgame.git```  
to clone the game files and the SFML library.

If you didn't use the ```--recurse-submodules``` flag then you can init the submodules manually by havigating to the directory
and running the following command:  
```git submodule update --init --recursive```

Compiling the project requires CMake 3.9 or later.
Generate makefiles for your specific platform using CMake:
*nix-based platforms:
```
cmake -G"Unix Makefiles"
make
```

Windows:
```
Use the CMake GUI to make VS2017 .sln project files
```

# Development
It is recommended that any work be done using a Unix or Unix-like environment, Windows is supported but is not an active focus. Any support I can give you will be relative to g++ or clang++.  
The recommended tools for developing and maintaining the software is VisualStudio Code and a modern C++ compiler such as g++ or clang++.  
```https://code.visualstudio.com/```  
To work on the level data and maps, use the Tiled Map Editor.  
```https://www.mapeditor.org/```  
To edit pixel-level graphics, use either PikoPixel or Adobe Fireworks.  
```http://twilightedge.com/mac/pikopixel/```

# Pull Requests & Contribution
Pull requests will be evaluated according to code quality, and then signifigance. This is a side project, with two people at most working on it, any interest or contributions will be appreciated! 
