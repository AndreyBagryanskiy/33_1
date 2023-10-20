#include <iostream>
#include <exception>
#include <string>
#include <map>

#define MAP std::map<std::string, int>

void addToStock(MAP& stock){
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

void mapOut(const MAP& outMap){
    for(auto it = outMap.begin(); it != outMap.end(); ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }
}

void addToCart(MAP& stock, MAP& cart){
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
    std::cout << "Input the quantity to add to the cart: ";
    std::cin >> quantity;
    if(std::cin.fail() || quantity <= 0){ 
        std::cin.clear();
        std::cin.sync();
        throw std::invalid_argument("Invalid quantity, repeat input");
    }
    if(quantity > (stock.find(article)->second)){
        std::cout << "Available to order only " << stock.find(article)->second << " piece." << std::endl;
        std::cout << stock.find(article)->second << " products were added to the cart." << std::endl;
        if(cart.find(article) == cart.end()){
            cart[article] = stock.find(article)->second;
        }else{
        cart[article]+= stock.find(article)->second;     
        }
        stock[article] = 0;
    }else{
        stock[article] -= quantity;
        if(cart.find(article) == cart.end()) cart[article] = 0;
        cart[article] += quantity;
    }
}

void removeToCart(MAP& stock, MAP& cart){
    std::string article;
    std::cout << "Input the article to remove from cart: ";
    std::cin >> article;
    if(cart.find(article) == cart.end()){
        throw std::invalid_argument("The article was not in the cart!");
    }
    if(cart.find(article)->second <= 0){
        cart.erase(cart.find(article));
        throw std::invalid_argument("The article was not in the cart!");
    }
    int quantity;
    std::cout << "Input the quantity to remove from cart: ";
    std::cin >> quantity;
    if(std::cin.fail() || quantity <= 0){ 
        std::cin.clear();
        std::cin.sync();
        throw std::invalid_argument("Invalid quantity, repeat input");
    }
    if(quantity > (cart.find(article)->second)){
        std::cout << "In cart have only" << cart.find(article)->second << " pieces this article." << std::endl;
        std::cout << cart.find(article)->second << " products were removed to the cart." << std::endl;
        stock.find(article)->second +=cart.find(article)->second;
        cart.find(article)->second-= cart.find(article)->second;
        if(cart.find(article)->second <= 0) cart.erase(cart.find(article));
    }else{
        stock.find(article)->second +=quantity;
        cart.find(article)->second-= quantity;
    }

}



int main(){
    std::map<std::string, int> stock;
    std::map<std::string, int> cart;
    addToStock(stock);
    std::string command;
    while(true){
        std::cout << "Atricle in stock: " << std::endl; 
        mapOut(stock);
        std::cout << "Input command ('add', 'remove', or 'exit'):";
        std::cin >> command;
        if(command == "exit")break;
        if(command == "add"){
            try{
                addToCart(stock, cart);
            }catch (const std::invalid_argument& x){
                std::cerr << "Invalid argument supplied: " << x.what() << std::endl;
            }
            std::cout << "Atricle in cart: " << std::endl; 
            mapOut(cart);
        }else if(command == "remove"){
            try{
                removeToCart(stock, cart);
            }catch (const std::invalid_argument& x){
                std::cerr << "Invalid argument supplied: " << x.what() << std::endl;
            }
            std::cout << "Atricle in cart: " << std::endl; 
            mapOut(cart);            
        }else{
            std::cout << "Bad command! Repeat input!" << std::endl;
        }
    }
}