#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <memory>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;
//do not add additional libraries

class SetSolver
{
private:
    int boardSize = 9;
    vector<vector<SetSolverSquareSet>>board;
    
public:

/**
 * Constructor for SetSolver
 * Initialises the board
*/
SetSolver()
{
    //implement your code here
    board = std::vector<std::vector<SetSolverSquareSet>>(boardSize, std::vector<SetSolverSquareSet>(boardSize, SetSolverSquareSet()));
}

/**
 * Populate the board
*/
void PopulateBoard(const std::vector<std::string> & skeletonBoard) {
    for (size_t row = 0; row < skeletonBoard.size(); row++) {
        size_t actualColumn = 0;  // Initialize actualColumn for each row
        for (size_t column = 0; column < skeletonBoard[row].length(); column++) {
            char current = skeletonBoard[row][column];
            if (current == '0') {
                board[row][actualColumn].assign_vector(0);
            } else if (current == '-') {
                if (column + 1 < skeletonBoard[row].length()) {
                    std::string temp = std::string(1, current) + skeletonBoard[row][column + 1];
                    int integer = convertToInt(temp);
                    if (integer == 0) {
                        return;
                    } else {
                        board[row][actualColumn].assign_vector(integer);
                        column++;  // Skip the next character since it's part of the number
                    }
                } else {
                    return;
                }
            } else if (current == '*') {
                board[row][actualColumn].assign_vector(99);
            } else {
                std::string charAsString(1, current);
                int integer = convertToInt(charAsString);
                if (integer == 0) {
                    return;
                } else {
                    board[row][actualColumn].assign_vector(integer);
                }
            }
            actualColumn++;  // Increment column position within the row
        }
    }
}

/**
 * Convert the string into a integer
 * Return the integer
*/
int convertToInt(string input){
    try{
        return std::stoi(input);
    }catch (const std::invalid_argument & e){
        std::cerr<<"Invalid arguement: " <<e.what() << "\n";
    } catch (const std::out_of_range & e){
        std::cerr << "Out of range: "<< e.what()<<"\n";
    }

    return 0;
}

/**
 * Return the value of the given cell
*/
int ReturnValue(const size_t row, const size_t col)
{
    return board[row][col].get_value();
}

/**
 * Check if the number is present in the nums vector
 * If yes return false else return true
*/
bool checkLoop(const vector<int> & nums, const int num) const{
    for(int n: nums){
        if(n == num){
            return false;
        }
    }
    return true;
}

/**
 * Finds if the number is within the range
*/
bool find_range(const vector<int> & nums, const int row, const int column, const int available, const int num) const{
    int count = 0;
    if(nums.size() > 0){
        int min = 9;
        int max = 1;
        for(int n : nums){
            if(n >= max){
                max = n;
            }
            if(n <= min){
                min = n;
            }
        }
        int temp = min;
        while(count != available){
            temp++;
            if(temp >9){
                break;
            }else if(checkLoop(nums, temp)){
                if(temp == num){
                    return true;
                }
                count++;
            }
        }
        temp = max;
        count = 0;
        while(count != available){
            temp--;
            if(temp < 1){
                break;
            }else if(checkLoop(nums, temp)){
                count++;
                if(temp == num){
                    return true;
                }
            }
        }
        return false;
    }
    else{
        return true;
    }
}

/**
 * Checks horizontal compartment
*/
bool checkHorizontalComp(const int row, const int column, const int num){
    int currentColumn = column;
    int available = 1;
    int current = board[row][column].get_value();
    vector<int> numbers;

    //Checks the indexes above the current index
    while(current > 0 && currentColumn < 8){
        currentColumn++;
        current = board[row][currentColumn].get_value();
        if(current <= 0){
            break;
        }else if(current == 99){
            available++;
        }else if(current > 0){
            numbers.push_back(current);
        }
    }
    currentColumn = column;
    current = board[row][currentColumn].get_value();

    //Checks the indexes below the current index
    while(current > 0 && currentColumn > 0){
        currentColumn--;
        current = board[row][currentColumn].get_value();
        if(current <= 0){
            break;
        }else if(current == 99){
            available++;
        }else if(current > 0){
            numbers.push_back(current);
        }
    }
    return find_range(numbers, row, column, available, num);

}

/**
 * Checks the vertical compartment
*/
bool checkVerticalComp(const int row, const int column, const int num){
    int currentRow = row;
    int available = 1;
    int current = board[row][column].get_value();
    vector<int> numbers;

    //Checks the indexes above the current index
    while(current > 0 && currentRow < 8){
        currentRow++;
        current = board[currentRow][column].get_value();
        if(current <= 0){
            break;
        }else if(current == 99){
            available++;
        }else if(current > 0){
            numbers.push_back(current);
        }
    }
    currentRow = row;
    current = board[currentRow][column].get_value();
    //Checks the indexes below the current index
    while(current > 0 && currentRow > 0){
        currentRow--;
        current = board[currentRow][column].get_value();
        if(current <= 0){
            break;
        }else if(current == 99){
            available++;
        }else if(current > 0){
            numbers.push_back(current);
        }
    }
    return find_range(numbers, row, column, available, num);
}

/**
 * Checks the row
 * 
*/
bool checkRow(const int row, const int num){
    for(int column=0; column<board[row].size(); column++){
        if(num == board[row][column].get_value() || num == (board[row][column].get_value()) * -1){
            return false;
        }
    }
    return true;
}

/**
 * Checks the column
*/
bool checkColumn(const int column, const int num){
    for(int row = 0; row<9; row++){
        if(num == board[row][column].get_value() || num == (board[row][column].get_value()) * -1){
            return false;
        }
    }
    return true;
}

    

bool solve_problem(){
    for(int row=0; row<board.size(); row++){
        for(int column=0; column<board[row].size(); column++){
            int current = board[row][column].get_value();
            if(current == 99){
                for(int i=1; i<10; i++){
                    if(checkRow(row, i) && checkColumn(column, i) && checkHorizontalComp(row, column, i) && checkVerticalComp(row, column, i)){
                        board[row][column].assign_vector(i);

                        if(solve_problem()){
                            return true;
                        }

                        board[row][column].assign_vector(99);
                    }
                }
                return false;
            }
        }
    }
    return true;
}

/**
 * Main method
*/
void Solve()
{
    //Added
    solve_problem();
}
//Don't edit below this line    
    
};
#endif /* SetSolver_h */
;