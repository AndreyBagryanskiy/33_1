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
        throw std::invalid_argument(apples < 0 ? "aplles": "count");
    }
    return divide(apples, count);
}

int main(){
    int apples;
    int count;
    bool input  = true;
    while(input){
        std::cin >> apples >> count ;

        try{
            std::cout << "Apples: " << distribute(apples, count) << std::endl;
            input = false;
        }catch (const DivisionByZeroException& x){
            input = false;
        }catch (const std::invalid_argument& x){
            std::cerr << "Invalid argument supplied: " << x.what() << std::endl;
        }
    }
}