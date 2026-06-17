#include "../include/Product_Manager.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <limits>

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

void printProductTableHeader()
{
    cout << left
         << setw(6) << "ID"
         << setw(24) << "Product name"
         << setw(16) << "Category"
         << setw(12) << "Color"
         << right
         << setw(18) << "Price"
         << setw(9) << "Stock"
         << setw(9) << "Views"
         << setw(9) << "Sold"
         << '\n';
    cout << string(103, '-') << '\n';
}

void printProductRow(const Product& product)
{
    cout << left
         << setw(6) << product.getId()
         << setw(24) << product.getName()
         << setw(16) << product.getCategory()
         << setw(12) << product.getColor()
         << right
         << setw(18) << formatMoney(product.getPrice())
         << setw(9) << product.getStock()
         << setw(9) << product.getTotalViews()
         << setw(9) << product.getTotalSold()
         << '\n';
}
}

void ProductManager::loadProducts()
{
    products.clear();
    ifstream fin("data/products.txt");

    if (!fin)
    {
        cout << "Cannot open products.txt\n";
        return;
    }

    string line;

    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string idStr;
        string name;
        string category;
        string color;
        string priceStr;
        string stockStr;
        string viewsStr;
        string soldStr;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, color, '|');
        getline(ss, priceStr, '|');
        getline(ss, stockStr, '|');
        getline(ss, viewsStr, '|');
        getline(ss, soldStr, '|');

        Product product(
            stoi(idStr),
            name,
            category,
            color,
            stoll(priceStr),
            stoi(stockStr),
            stoi(viewsStr),
            stoi(soldStr)
        );

        products.push_back(product);
    }
}

void ProductManager::displayProducts()
{
    cout << "\n=============================== PRODUCT LIST ===============================\n";

    if (products.empty())
    {
        cout << "No products available.\n";
        return;
    }

    printProductTableHeader();

    for (const Product& product : products)
    {
        printProductRow(product);
    }
}

vector<Product>& ProductManager::getProducts()
{
    return products;
}

Product* ProductManager::findProductById(int id)
{
    for (auto& product : products)
    {
        if (product.getId() == id)
        {
            return &product;
        }
    }

    return nullptr;
}

void ProductManager::saveProducts()
{
    ofstream fout("data/products.txt");

    if (!fout)
    {
        cout << "Cannot open products.txt for writing.\n";
        return;
    }

    for (const Product& product : products)
    {
        fout << product.getId() << "|"
             << product.getName() << "|"
             << product.getCategory() << "|"
             << product.getColor() << "|"
             << product.getPrice() << "|"
             << product.getStock() << "|"
             << product.getTotalViews() << "|"
             << product.getTotalSold()
             << endl;
    }

    fout.close();
}

void ProductManager::addProduct(Product product)
{
    if (findProductById(product.getId()) != nullptr)
    {
        cout << "Product ID already exists.\n";
        return;
    }

    products.push_back(product);
    saveProducts();

    cout << "Product added successfully.\n";
}

void ProductManager::deleteProduct(int id)
{
    for (int i = 0; i < static_cast<int>(products.size()); i++)
    {
        if (products[i].getId() == id)
        {
            products.erase(products.begin() + i);
            saveProducts();

            cout << "Product deleted successfully.\n";
            return;
        }
    }

    cout << "Product not found.\n";
}

void ProductManager::editProduct(int id)
{
    Product* product = findProductById(id);

    if (product == nullptr)
    {
        cout << "Product not found.\n";
        return;
    }

    string newName;
    string newCategory;
    string newColor;
    long long newPrice;
    int newStock;

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    cout << "Enter new name: ";
    getline(cin, newName);

    cout << "Enter new category: ";
    getline(cin, newCategory);

    cout << "Enter new color: ";
    getline(cin, newColor);

    cout << "Enter new price: ";
    cin >> newPrice;

    cout << "Enter new stock: ";
    cin >> newStock;

    *product = Product(
        id,
        newName,
        newCategory,
        newColor,
        newPrice,
        newStock,
        product->getTotalViews(),
        product->getTotalSold()
    );

    saveProducts();

    cout << "Product updated successfully.\n";
}

void ProductManager::displayMostViewedProducts()
{
    if (products.empty())
    {
        cout << "No products available.\n";
        return;
    }

    vector<Product> sortedProducts = products;

    sort(
        sortedProducts.begin(),
        sortedProducts.end(),
        [](const Product& a, const Product& b)
        {
            return a.getTotalViews() > b.getTotalViews();
        }
    );

    cout << "\n===== MOST VIEWED PRODUCTS =====\n";

    int limit = min(5, (int)sortedProducts.size());

    for (int i = 0; i < limit; i++)
    {
        cout << i + 1 << ". "
             << sortedProducts[i].getName()
             << " | Views: "
             << sortedProducts[i].getTotalViews()
             << endl;
    }
}

void ProductManager::displayBestSellingProducts()
{
    if (products.empty())
    {
        cout << "No products available.\n";
        return;
    }

    vector<Product> sortedProducts = products;

    sort(
        sortedProducts.begin(),
        sortedProducts.end(),
        [](const Product& a, const Product& b)
        {
            return a.getTotalSold() > b.getTotalSold();
        }
    );

    cout << "\n===== BEST SELLING PRODUCTS =====\n";

    int limit = min(5, (int)sortedProducts.size());

    for (int i = 0; i < limit; i++)
    {
        cout << i + 1 << ". "
             << sortedProducts[i].getName()
             << " | Sold: "
             << sortedProducts[i].getTotalSold()
             << endl;
    }
}