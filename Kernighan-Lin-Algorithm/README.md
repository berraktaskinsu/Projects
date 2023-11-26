# Kernighan-Lin-Algorithm

### Notes:

#### Running valgrind for locating memory leak checks:
- STEP 1: Download Ubuntu WSL from Microsoft Store.
- STEP 2: Install gcc and make commands (Just type make and it will display installation commands)
- STEP 3: Compile the program and run the executable with valgrind:\
`>> make`\
`>> valgrind --leak-check=yes -s ./KL`\
OR 
`>> valgrind --leak-check=full --show-leak-kinds=all -s ./KL`\
