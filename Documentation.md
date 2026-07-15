# Documentation

## Comments and Whitespace
In Tortilla, all whitespace is ignored. 
You could write your entire program in one line if you wanted to.
Spaces are needed between multiple words, but not next to operators.

* Single-Line Comments start with #
* Multi-Line Comments begin and end with ##


```
##This is a comment ## 
int a += 3 # This is too

# This whole ## line is # a comment
## So is # this # one ##
```

## Data Types
In Tortilla, there are 7 basic types:
|Type |Size |Default/Null|
|---|---|---|
|int  |32 Bits |0
|float  |32 Bits |0.0
|bigInt  |64 Bits |0
|doub  |64 Bits |0.0
|char  |8 Bits |""
|bool  |1 Bit |false
|null  | |null

There are also 3 collection types, talked about later:
- Arrays (Including Strings)
- Dictionaries
- Sets

## Variables and Assignment
To create a basic variable, follow this formula: DataType Name = Value
```
int num1 = 5
float num2 = 6.2
char letter = "B"
bool coin = false
null nothing = null
```
A variable may also be created without defining it:
```
int num3
```
An undefined variable is equal to null. When null is used in an operation, it casts itself to the datatype of the operation:
```
int num3   #This equals null
int output = num3 + 5   #num3 becomes 0, the default int value, in this equation
```
The null values of every datatype are told in the table seen earlier. The null value of any collection type is an empty collection.

To Do: 
Types
Strings
Operators
Type Conversion
Arrays
Dicts
Property Calling
Sets
While
For
ForEach
If
Switch, Also
Errors
Try/Catch
Break
Functions
Return and Scope
Classes
Concurrency
Imports
