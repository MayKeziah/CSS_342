//
// Created by E on 10/20/2019.
//
#include "Stack.cpp"
#include <iostream>

using namespace std;

int main(){
    Stack<int> s1;
    for (int i = 1; i < 7; i++){
        s1.push(i);
    }

    for (int i = 6; i > 0; i--){
        assert(i == s1.peek());
        s1.pop();
    }

    try{
        if(s1.isEmpty()){
            s1.peek();
        }
    } catch (logic_error e){
        cout << "All tests Passed." << endl;
    }
}