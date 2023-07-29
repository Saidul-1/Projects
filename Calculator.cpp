#include <bits/stdc++.h>
using namespace std;

map<string, int> precedence = { 
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}
};
vector<string> tokenize(string infix){
    
    vector<string> tokens;
    int l=0, r;
    for(r = 0; r < infix.size(); r++){
        char c = infix[r];
        if(c=='(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c=='^'){
            if(r>l){
                tokens.push_back(infix.substr(l,r-l));
            }
            tokens.push_back(infix.substr(r,1));
            l = r+1;
        }
    }
    if(r>l){
        tokens.push_back(infix.substr(l,r-l));
    }
    return tokens;
}
vector<string> infixToPostfix(vector<string>&infix){
    vector<string>postfix;
    stack<string>operatorStack;
    for(int it = 0; it < infix.size(); it++){
        if(isdigit(infix[it][0])){
            postfix.push_back(infix[it]);
        }
        else if(infix[it] == "("){
            operatorStack.push(infix[it]);
        }
        else if(infix[it] == ")"){
            while(!operatorStack.empty() && operatorStack.top() != "("){
                postfix.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else if(infix[it]=="-" && (it==0 || !isdigit(infix[it-1][0]) && isdigit(infix[it+1][0]))){
            string negNumber = "-"+infix[++it];
            postfix.push_back(negNumber);
        }
        else{
            while(!operatorStack.empty() && (precedence[operatorStack.top()] >= precedence[infix[it]])){
                postfix.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(infix[it]);
        }
    }
    while(!operatorStack.empty()){
        postfix.push_back(operatorStack.top());
        operatorStack.pop();
    }
    return postfix;
}
double evaluatePostfix(vector<string>&postfix){
    double operand1, operand2;
    stack<long double>operands;
    
    for(string it: postfix){
        if(isdigit(it[it.size()-1])){
            operands.push(stod(it));
        }
        else{
            operand2 = operands.top();
            operands.pop();
            operand1 = operands.top();
            operands.pop();
            if(it == "+"){
                operands.push(operand1 + operand2);
            }
            else if(it == "-"){
                operands.push(operand1 - operand2);
            }
            else if(it == "*"){
                operands.push(operand1 * operand2);
            }
            else if(it == "/"){
                operands.push(operand1 / operand2);
            }
            else if(it == "^"){
                int sign = operand1/abs(operand1);
                operands.push(sign*pow(abs(operand1), operand2));
            }
        }
    }
    return operands.top();
}
int main()
{
    string infix;
    cout<<"Enter the infix expression:\n";
    cin>>infix;
    vector<string>tokens = tokenize(infix);
    vector<string>postfix = infixToPostfix(tokens);
    double answer = evaluatePostfix(postfix);
    cout<<infix<<" = "<<answer<<"\n";
    return 0;
}
