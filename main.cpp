#include <iostream>
#include <exception>
#include <map>

void addToStock(std::map<std::string, int>& stock){
    std::string article;
    int quantity;
    while(true){
        std::cout << "Input article(string) and quantity(int) or 'end' to exit adding products: ";
        std::cin >> article;
        if(article == "end") break;
        try{
            std::cin >> quantity;
            if(std::cin.fail()){ 
                std::cin.clear();
                std::cin.sync();
                throw std::invalid_argument("Invalid quantity, repeat input");
            }
        }catch (const std::invalid_argument& x){
            std::cerr << "Invalid argument supplied: " << x.what() << std::endl;
        }
        stock[article] = quantity;
    }
}

int main(){
    std::map<std::string, int> stock;
    std::map<std::string, int> cart;
    addToStock(stock);
}