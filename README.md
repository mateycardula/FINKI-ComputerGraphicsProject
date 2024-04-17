# Procedural Dungeon Generation

Procedural generation of a dungeon and the rooms in it. The dungeon can be regenarated during runtime with different parameters such as depth, width and number of tiles in the dungeon.
This project is my final assignment for the Computer Graphics course at [Faculty of Computer Science and Engineering (FCSE)](https://www.finki.ukim.mk/en).

## Showcase


https://github.com/mateycardula/FINKI-ComputerGraphicsProject/assets/137711431/24cecbe3-4615-4c34-92b6-d818308979ca


## How to Run

This section details how to build and run the project.

### Prerequisites

Ensure you have CMake installed on your system. You can download it from the [official CMake website](https://cmake.org/download/).

### Running the project

You can simply run the .exe file under cmake-build-debug or rebuild the project using cmake.

<pre>
root
└── cmake-build-debug
    └── ProceduralGenerationFINKI.exe
</pre>


### Building the Project

Follow these steps to build the project using CMake:

1. Open a terminal or command prompt.
2. Navigate to the root directory of the project.
3. Create a new directory for the build files and enter it:
   ```bash
   mkdir cmake-build-debug
   cd cmake-build-debug
   cmake ..
   cmake --build .
