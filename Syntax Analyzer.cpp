#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>

int main()
{
    // Create necessary variables
    int index = 0;
    std::string myString; // used for three things
    std::vector<std::string> tokens;
    std::vector<std::string> lexemes;
    std::vector<std::string> lineNumbers;
    const std::set<std::string> terminals{ "IDENTIFIER", "INTEGER", "FLOAT", "bool", "float", "int", "+", "-", "*", "/", "=", "while", "if", "(", ")", ";", "<", ">", "<=", ">=", "==", "!=", "$" };
    std::stack<std::string> myStack; myStack.push("$"); // Initialize the stack to have the "END OF FILE" character
    std::vector<std::string> table[13][23];
    table[0][0].push_back("<Assignment>");
    table[0][3].push_back("<Declarative>");
    table[0][4].push_back("<Declarative>");
    table[0][5].push_back("<Declarative>");
    table[0][11].push_back("<While>");
    table[0][12].push_back("<If>");
    table[1][3].push_back("<Type>"); table[1][3].push_back("IDENTIFIER"); table[1][3].push_back(";");
    table[1][4].push_back("<Type>"); table[1][4].push_back("IDENTIFIER"); table[1][4].push_back(";");
    table[1][5].push_back("<Type>"); table[1][5].push_back("IDENTIFIER"); table[1][5].push_back(";");
    table[2][0].push_back("IDENTIFIER"); table[2][0].push_back("="); table[2][0].push_back("<Expression>"); table[2][0].push_back(";");
    table[3][11].push_back("while"); table[3][11].push_back("("); table[3][11].push_back("<Condition>"); table[3][11].push_back(")"); table[3][11].push_back("<Assignment>");
    table[4][12].push_back("if"); table[4][12].push_back("("); table[4][12].push_back("<Condition>"); table[4][12].push_back(")"); table[4][12].push_back("<Assignment>");
    table[5][0].push_back("<Expression>"); table[5][0].push_back("<Conditional Operator>"); table[5][0].push_back("<Expression>");
    table[5][1].push_back("<Expression>"); table[5][1].push_back("<Conditional Operator>"); table[5][1].push_back("<Expression>");
    table[5][2].push_back("<Expression>"); table[5][2].push_back("<Conditional Operator>"); table[5][2].push_back("<Expression>");
    table[5][13].push_back("<Expression>"); table[5][13].push_back("<Conditional Operator>"); table[5][13].push_back("<Expression>");
    table[6][0].push_back("<Term>"); table[6][0].push_back("<Expression'>");
    table[6][1].push_back("<Term>"); table[6][1].push_back("<Expression'>");
    table[6][2].push_back("<Term>"); table[6][2].push_back("<Expression'>");
    table[6][13].push_back("<Term>"); table[6][13].push_back("<Expression'>");
    table[7][6].push_back("+"); table[7][6].push_back("<Term>"); table[7][6].push_back("<Expression'>");
    table[7][7].push_back("-"); table[7][7].push_back("<Term>"); table[7][7].push_back("<Expression'>");
    table[7][14].push_back("epsilon");
    table[7][15].push_back("epsilon");
    table[7][16].push_back("epsilon");
    table[7][17].push_back("epsilon");
    table[7][18].push_back("epsilon");
    table[7][19].push_back("epsilon");
    table[7][20].push_back("epsilon");
    table[7][21].push_back("epsilon");
    table[8][0].push_back("<Factor>"); table[8][0].push_back("<Term'>");
    table[8][1].push_back("<Factor>"); table[8][1].push_back("<Term'>");
    table[8][2].push_back("<Factor>"); table[8][2].push_back("<Term'>");
    table[8][13].push_back("<Factor>"); table[8][13].push_back("<Term'>");
    table[9][6].push_back("epsilon");
    table[9][7].push_back("epsilon");
    table[9][8].push_back("*"); table[9][8].push_back("<Factor>"); table[9][8].push_back("<Term'>");
    table[9][9].push_back("/"); table[9][9].push_back("<Factor>"); table[9][9].push_back("<Term'>");
    table[9][14].push_back("epsilon");
    table[9][15].push_back("epsilon");
    table[9][16].push_back("epsilon");
    table[9][17].push_back("epsilon");
    table[9][18].push_back("epsilon");
    table[9][19].push_back("epsilon");
    table[9][20].push_back("epsilon");
    table[9][21].push_back("epsilon");
    table[10][0].push_back("IDENTIFIER");
    table[10][1].push_back("INTEGER");
    table[10][2].push_back("FLOAT");
    table[10][13].push_back("("); table[10][13].push_back("<Expression>"); table[10][13].push_back(")");
    table[11][3].push_back("bool");
    table[11][4].push_back("float");
    table[11][5].push_back("int");
    table[12][16].push_back("<");
    table[12][17].push_back(">");
    table[12][18].push_back("<=");
    table[12][19].push_back(">=");
    table[12][20].push_back("==");
    table[12][21].push_back("!=");
    std::map<std::string, short> terminalMap;
    terminalMap["IDENTIFIER"] = 0;
    terminalMap["INTEGER"] = 1;
    terminalMap["FLOAT"] = 2;
    terminalMap["bool"] = 3;
    terminalMap["float"] = 4;
    terminalMap["int"] = 5;
    terminalMap["+"] = 6;
    terminalMap["-"] = 7;
    terminalMap["*"] = 8;
    terminalMap["/"] = 9;
    terminalMap["="] = 10;
    terminalMap["while"] = 11;
    terminalMap["if"] = 12;
    terminalMap["("] = 13;
    terminalMap[")"] = 14;
    terminalMap[";"] = 15;
    terminalMap["<"] = 16;
    terminalMap[">"] = 17;
    terminalMap["<="] = 18;
    terminalMap[">="] = 19;
    terminalMap["=="] = 20;
    terminalMap["!="] = 21;
    terminalMap["$"] = 22;
    std::map<std::string, short> nonterminalMap;
    nonterminalMap["<Start>"] = 0;
    nonterminalMap["<Declarative>"] = 1;
    nonterminalMap["<Assignment>"] = 2;
    nonterminalMap["<While>"] = 3;
    nonterminalMap["<If>"] = 4;
    nonterminalMap["<Condition>"] = 5;
    nonterminalMap["<Expression>"] = 6;
    nonterminalMap["<Expression'>"] = 7;
    nonterminalMap["<Term>"] = 8;
    nonterminalMap["<Term'>"] = 9;
    nonterminalMap["<Factor>"] = 10;
    nonterminalMap["<Type>"] = 11;
    nonterminalMap["<Conditional Operator>"] = 12;

    // Get an output file generated by the lexical analyzer to use for input
    std::cout << "Enter the name of your file: ";
    std::getline(std::cin, myString);
    std::ifstream inputFile(myString);

    // Create list of tokens and list of lexemes and a list of line numbers. A linked list or vector of triplets would be better than three separate vectors.
    inputFile >> myString >> myString >> myString >> myString; // skip over the first line in the inputFile
    while (inputFile >> myString)
    {
        tokens.push_back(myString);
        inputFile >> myString;
        lexemes.push_back(myString);
        inputFile >> myString;
        lineNumbers.push_back(myString);
    }
    tokens.push_back("END OF FILE"); lexemes.push_back("$"); lineNumbers.push_back("Last line");
    // Display the data received from the lexical analyzer
    //for (size_t index = 0; index < lexemes.size(); ++index)
    //    std::cout << tokens[index] << '\t' << lexemes[index] << '\t' << lineNumbers[index] << std::endl;

    // Begin syntactical analysis
    std::cout << "\nToken: " << tokens[index] << "\tLexeme: " << lexemes[index] << "\tLine number: " << lineNumbers[index] << std::endl;

    while (!myStack.empty())
    {
        // If the top of the stack is the end-of-file character but there's still more input, push a starting symbol on the stack
        if (myStack.top() == "$" && lexemes.size() - index > 1) myStack.push("S");

        //std::cout << "CURRENT STATUS:\n\tTop-of-the-stack: " << myStack.top() << "\n\tCurrent token: " << tokens[index] << "\n\tCurrent lexeme: " << lexemes[index] << "\n\tCurrent line number: " << lineNumbers[index] << std::endl;

        // If the top of the stack is a terminal
        if (terminals.find(myStack.top()) != terminals.end())
        {
            // If the top of the stack matches the current input token
            if (myStack.top() == tokens[index] || myStack.top() == lexemes[index])
            {
                myStack.pop(); // remove the terminal from the stack
                if (++index < lexemes.size()) std::cout << "\nToken: " << tokens[index] << "\tLexeme: " << lexemes[index] << "\tLine number: " << lineNumbers[index] << std::endl; // print the next input token
            }
            // If the terminal at the top of the stack doesn't match the current input token
            else
            {
                std::cout << "There was an error. The expected terminal was not found.\n\tCurrent token: " << tokens[index] << "\n\tCurrent lexeme: " << lexemes[index] << "\n\tCurrent line number: " << lineNumbers[index] << "\n\tExpected terminal: " << myStack.top();
                return 0;
            }
        }
        // If the top of the stack is a nonterminal
        else
        {
            // If the nonterminal at the top of the stack and the current token have a defined table entry (Subsection for <Identifier> and <Number> rules)
            if ((myStack.top() == "IDENTIFIER" || myStack.top() == "INTEGER" || myStack.top() == "FLOAT") && !table[nonterminalMap[myStack.top()]][terminalMap[tokens[index]]].empty())
            {
                myString = myStack.top(); myStack.pop(); // take the top of the stack

                    // Print the production rule to use
                std::cout << "Using production rule: " << myString << " ->";
                for (std::vector<std::string>::iterator it = table[nonterminalMap[myString]][terminalMap[tokens[index]]].begin(); it != table[nonterminalMap[myString]][terminalMap[tokens[index]]].end(); ++it)
                    std::cout << ' ' << *it;
                std::cout << std::endl;

                // Push the production rule onto the stack in reverse order
                for (std::vector<std::string>::reverse_iterator rit = table[nonterminalMap[myString]][terminalMap[tokens[index]]].rbegin(); rit != table[nonterminalMap[myString]][terminalMap[tokens[index]]].rend(); ++rit)
                    myStack.push(*rit);
            }
            // If the nonterminal at the top of the stack and the current lexeme have a defined table entry (Subsection for not <Identifier> and not <Number> rules & current token is IDENTIFIER, INTEGER, or FLOAT)
            else if (/*!(myStack.top() == "IDENTIFIER" || myStack.top() == "INTEGER" || myStack.top() == "FLOAT") && */(tokens[index] == "IDENTIFIER" || tokens[index] == "INTEGER" || tokens[index] == "FLOAT") && !table[nonterminalMap[myStack.top()]][terminalMap[tokens[index]]].empty())
            {
                myString = myStack.top(); myStack.pop();

                std::cout << "Using production rule: " << myString << " ->";
                for (std::vector<std::string>::iterator it = table[nonterminalMap[myString]][terminalMap[lexemes[index]]].begin(); it != table[nonterminalMap[myString]][terminalMap[lexemes[index]]].end(); ++it)
                    std::cout << ' ' << *it;
                std::cout << std::endl;

                // Push the production rule onto the stack in reverse order
                for (std::vector<std::string>::reverse_iterator rit = table[nonterminalMap[myString]][terminalMap[lexemes[index]]].rbegin(); rit != table[nonterminalMap[myString]][terminalMap[lexemes[index]]].rend(); ++rit)
                {
                    if (*rit != "epsilon")
                    {
                        myStack.push(*rit);
                    }
                }
            }
            // If the nonterminal at the top of the stack and the current lexeme have a defined table entry (Subsection for not <Identifier> and not <Number> rules & current token is neither IDENTIFIER, nor INTEGER, nor FLOAT)
            else if (/*!(myStack.top() == "IDENTIFIER" || myStack.top() == "INTEGER" || myStack.top() == "FLOAT") && */!(tokens[index] == "IDENTIFIER" || tokens[index] == "INTEGER" || tokens[index] == "FLOAT") && !table[nonterminalMap[myStack.top()]][terminalMap[lexemes[index]]].empty())
            {
                myString = myStack.top(); myStack.pop();


                std::cout << "Using production rule: " << myString << " ->";
                for (std::vector<std::string>::iterator it = table[nonterminalMap[myString]][terminalMap[lexemes[index]]].begin(); it != table[nonterminalMap[myString]][terminalMap[lexemes[index]]].end(); ++it)
                    std::cout << ' ' << *it;
                std::cout << std::endl;

                // Push the production rule onto the stack in reverse order
                for (std::vector<std::string>::reverse_iterator rit = table[nonterminalMap[myString]][terminalMap[lexemes[index]]].rbegin(); rit != table[nonterminalMap[myString]][terminalMap[lexemes[index]]].rend(); ++rit)
                {
                    if (*rit != "epsilon")
                    {
                        myStack.push(*rit);
                    }
                }
            }
            // The nonterminal at the top of the stack and the current token have an undefined table entry
            else
            {
                std::cout << "There was an error. The table entry for current top-of-stack and current token is undefined.\n\tCurrent token: " << tokens[index] << "\n\tCurrent lexeme: " << lexemes[index] << "\n\tCurrent line number: " << lineNumbers[index] << "\n\tCurrent top-of-stack: " << myStack.top();
                return 0;
            }
        }
    }

    // If we've gotten this far, than the file is syntactically correct.
    std::cout << "\nThe file is syntactically correct.\n";

    return 0;
}