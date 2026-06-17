#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include "Product_Manager.h"
#include "Cart.h"

class Customer
{
private:
    string name ;
    Cart cart;

public:
    Customer();
    Customer(string name);
    string getName() const;
    void browseProducts(ProductManager& pm);

    void addProductToCart(ProductManager& pm);

    void viewCart();

    void updateQuantity();

    void removeProduct();

    void customerMenu(ProductManager& pm);
    void checkout(ProductManager& pm);
    void receiveRecommendations(ProductManager& pm);
};

#endif