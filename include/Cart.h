#ifndef CART_H
#define CART_H

#include <vector>
#include "Cart_Item.h"

using namespace std;

class Cart
{
private:
    vector<CartItem> items;

public:
    void addProduct(Product product, int quantity);

    void removeProduct(int productId);

    void updateQuantity(int productId, int newQuantity);

    long long calculateTotal() const;

    void displayCart() const;

    vector<CartItem> getItems() const;

    bool isEmpty() const;

    void clearCart();
};

#endif
