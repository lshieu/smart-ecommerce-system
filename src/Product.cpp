#include "../include/Product.h"

#include <iomanip>
#include <sstream>

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

Product::Product()
{
    id = 0;
    name = "";
    category = "";
    color = "";
    price = 0;
    stock = 0;
    totalViews = 0;
    totalSold = 0;
}

Product::Product(
    int id,
    string name,
    string category,
    string color,
    long long price,
    int stock,
    int totalViews,
    int totalSold)
{
    this->id = id;
    this->name = name;
    this->category = category;
    this->color = color;
    this->price = price;
    this->stock = stock;
    this->totalViews = totalViews;
    this->totalSold = totalSold;
}

void Product::display() const
{
    cout << "\n========== PRODUCT DETAILS ==========\n";
    cout << left << setw(16) << "Product ID:" << id << '\n';
    cout << left << setw(16) << "Name:" << name << '\n';
    cout << left << setw(16) << "Category:" << category << '\n';
    cout << left << setw(16) << "Color:" << color << '\n';
    cout << left << setw(16) << "Price:" << formatMoney(price) << '\n';
    cout << left << setw(16) << "Stock:" << stock << " item(s)\n";
    cout << left << setw(16) << "Views:" << totalViews << '\n';
    cout << left << setw(16) << "Units sold:" << totalSold << '\n';
    cout << "=====================================\n";
}

int Product::getId() const
{
    return id;
}

string Product::getName() const
{
    return name;
}

string Product::getCategory() const
{
    return category;
}

string Product::getColor() const
{
    return color;
}

long long Product::getPrice() const
{
    return price;
}

int Product::getStock() const
{
    return stock;
}

int Product::getTotalViews() const
{
    return totalViews;
}

int Product::getTotalSold() const
{
    return totalSold;
}

void Product::setStock(int stock)
{
    this->stock = stock;
}

void Product::increaseView()
{
    totalViews++;
}

void Product::increaseSold(int quantity)
{
    totalSold += quantity;
}
