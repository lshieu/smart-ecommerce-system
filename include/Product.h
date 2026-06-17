#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

class Product
{
private:
    int id;
    string name;
    string category;
    string color;
    long long price;
    int stock;

    int totalViews;
    int totalSold;

public:
    Product();

    Product(
        int id,
        string name,
        string category,
        string color,
        long long price,
        int stock,
        int totalViews,
        int totalSold
    );

    void display() const;

    int getId() const;
    string getName() const;
    string getCategory() const;
    string getColor() const;
    long long getPrice() const;
    int getStock() const;
    int getTotalViews() const;
    int getTotalSold() const;

    void setStock(int stock);

    void increaseView();
    void increaseSold(int quantity);
};

#endif