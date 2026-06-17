#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <vector>
#include "Product.h"

using namespace std;

class ProductManager
{
private:
    vector<Product> products;

public:
     void loadProducts();

    void saveProducts();

    void displayProducts();

    vector<Product>& getProducts();

    Product* findProductById(int id);

    void addProduct(Product product);

    void deleteProduct(int id);

    void editProduct(int id);
    void displayMostViewedProducts();

void displayBestSellingProducts();
    
};


#endif