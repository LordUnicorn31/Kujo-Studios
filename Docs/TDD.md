single variable:speed

multiple variable:playerSpeed

Enums: EN_MAJUSCULA_TOT

enum Input: 
INPUT_UP

enum UI: 
UI_NONE

Functions:

MyFunction()
Names representing a collection of numbers must be in plural
Bool variables should use the is prefix
File content must be kept within 160 columns. If you need more columns split the code onto 2 or more lines. Keep in easy to read.
Should be grouped by their hierarchical position in the system with low levels files first. Leave an empty line between groups of include statements.
If the variable is a number, use i, (and j, k for nested loops):
If iterators, increase/decrease them using ++variable/--variable.
i++
Else, increase/decrease them using variable++/variable--.
speed++
Whitespace: El automatic del visual
Parenthesis: We use them to clarify difficult operations
a += b;
ternary operators ???
Add one blank line between each logical block of code.
block of code comment /* ... */
line comment only //

Never use magic numbers
If there is more than one variable of the same type, declarate them in the same line.
int i, j, k, l
pointers amb nullptr char* name = nullptr
Floating numbers must be initialized with default 0.0f.
float speed = 0.0f
Booleans must be initialized with true or false.
bool isChild= true/false
should have their reference symbol next to the type rather than to the name.
char* name = nullptr (buscar el default del visual)

if()
{
}

Classes:

It is preferred to use private (or protected) variables and access functions instead of public variables, which violate the encapsulation concept (hiding information).
Structs:

It is preferred to use global variables.

Use the while(true) form
while (true)

the conditional should be put on a separate line
if (isOpen)
	Close() (el "tabulador")
If there is only one sentence after the if-else statement, don’t use brackets.
if (isOpen)
	Close()
else
	Open()
Classes and structs
Use a struct when the class is essentially a data structure.

Class elements must be written in this order
XML
all info on atributes
map types