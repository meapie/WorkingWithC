#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void generateRPNPermutations(std::vector<std::string>& rpnExpressions, const std::string& operators, const std::string& operands, std::string currentExpr, int numOperands) {
    if (currentExpr.size() == numOperands * 2 - 1) {
        rpnExpressions.push_back(currentExpr);
        return;
    }

    for (char op : operators) {
        for (char operand : operands) {
            generateRPNPermutations(rpnExpressions, operators, operands, currentExpr + operand + ' ', numOperands);
        }
    }
}

int main() {
    int numOperands = 4; // Change this to the number of operands you want in the RPN expressions
    std::string operators = "+-*/";
    std::string operands = "1234"; // Change this to match the number of operands

    std::vector<std::string> rpnExpressions;
    std::string currentExpr;

    generateRPNPermutations(rpnExpressions, operators, operands, currentExpr, numOperands);

    std::cout << "All RPN Expressions with " << numOperands << " operands and operators " << operators << ":\n";
    for (const std::string& expr : rpnExpressions) {
        std::cout << expr << std::endl;
    }

    return 0;
}
