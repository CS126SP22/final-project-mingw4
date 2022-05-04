# Cellular automata based forest fire simulation

## What The Project Does:

Cellular Automata resembling fire spread is first implemented, with rules: if the cell is alive, then it stays alive if it has either 2 or 3 live neighbors; if the cell is dead, then it springs to life only in the case that it has 3 live neighbors.

A forest fire simulator is built based on cellular automata. States of lattice cells are expanded to forest land, grassland, lake, river, burning, burnout. In the fire spread model, different types of areas have different properties, such as nonflammability, rapid burnup, slow combustion and so on.

You can choose from two cell-shapes: square & hexagon, in both cellular automata & forest fire simulator.

Additional interactive features including pause, stop, brush-radius adjustment, and mode change are also implemented.

## How to Set it up and run it:

### Set and Run by Cinder:

* Import the project.
* Right-click the "CMakeList.txt" file.
* Click "Load CMake Project."
* Run the tests and program via Cinder interface.

### Set and Run Manually:
* Create the "build" directory and move inside it.
```sh
mkdir build
cd build
```
* Load cmake and compile.
```sh
cmake ..
make
```
* To run the tests:
```sh
./Debug/cellular-automata-test/cellular-automata-test.app/Contents/MacOS/cellular-automata-test
```
* To run the program:
```sh
./Debug/cellular-automata/cellular-automata.app/Contents/MacOS/cellular-automata
```

