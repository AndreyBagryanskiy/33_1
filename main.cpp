#include <iostream>
#include <exception>

class DivisionByZeroException: public std::exception{
        const char* what() const noexcept override{
            return "Division by zero";
        }
};


int divide(int dividend, int divisor){
    if(divisor == 0){
        throw DivisionByZeroException();
    }
    return dividend / divisor;
}

int distribute(int apples, int count){
    if(apples < 0 || count < 0){
        throw std::exception();
    }
    return divide(apples, count);
}

int main(){
    int apples;
    int count;
    std::cin >> apples >> count ;

    try{
        std::cout << "Apples: " << distribute(apples, count) << std::endl;
    }catch (const std::exception& x){
        std::cerr << "Caught exception: " << x.what() << std::endl;
    }
}