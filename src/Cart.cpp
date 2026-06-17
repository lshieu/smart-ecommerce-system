#include "../include/Cart.h"

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

void Cart::addProduct(Product product, int quantity)
{
    for (auto& item : items)
    {
        if (item.getProduct().getId() == product.getId())
        {
            item.setQuantity(item.getQuantity() + quantity);
            return;
        }
    }

    items.push_back(CartItem(product, quantity));
}

void Cart::removeProduct(int productId)
{
    for (int i = 0; i < static_cast<int>(items.size()); i++)
    {
        if (items[i].getProduct().getId() == productId)
        {
            items.erase(items.begin() + i);
            cout << "Product removed.\n";
            return;
        }
    }

    cout << "Product not found.\n";
}

void Cart::updateQuantity(int productId, int newQuantity)
{
    for (auto& item : items)
    {
        if (item.getProduct().getId() == productId)
        {
            item.setQuantity(newQuantity);
            cout << "Quantity updated.\n";
            return;
        }
    }

    cout << "Product not found.\n";
}

long long Cart::calculateTotal() const
{
    long long total = 0;

    for (const auto& item : items)
    {
        total += item.getSubtotal();
    }

    return total;
}

void Cart::displayCart() const
{
    cout << "\n============================= YOUR CART =============================\n";

    if (items.empty())
    {
        cout << "Cart is empty.\n";
        return;
    }

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
    cout << right << setw(61) << "TOTAL:"
         << setw(20) << formatMoney(calculateTotal())
         << '\n';
}

vector<CartItem> Cart::getItems() const
{
    return items;
}

bool Cart::isEmpty() const
{
    return items.empty();
}

void Cart::clearCart()
{
    items.clear();
}

