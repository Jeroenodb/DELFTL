'''
* Author: Jeroen Op de Beek
* Date: 2024-03-21
* License: CC0
* Source: me
* Description: Stresstest in python, expecting gen.py, ./brute and ./fast to be created. 
* Runs random tests until it finds a difference, and stores the test in input.in. 
* Run stress.py inside the working directory
* Status: Works on linux.
'''
from random import * # put this in gen.py
import sys
seed(int(sys.argv[1]))
# make a small test here

import os # put this in stress.py
for i in range(10**9):
    print(f"testing {i}")
    assert(os.system(f"python3 gen.py {i} > input.in")==0)
    assert(os.system("./fast < input.in > fast.out")==0)
    assert(os.system("./slow < input.in > slow.out")==0)
    assert(os.system("diff fast.out slow.out")==0)