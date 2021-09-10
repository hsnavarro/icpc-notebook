# How to use the PDF generator

## Setup (Ubuntu-20.04)

### Install Latexmk
```
sudo apt install latexmk texlive-latex-extra
```

### Install Python
```
sudo apt install python
```

### Add files to contents.txt
Follow the model:
```
[Section name]
folder/file-name.cpp  Description of the file
```
See [```notebook-generator/contents.txt```](notebook-generator/contents.txt) for examples

## Run generator
### Change to the [```notebook-generator```](notebook-generator) folder
```
cd notebook-generator
```

### Run generator command
```
python generate_pdf.py
```

# How to add tests
1. Go to the [```tests```](tests) folder
2. Select/Create appropriate folder for your tests (if you want to test a graph algorithm, create a [```graphs```](tests/graphs) folder)
3. Names should follow the pattern 
```<name of the file to test>.test<test number>.cpp```
4. Files should follow the model:
```cpp
// @problem_url: <link to the problem>

# headers, namespaces, other constants used on your code

// @include: <relative path to your code>

# rest of the code
```

## Example
Let's say I want to add tests for the code [```data-structures/bit.cpp```](data-structures/bit.cpp)

1. Create folder [```data-structures```](tests/data-structures) in [```tests```](tests)
2. Create file with name [```bit.test.cpp```](tests/data-structures/bit.test.cpp)
    * If you want do add more than one test for the same code follow the pattern ```bit.test1.cpp```, ```bit.test2.cpp```, etc
3. The file content will be like this:
```cpp
// @problem_url: https://www.spoj.com/problems/FENTREE/
#include<bits/stdc++.h>
using namespace std;

const int N = 2e6;

// @include: data-structures/bit.cpp

# rest of the code
```