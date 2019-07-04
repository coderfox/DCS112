# [algorithm]ISBN

Practically every book that has been published during the past thirty years can be uniquely identified by its International Standard Book Number (ISBN). An example of an ISBN is 
963-10-0604-2. 
* An ISBN has 13 characters. 
* Exactly three of the 13 characters are hyphens. 
 *		The first (leftmost) character of the ISBN is not a hyphen. 
 *		The next-to-last character of the ISBN is a hyphen. 
 *  	No two hyphens occupy adjacent positions. 
* The last (rightmost) character is either a decimal digit (0..9) or an upper case X. 
* The nine characters which are not in the rightmost position and are not hyphens are decimal digits.
 
The rightmost character is known as the check digit. It can actually be calculated from the other digits, according to the following steps (as each step is stated, it will be illustrated using the example 963-10-0604-2). 

 1. Assign numbers 10,9,8,... as the respective "weights" to the first, second, third, ... digit:
  ```
	 Digit  9  6 3 1 0 0 6 0 4 
	 Weight 10 9 8 7 6 5 4 3 2
  ```
 
 2. Calculate the weighted sum by adding the products obtained by multiplying each of the first nine digits by its weight: 
```
10*9+ 9*6 + 8*3 + 7*1 + 6*0 + 5*0 + 4*6 + 3*0 + 2*4 = 207. 
```
 3. The check digit is the smallest non-negative number that can be added to the weighted sum in order to get a number that is divisible by 11. The check digit is always in the range 0..10. If it is equal to 10, we denote it by an upper case X. In the given example, the check digit is 2, because 207 + 2 = 209, which is divisible by 11.
## Input
The input file will contain one or more lines. The First Line is time which mean the number of ISBN. Next Each line will contain the first 11 characters of an ISBN, starting in column 1. The input will not contain any white spaces, except for the end-of-line characters.
## Output
In the output, each incomplete ISBN from the input will be completed: the third hyphen and the check digit will have been added. The output will contain one ISBN per line, starting at column 1.
## Sample Input
```
4
0-07-109219
0-534-95054
963-10-0604
1-890880-01
```
## Sample Ouput
```
0-07-109219-6
0-534-95054-X
963-10-0604-2
1-890880-01-9
```
