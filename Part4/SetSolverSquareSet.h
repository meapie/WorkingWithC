#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h

// Do not add any additional classes.
#include <vector>


class SetSolverSquareSet
{
public:
    std::vector<int>set;
    /**
     * Constructor for SetSolverSquareSet
     * Initilaises the set
     * 
    */
    SetSolverSquareSet(){
        //Write your constructor here
        for(int i=1; i<=9; i++){
            set.emplace_back(i);
        }
    }
    // You can add any additional functions you'd like in order to help with the task

    /**
     * Assigns the vector to the number provided
    */
    void assign_vector(int number){
        set.clear();
        set.emplace_back(number);
    }

    /**
     * Returns the vector value
    */
    int get_value(){
        return set.back();
    }
};

#endif /* SetSolverSquareSet_h */
