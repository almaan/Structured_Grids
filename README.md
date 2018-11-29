# SF2565 Project 3 HT18P2 Alma Andersson
Source code for construction of four sided clodes domains
over which a grid is generated using the "Algebraic Grid Generation" formula.

## Instructions for usage on Linux systems
Best way to run the program is accordingly

### 1. Clone repository
```bash
cd YOUR_FAVORITE_DIRECTORY
git clone https://github.com/almaan/Structured_Grids.git
```

### 2. Compile source code
```bash
cd YOUR_FAVORITE_DIRECTORY/Structured_Grids
mkdir res
cd bin
g++ *.{.cpp,.h} -o main.o -std=c++11
```

### 3. Run main program
```bash
./main.o<<EOF
normal_grid.bin
adjusted_grid.bin
EOF
```

### 4. Visualize Results (Non adjusted resolution)
```bash
cd ../
chmod +x visual.py
./visual.py res/x_vec_normal_grid.bin res/y_vec_normal_grid.bin
```

