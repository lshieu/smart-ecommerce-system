#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "Cart_Item.h"

using namespace std;

class Order
{
private:
    int orderId;
    string customerName;
    vector<CartItem> items;
    long long totalPrice;

public:
    Order();

    Order(
        int orderId,
        string customerName,
        vector<CartItem> items,
        long long totalPrice
    );

    int getOrderId() const;

    string getCustomerName() const;

    vector<CartItem> getItems() const;

    long long getTotalPrice() const;

    void display() const;
};

#endif
