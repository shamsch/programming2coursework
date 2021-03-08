#include <iostream>

using namespace std;

void push(int addVal, int *ptr, int &top)
{
    top++;
    ptr += top;
    *ptr = addVal;
}

int pop(int *ptr, int &top, int plusMinus = 0)
{
    ptr += (top + plusMinus);
    int val = *ptr;
    top--;
    return val;
}

int main()
{
    char exp[80];
    int stack[80];
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";
    char *ptr = exp;
    char *firstExp= exp;
    int *stackPtr = stack;
    int top = -1;
    int temp;
    int operatorCounter=0,operandsCounter=0;
    cin.getline(exp, 80);
    bool divByZero=false;

    while (true)
    {

        if (*firstExp=='+' || *firstExp=='-' || *firstExp=='*' || *firstExp=='/'){
            cout<<"Error: Expression must start with a number"<<endl;
            return EXIT_FAILURE;
        }

        if (isalnum(*ptr))
        {
            push(*ptr - 48, stackPtr, top);
            operandsCounter++;
        }
        else if (*ptr == '+')
        {
            temp = pop(stackPtr, top) + pop(stackPtr, top);
            push(temp, stackPtr, top);
            operatorCounter++;
        }
        else if (*ptr == '-')
        {
            temp = pop(stackPtr, top, -1) - pop(stackPtr, top, 1);
            push(temp, stackPtr, top);
            operatorCounter++;
        }
        else if (*ptr == '*')
        {
            temp = pop(stackPtr, top) * pop(stackPtr, top);
            push(temp, stackPtr, top);
            operatorCounter++;
        }
        else if (*ptr == '/')
        {
            operatorCounter++;
            int x= pop(stackPtr, top, -1);
            int y= pop(stackPtr, top, 1);
            if(x == 0 || y == 0){
                divByZero=true;
                break;
            }
            temp = x /y ;
            push(temp, stackPtr, top);
        }
        else if (*ptr == '#')
        {
            break;
        }
        else if (*ptr == ' ')
        {
            
        }
        else{
            cout<<"Error: Unknown character"<<endl;
            return EXIT_FAILURE;
        }
        ptr+=1;
    }
    operatorCounter++;
    if (top==0){
        cout << "Correct: " << stack[top] << " is the result" << endl;
        return EXIT_SUCCESS;
    }
    else if(operatorCounter>operandsCounter){
        cout<<"Error: Too few operands"<<endl;
        return EXIT_FAILURE;
    }
    else if(operatorCounter<operandsCounter){
        cout<<"Error: Too few operators"<<endl;
        return EXIT_FAILURE;
    }
    else if(divByZero){
       cout<<"Error: Division by zero"<<endl;
       return EXIT_FAILURE;
    }
    
}
