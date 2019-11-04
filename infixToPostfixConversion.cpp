#include<iostream>
#include <stack> 
#include<cstring>
using namespace std;

//Function to check whether open and close braces match
bool checkParentheses(char infix[]) {
    int open=0, close=0, i=0;
    while (infix[i] != '\0') {
        if(infix[i] == '(')
            open++;
        if(infix[i] == ')') {
            close++;
            if (close>open)
                return false;
        }
        i++;
    }
    if(open==close)
        return true;
    else
        return false;
}

bool isValid(char currentChar) {
    return ( (currentChar>=65 && currentChar<=90) || (currentChar>=97 && currentChar<=122) || (currentChar>=40 && currentChar<=43) || currentChar==45 || currentChar==47 || currentChar==94);
}


//Validate String
//Allowed: a-z, A-Z, + - * / % ^ ( )
bool validate(char infix[]) {
    int i=0;
    while (infix[i] != '\0') {
        if (! isValid(infix[i]) ) 
            return false;  
        else 
            i++;
    }

    if (checkParentheses(infix) == false) {
        return false;
    }
    return true;
}

int priorityNumber(char Operator) {
    if (Operator=='^')
        return 0;
    if (Operator=='*' || Operator=='/')
        return 1;
    if (Operator=='+' || Operator=='-') 
        return 2;
    if (Operator=='(')
        return 3;
}

bool checkPriority(char currentOperator, char topOperator) {
    if (priorityNumber(currentOperator) < priorityNumber(topOperator))
        return true;
    else 
        return false;
}

bool isOperand(char currentChar) {
    return ( (currentChar>=65 && currentChar<=90) || (currentChar>=97 && currentChar<=122) );
}

void infix2Postfix(char infix[], char answer[]) {
    int i=0, j=0;
    char currentChar;
    char postfix[50]="";
    stack<char> operatorStack; //Operator stack
    while(infix[i]!='\0') {
        currentChar=infix[i];
        if ( isOperand(currentChar) ) {
            postfix[j]=currentChar;
            j++;
        }
        else  { //It is operator
            if (currentChar=='(') {
                operatorStack.push(currentChar);
                i++;
                continue;
            }

            if(operatorStack.empty() ) { 
                if (currentChar!=')') 
                    operatorStack.push(currentChar);
            }
            else { 
                if (checkPriority(currentChar,operatorStack.top()))  {
                    //Current operator has high precedence than the one on the top of the stack
                    operatorStack.push(currentChar);
                }
                else { 
               //Current operator has equal or less precedence than the one on the top of the stack
                    while (!operatorStack.empty()) {
                        if (operatorStack.top()=='(') {
                            operatorStack.pop(); 
                            break; 
                        }
                        postfix[j]=operatorStack.top();
                        j++;
                        operatorStack.pop(); 
                    } //End of while
                    if(currentChar!=')') 
                        operatorStack.push(currentChar);
                } //End of else 
            } //End of else
        }
        i++; //Point to next character of infix expression
    }//Traversing string

    //Transfer remaining items from stack to postfix string
    while(!operatorStack.empty()) {
        postfix[j]=operatorStack.top();
        operatorStack.pop();
        j++;
    }

    strcpy(answer,postfix);

} //End of function

int main() {
    char infix[50], postfix[50];
    cout << "Enter an infix expression without space. Use round brace to indicate priority. Only +, -, *, /, ^ symbols are allowed\n";
    cin >> infix;

   //Check whether open and closing braces match or not
    if (validate(infix) == false) {
        cout << "The expression contains a number, or an unwanted symbol, or the round braces do not match\n";
        return -1;
    }

    cout << "Infix expression : " << infix << endl;

    infix2Postfix(infix,postfix);
    cout << "Postfix expression : " << postfix << endl;

   return 0;
}


/*
Sample Output

Enter an infix expression without space. Use round brace to indicate priority. Only +, -, *, /, ^ symbols are allowed
a+b
Infix expression : a+b
Postfix expression : ab+

Enter an infix expression without space. Use round brace to indicate priority. Only +, -, *, /, ^ symbols are allowed
a+b*c
Infix expression : a+b*c
Postfix expression : abc*+

Enter an infix expression without space. Use round brace to indicate priority. Only +, -, *, /, ^ symbols are allowed
a*b+c
Infix expression : a*b+c
Postfix expression : ab*c+

Enter an infix expression without space. Use round brace to indicate priority. Only +, -, *, /, ^ symbols are allowed
a*(b+c)
Infix expression : a*(b+c)
Postfix expression : abc+*

Enter an infix expression without space. Use round brace to indicate priority. Only +, -, *, /, ^ symbols are allowed
(a+b)*(a-b)
Infix expression : (a+b)*(a-b)
Postfix expression : ab+ab-*

Enter an infix expression without space. Use round brace to indicate priority. Only +, -, *, /, ^ symbols are allowed
a*(b+c*d)+e
Infix expression : a*(b+c*d)+e
Postfix expression : abcd*+*e+

Enter an infix expression without space. Use round brace to indicate priority. Only +, -, *, /, ^ symbols are allowed
(a^b*(c+(d*e)-f))/g
Infix expression : (a^b*(c+(d*e)-f))/g
Postfix expression : ab^cde*+f-*g/
*/
