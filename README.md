# CSI-391-Data-Structures-Algorithms-Final-Project-Fall-2020-2021
**Welcome to the CSI-391-Data-Structures-Algorithms-Final-Project-Fall-2020-2021 wiki!**

**Assignment/Problem Description:** For this project, I will be working to build a calculator that can evaluate expressions of arbitrary length. I will be using a data structure known as a binary search tree (BST) to build this calculator. This program will only perform simple algebraic operations (+, -, *, /, %, ^) to an infix arithmetic expression that will be input by the user, without any evaluation being done. 
*Language to be used for development is C++*

**Solution/Program Description:**
The program first is supposed to request the user to enter an arithmetic expression in the infix format. Then the program builds a BST for that expression. After building the BST, a menu will be present to the user allowing him to choose between the following options:
1. Traverse the BST in in order,
2. Traverse the BST in post order,
3. Traverse the BST in preorder.

After the user chooses among the options present, the result will be the display of the original arithmetic expression and the new one that depends on the option chosen.

**Major Implementation Issue:** The most difficult part of the program is when writing the algorithm to construct an expression tree from the typical infix expression syntax given above.

**Solution:** For simplicity, I decided to implement a function that changes the expression from infix to one that is known as postfix notation (also known as Reverse Polish Notation(RPN)); by that, it is not necessary now to wirte an algorithm that constructs a BST from the infix notation.
