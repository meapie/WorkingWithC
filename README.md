# WorkingWithC
All of my projects working with C++

# Part1

Solving the Countdown Numbers Game:
  Players are given six integer numbers and a a target integer number
  The six numbers should be combines and using the mathematical operators + - * and / in a way that gets as close as possible to the target number
  Each number can only be used once at most, but it is okay not to use any given number(s)
  Divisions by zero can be discarded
  For instance if the numbers (100,4,17,9,3,2) and the target is 37, then one way to do is 
  '(100 / (3 + 2)) + 17)'

# Part3

Implementing a Linked List template class without additional imports

# Part4

This is a Numbers puzzle called NumberSets which is very similar to sudoku

#The Puzzle

NumberSets is a numbers puzzle, which is very similar to Sudoku. It is played on a 9x9 board where the board is partially filled with numbers in white and black cells. The aim in this task is to fill the empty white cells with the correct numbers. White cells with numbers and all black cells (both empty and not) are blocked and mustn't be changed.
![image](https://github.com/meapie/WorkingWithC/assets/73711651/6d18c4c4-5de1-4ffa-874b-e00b0bb1e28d)

1. Rows and columns are divided into compartments.
2. A compartment is a series of uninterrupted white cells (above column F, is made up of two compartments marked in green border)
3. Each compartment needs to be filled with an unordered but uninterrupted set of numbers. That said, compartments do not necessarily need to continue each other's numbers. So the answer for column F top compartment is: (2,F) 4, (3,F) 6 and (4,F) 7 (creating an unordered but uninterrupted set of numbers: 4,6,7 and 5). Similarly the answer to column F low compartment is: (7,F) 9 creating the set of 9,8.
4. Possible numbers are 1-9
5. By uninterrupted we mean there are no gaps in the middle (e.g., 3, 1, 2 or 5, 9, 6, 8, 7).
6. The number within any given compartment can appear in any order.
7. Like Sudoku, no single number can repeat in any row or column (irrespective of compartments).

As mentioned above, a black square is a blocked square, which means that the solver cannot input a number into it. If a black square contains a number, it helps by providing a clue that this number can effectively be removed from the list of possibility for any cell in that row and column.
As an example, the board below is showing different compartments in red, purple and green. Both the red and purple squares cannot contain the number 3 as it appears in 0,F. Similar is the case for the number 1 in 0,G. It is also the case that the red compartment cannot contain the numbers 5, 6, 8 and 3 as they already appear in columns C and D (see arrows).

This process can be used to eliminate and deduce which number fits in which empty white square. Looking above at the orange compartment (8,F and 8,G) it already contains the number 8 (8,F). This means that the empty white square to its right (8,G) can only be a 7 or a 9 as a compartment can only contain uninterrupted numbers, although these can appear in any order. As such, because column G contains the numbers 1, 5, 7 and 6, it means that 7 can also be removed as possibilities, leaving 9 as the only viable option.


![image](https://github.com/meapie/WorkingWithC/assets/73711651/458591a3-8810-42d9-8d50-5e9be501f3f7)
As can be view in the above solution to the puzzle, the sequence of uninterrupted numbers only persists within a compartment. Row zero has two compartments marked in Red and Purple. Within each compartment the numbers are uninterrupted, but there is a gap between the compartments.
Representing a board in code
To represent the board, a vector of strings (vector<std::string>) will be provided in the .cpp test file. It represents an empty black square as Zero, an empty white square as an asterisk and a black square with a number as a negative of that that number. We're only using negative numbers for black squares that have numbers in order to distinguish them from a white cell with number. For example, the number 3 in row 0 (0,F) will be represented as -3 in the string. For clarity, empty white squares can only contain positive numbers 1 through to
9.
As an example, the above board will be represented in the following way:
vector<string> easyBoard =
{"00**0-31*0",
******0**0",
"7*003*-5**",
'**05**7**",
"*0**0*6-9*",
"4***650**",
"*2-8**00***
"-23*0*****"
"043-608*0-1"};

