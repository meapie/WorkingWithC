#ifndef COUNTDOWN_H
#define COUNTDOWN_H
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
#include <vector>
using std::vector;

string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}
class CountdownSolution {
  
private:
    string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};
// Do not edit above this line
// TODO: write code here:


//Boolean value for if a solution has been found
bool foundSolution;

//The final rpn expression
string finalRPN;

//The final solution
double solution;

//The difference for if the solution cannot be reached
double diff;
/**
 * Evaluates a given rpn expression 
*/
double evaluateCountdown (const string & input) {
    vector<double> numberStack;
    bool first = true;
    double total = 0;
    vector<string> tokens;
    istringstream iss(input);
    string token;
    while (std::getline(iss, token, ' ')){
        tokens.push_back(token);
    }
    for(const string& str:tokens) {
        if(str == ""){
            //do nothing
        }else if(str == "-"){
            total = total - numberStack.back();
            numberStack.pop_back();
        }else if(str == "+"){
            total = total + numberStack.back();
            numberStack.pop_back();
        }else if(str == "/"){
            total = total / numberStack.back();
            numberStack.pop_back();
        }else if(str == "*"){
            total = total * numberStack.back();
            numberStack.pop_back();
        }else{
            numberStack.push_back(std::stod(str));
            if(first){
                total = numberStack.back();
                numberStack.pop_back();
                first = false;
            }
        }
    }
    return total;
}

/**
 * Creates the rpn expression
*/
void createRpn(const vector<string> & signs, const vector<string> & numbers, const int target){
    string rpn = numbers[0]; //Add the first number to thr rpn
    //Adds all the signs and numbers in alternating pattern
    for(int i=0; i<signs.size(); i++){
        rpn = rpn + + " " + numbers[i+1];
        rpn = rpn + " " + signs[i];
    }
    double countdown = evaluateCountdown(rpn); //Find the countdown value
    if(countdown == target){
        solution = target;
        finalRPN = rpn;
        foundSolution = true;
    }
    //Finding the closest solution
    else if(countdown > 0){
        int tempDiff = target - countdown;
        if (tempDiff < 0){
            tempDiff = tempDiff * -1;
        }
        if(tempDiff< diff){
            diff = tempDiff;
            finalRPN = rpn;
            solution = countdown;
        }
    }
};

/**
 * Generates all sign permutations for a given length
*/
void generate_sign_perms(const vector<string> & signs, int size, const vector<string> & nums, const int target){
    int length = signs.size();
    vector<int> indicies(size, 0);
    vector<string> current(size, "");

    for (int i = 0; i < size; ++i) {
        
        indicies[i] = 0;
        current[i] = signs[0];

    }

    while(true) {

        //Making sure that the number of signs is one less than the numbers
        if(current.size() == nums.size() -1){
            createRpn(current, nums, target);
            if (foundSolution){
                return;
            }
        }

        int i = size -1;
        while ( i >= 0 && ++indicies[i] == length){
            indicies[i] = 0;
            current[i] = signs[0];
            --i;
        }

        if (i<0) {
            break;
        }

        current[i] = signs[indicies[i]];
    }
}

/**
 * Generates all number permutations recursively for a given length
*/
void numberPermutations(vector<int> & input, vector<string> & current, vector<bool> & full, int length, const int target){
    if(length == 0){
        vector<string> signs = {"+", "-", "/", "*"};
        generate_sign_perms(signs, current.size()-1,current, target);
        if (foundSolution){
            return;
        }
        return;
    }
    for(int i=0; i<input.size(); i++){
        if(!full[i]){
            current.push_back(intToString(input[i]));
            full[i] = true;
            numberPermutations(input, current, full, length -1, target);
            current.pop_back();
            full[i] = false;
        }
    }
}

/**
 * Starting point to find the solution
*/
CountdownSolution solveCountdownProblem(vector<int> & numbers, const int target)
{
    foundSolution = false;
    solution = 0;
    finalRPN = "";
    diff = 100;

    vector<string> current;
    vector<bool> full(numbers.size(), false);
    for(int length = 1; length<=numbers.size(); length++){
        numberPermutations(numbers, current, full, length, target);
    }
    return CountdownSolution(finalRPN, solution);
}

// Do not edit below this line
#endif