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

void mapOut(const std::map<std::string, int>& outMap){
    for(auto it = outMap.begin(); it != outMap.end(); ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }
}

void addToCart(std::map<std::string, int>& stock, std::map<std::string, int>& cart){
    std::string article;
    std::cout << "Input the article to add to the cart: ";
    std::cin >> article;
    if(stock.find(article) == stock.end()){
        throw std::invalid_argument("The article was not found in the store!");
    }
    if(stock.find(article)->second <= 0){
        throw std::invalid_argument("The product ran out in the store!");
    }
    int quantity;


}



int main(){
    std::map<std::string, int> stock;
    std::map<std::string, int> cart;
    addToStock(stock);
    mapOut(stock);
    try{
        addToCart(stock, cart);
    }catch (const std::invalid_argument& x){
        std::cerr << "Invalid argument supplied: " << x.what() << std::endl;
    }

}