#include <iostream>
#include <stdexcept>

using namespace std;

void f() {
    cout << "Throw" << endl;
    throw 42;

}

double d(int a, int b) {
    if(b == 0)
        throw std::logic_error("division by zero");

    return (double)a/b;
}

int main() {

    try{
        cout << "division result: " << d(10, 3);
        //f();
    }
    catch(const std::logic_error& e) {
           cout << "catch:" << e.what() << endl;

    }



    return 0;
}