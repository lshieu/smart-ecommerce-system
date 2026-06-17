#include "../include/Order.h"

#include <iomanip>
#include <iostream>

using namespace std;

namespace
{
string formatMoney(long long amount)
{
    string value = to_string(amount);

    for (int i = static_cast<int>(value.length()) - 3; i > 0; i -= 3)
    {
        value.insert(i, ",");
    }

    return value + " VND";
}
}

Order::Order()
{
    orderId = 0;
    customerName = "Guest";
    totalPrice = 0;
}

Order::Order(
    int orderId,
    string customerName,
    vector<CartItem> items,
    long long totalPrice)
{
    this->orderId = orderId;
    this->customerName = customerName;
    this->items = items;
    this->totalPrice = totalPrice;
}

int Order::getOrderId() const
{
    return orderId;
}

string Order::getCustomerName() const
{
    return customerName;
}

vector<CartItem> Order::getItems() const
{
    return items;
}

long long Order::getTotalPrice() const
{
    return totalPrice;
}

void Order::display() const
{
    cout << "\n=========================== ORDER SUMMARY ===========================\n";
    cout << left << setw(15) << "Order ID:" << orderId << '\n';
    cout << left << setw(15) << "Customer:" << customerName << "\n\n";

    cout << left
         << setw(6) << "ID"
         << setw(25) << "Product name"
         << right
         << setw(10) << "Quantity"
         << setw(20) << "Unit price"
         << setw(20) << "Subtotal"
         << '\n';
    cout << string(81, '-') << '\n';

    for (const auto& item : items)
    {
        const Product& product = item.getProduct();

        cout << left
             << setw(6) << product.getId()
             << setw(25) << product.getName()
             << right
             << setw(10) << item.getQuantity()
             << setw(20) << formatMoney(product.getPrice())
             << setw(20) << formatMoney(item.getSubtotal())
             << '\n';
    }

    cout << string(81, '-') << '\n';
    cout << right << setw(61) << "TOTAL PRICE:"
         << setw(20) << formatMoney(totalPrice)
         << '\n';
}
