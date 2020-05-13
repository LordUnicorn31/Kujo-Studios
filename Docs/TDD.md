Introduction:

In this document we will disscus the technical specifications about the game. Our game will be a 2d RTS and it will be rendered on an
orthoganal prespective. It is writen entirely on C++ language and we will also use external libraries writen in C. (missing lisences)

Technicla Goals:

- Run the game at 60 fps

- Random generated map

- 2D orthogonal map renderization

- Ui (minimap,settings...)

- Entity system

- Opponent Ia

Performance budgets:

- We can't target x64 platforms because we can't build a x64 png library

Branching:

We will comit everything on the master branch.

Tools to develop:

- Visual studio 2019

- Tiled

- Photoshop and paint

- External libraries: eastl, puguixml, SDL (and extensions)

Game mechanics implementation:

- Random map:...

Code style:

single variable:	`speed`

multiple variable:	`playerSpeed`

Enums: `EN_MAJUSCULA_TOT`

enum Input: 
`INPUT_UP`

enum UI: 
`UI_NONE`

Functions:
`MyFunction()`

Names representing a collection of numbers must be in plural

Bool variables should use the is prefix:	`isOpen`

File content must be kept within 160 columns. If you need more columns split the code onto 2 or more lines. Keep in easy to read.

Should be grouped by their hierarchical position in the system with low levels files first. Leave an empty line between groups of include statements.

If the variable is a number, use `i`, (and `j`, `k` for nested loops):

If iterators, increase/decrease by one unit use the operator on the right

`i++`

Else, increase/decrease them on the right `variable++`/`variable--`.

`speed++`

Whitespace: VisualStudio's default whitespace

Parenthesis: We use them to clarify difficult operations but not needed everywhere if the operation is easily readable

`a += b;`

ternary operators can be used if the condiltion is very simple and can be deduced by one glance

Add one blank line between each logical block of code.

block of code comment 
```
/* This is a really long
block of comment */
```

line comment only `// This is a single-line comment`


Never use magic numbers

If we have to declare more than one variable of the same type without initialazing them declare them in the same line.

`int i, j, k, l;`

Use the keyword nullptr for null pointers `char* name = nullptr;`

Floating numbers must use the extension .(value)f.

`float speed = 0.0f;`

Booleans must be initialized with true or false.

`bool isChild = true/false`

should have their reference symbol next to the type rather than to the name.

`char* name = nullptr;` (VisualStudio's default)

```
if()
{
}
```

Classes:

It is preferred to use private (or protected) variables and access functions instead of public variables, which violate the encapsulation concept (hiding information).
Structs:

It is preferred to use global variables.

Use the while(true) form
while (true)

the conditional should be put on a separate line using TAB
```
if (isOpen)
	Close()
```

If there is only one sentence after the if-else statement, don’t use brackets.
```
if (isOpen)
	Close()
else
	Open()
```

Classes and structs
Use a struct when the class is essentially a data structure.

Class elements must be written in this order

XML:...all info on atributes...map types etc

UML: (Entities, Ui)

Data layout:

We output everything on a bin folder on the solution directory. This bin directory will contain a game folder with the executable and all the needed dlls needed to run the executable. The bin directory also contains a library folder where all the compiled libraries will go.

We also generate an obj folder on the solution directory that will contain all the intermediate files of libraries and executable generated during the compilation and linking.

All the libraries are in the deps directory accesible from the game project directory.

Schedule:

Build delivery method:
