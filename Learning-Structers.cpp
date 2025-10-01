#include<iostream>
#include<string>
#include<regex>
using namespace std;

void getInput(string &question);
void validateInput(string &question);
void sortTheFirstThreeNumbers(string &question);
void resetGlobals();
float calculate();
bool isOperator(char c);

float result;
char operator_1 = '\0';
char operator_2 = '\0';

struct Number
{
    float value;
    string str_value = "";    
    bool complete = false;
}num_1, num_2, num_3;

int main()
{
    while (true)
    {
    system("cls");
    string question;    
    cout << "This program calculates simple math questions with up to three numbers and two operators." << endl;
    cout << "The supported operators are: +, -, *, /" << endl;
    getInput(question);
    system("cls");
    cout << "Question: " << question << endl;
    cout << "Result: " << result << endl;
    system("pause");    
    }
    return 0;
}

void getInput(string &question)
{
    resetGlobals();
    cout << "Input a question: ";
    cin >> question;
    if (question == "exit") exit(0);

    // Removing all whitespace and letters
    question = std::regex_replace(question, std::regex("\\s"), "");
    cout << "question after [regex]: " << question << endl;
    validateInput(question);
}

void validateInput(string &question)
{
    if (question.empty())
    {
        cout << "You didn't input anything!" << endl;
        getInput(question);
        return;
    }

    // Checking if the first letter is invalid
    if (question[0] == '+' || question[0] == '*' || question[0] == '/')
    {
        cout << "The first letter [" << question[0] << "] is invalid!" << endl;
        getInput(question);
        return;
    }

    // Checking if the last letter is invalid
    if (question[question.length() - 1] == '+' || question[question.length() - 1] == '*' ||
        question[question.length() - 1] == '/')
    {
        cout << "The last letter [" << question[question.length() - 1] << "] is invalid!" << endl;
        getInput(question);
        return;
    }
    sortTheFirstThreeNumbers(question);
}

void sortTheFirstThreeNumbers(string &question)
{
    // Improved parsing: handles multi-digit and negative numbers
    int len = question.length();
    int i = 0;
    int num_count = 0;
    string curr_num = "";
    while (i < len && num_count < 3) {
        // Handle negative sign at start or after operator
        if (question[i] == '-' && (i == 0 || isOperator(question[i-1]))) {
            curr_num += '-';
            i++;
        }
        // Parse number (digits and decimal point)
        while (i < len && (isdigit(question[i]) || question[i] == '.')) {
            curr_num += question[i];
            i++;
        }
        if (!curr_num.empty()) {
            if (num_count == 0) {
                num_1.str_value = curr_num;
                num_1.complete = true;
            } else if (num_count == 1) {
                num_2.str_value = curr_num;
                num_2.complete = true;
            } else if (num_count == 2) {
                num_3.str_value = curr_num;
                num_3.complete = true;
            }
            curr_num = "";
            num_count++;
        }
        // Parse operator
        if (i < len && isOperator(question[i])) {
            if (operator_1 == '\0') {
                operator_1 = question[i];
            } else if (operator_2 == '\0') {
                operator_2 = question[i];
            }
            i++;
        }
    }
    result = calculate();
}
void resetGlobals()
{
    result = 0.0f;
    operator_1 = '\0';
    operator_2 = '\0';
    num_1 = Number();
    num_2 = Number();
    num_3 = Number();
}

float calculate()
{
    // If the user entered one number only
    if (operator_1 == '\0') return std::stof(num_1.str_value);
    
    // If the user entered two numbers
    else if (operator_2 == '\0')
    {
        num_1.value = std::stof(num_1.str_value);
        num_2.value = std::stof(num_2.str_value);
        switch (operator_1)
        {
            case '+' : 
            num_1.value = num_1.value + num_2.value;
            operator_1 = '\0';
            num_2.complete = false;
            num_2.str_value = "";
            return num_1.value;    
            break;
  
            case '-' : 
            num_1.value = num_1.value - num_2.value;
            operator_1 = '\0';
            num_2.complete = false;
            num_2.str_value = "";
            return num_1.value;    
            break;

            case '*' : 
            num_1.value = num_1.value * num_2.value;
            operator_1 = '\0';
            num_2.complete = false;
            num_2.str_value = "";
            return num_1.value;    
            break;

            case '/' : 
            if (num_2.value != 0)
            {                
            num_1.value = num_1.value / num_2.value;
            operator_1 = '\0';
            num_2.complete = false;
            num_2.str_value = "";
            return num_1.value;   
            }
            else
            {
                cout << "Division by zero is not allowed!" << endl;
                exit(0);
            }            
            break;  
        }        
    }    
    
    // The program will do the multiplication before the addition
    else if ((operator_1 == '+' || operator_1 == '-') && (operator_2 == '*' || operator_2 == '/'))
    {
        num_1.value = std::stof(num_1.str_value);
        num_2.value = std::stof(num_2.str_value);
        num_3.value = std::stof(num_3.str_value); 
        switch (operator_2)
        {
            case '*' : 
            num_2.value = num_2.value * num_3.value;            
            break;
  
            case '/' : 
            num_2.value = num_2.value / num_3.value;
            break;            
        }

            operator_2 = '\0';
            num_3.complete = false;
            num_3.str_value = "";

        switch (operator_1)
        {
            case '+' : 
            num_1.value = num_1.value + num_2.value;
            break;
  
            case '-' : 
            num_1.value = num_1.value - num_2.value;
            break;            
        }    
        
            operator_1 = '\0';
            num_2.complete = false;
            num_2.str_value = "";      

        return num_1.value;
    }

    // The program will calculate sequentially
    else 
    {
        num_1.value = std::stof(num_1.str_value);
        num_2.value = std::stof(num_2.str_value);
        num_3.value = std::stof(num_3.str_value); 
        //cout << "Calculating sequentially..." << endl;
        switch (operator_1)
        {
            case '+' : 
            num_1.value = num_1.value + num_2.value;            
            break;
  
            case '-' : 
            num_1.value = num_1.value - num_2.value;            
            break;

            case '*' : 
            num_1.value = num_1.value * num_2.value;            
            break;

            case '/' : 
            if (num_2.value != 0)
            num_1.value = num_1.value / num_2.value;
            else 
            {
                cout << "Division by zero is not allowed!" << endl;
                exit(0);
            }
            break;  
        }    
            num_2.value = num_3.value;
            num_3.complete = false;
            num_3.str_value = "";
            operator_1 = operator_2;
            operator_2 = '\0';

        switch (operator_1) 
        {
            case '+' : 
            num_1.value = num_1.value + num_2.value;                
            break;
  
            case '-' : 
            num_1.value = num_1.value - num_2.value;    
            break;

            case '*' : 
            num_1.value = num_1.value * num_2.value;    
            break;

            case '/' : 
            if (num_2.value != 0)
            num_1.value = num_1.value / num_2.value;
            else 
            {
                cout << "Division by zero is not allowed!" << endl;
                exit(0);
            }
            break;  
        }
        num_2.complete = false;
        num_2.str_value = "";
        operator_1 = '\0';
        return num_1.value;
    }
    return 0;
}

bool isOperator(char c) 
{
    if (c == '+' || c == '-' || c == '*' || c == '/') return true;
    else return false;
}