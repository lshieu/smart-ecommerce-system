#include "../include/Manager.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace
{
struct UserActivity
{
    string customerName;
    int totalViews;
    int totalPurchases;

    double getScore() const
    {
        return totalViews * 0.2 + totalPurchases * 0.8;
    }
};
}

void Manager::managerMenu(ProductManager& pm)
{
    int choice;

    do
    {
        cout << "\n===== MANAGER MENU =====\n";
        cout << "1. Add Product\n";
        cout << "2. Edit Product\n";
        cout << "3. Delete Product\n";
        cout << "4. View Products\n";
        cout << "5. Most Viewed Products\n";
        cout << "6. Best Selling Products\n";
        cout << "7. View Active Users\n";
        cout << "0. Back\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addProductMenu(pm);
                break;

            case 2:
                editProductMenu(pm);
                break;

            case 3:
                deleteProductMenu(pm);
                break;

            case 4:
                pm.displayProducts();
                break;

            case 5:
                pm.displayMostViewedProducts();
                break;

            case 6:
                pm.displayBestSellingProducts();
                break;

            case 7:
                displayActiveUsers();
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

void Manager::addProductMenu(ProductManager& pm)
{
    int id;
    string name;
    string category;
    string color;
    long long price;
    int stock;

    cout << "\n===== ADD PRODUCT =====\n";
    cout << "Enter product ID: ";
    cin >> id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter product name: ";
    getline(cin, name);
    cout << "Enter category: ";
    getline(cin, category);
    cout << "Enter color: ";
    getline(cin, color);
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter stock: ";
    cin >> stock;

    Product newProduct(
        id,
        name,
        category,
        color,
        price,
        stock,
        0,
        0
    );

    pm.addProduct(newProduct);
}

void Manager::editProductMenu(ProductManager& pm)
{
    int id;

    cout << "\n===== EDIT PRODUCT =====\n";
    cout << "Enter product ID to edit: ";
    cin >> id;

    pm.editProduct(id);
}

void Manager::deleteProductMenu(ProductManager& pm)
{
    int id;

    cout << "\n===== DELETE PRODUCT =====\n";
    cout << "Enter product ID to delete: ";
    cin >> id;

    pm.deleteProduct(id);
}

void Manager::displayActiveUsers()
{
    ifstream fin("data/interactions.txt");

    if (!fin)
    {
        cout << "Cannot open interactions.txt.\n";
        return;
    }

    map<string, pair<int, int>> activityByCustomer;
    string line;

    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string customerName;
        string productIdText;
        string viewsText;
        string purchasesText;

        getline(ss, customerName, '|');
        getline(ss, productIdText, '|');
        getline(ss, viewsText, '|');
        getline(ss, purchasesText, '|');

        if (customerName.empty() ||
            productIdText.empty() ||
            viewsText.empty() ||
            purchasesText.empty())
        {
            continue;
        }

        try
        {
            int views = stoi(viewsText);
            int purchases = stoi(purchasesText);

            activityByCustomer[customerName].first += views;
            activityByCustomer[customerName].second += purchases;
        }
        catch (const exception&)
        {
            continue;
        }
    }

    if (activityByCustomer.empty())
    {
        cout << "\nNo user activity found.\n";
        return;
    }

    vector<UserActivity> activeUsers;

    for (const auto& entry : activityByCustomer)
    {
        activeUsers.push_back({
            entry.first,
            entry.second.first,
            entry.second.second
        });
    }

    sort(
        activeUsers.begin(),
        activeUsers.end(),
        [](const UserActivity& a, const UserActivity& b)
        {
            if (a.getScore() == b.getScore())
            {
                return a.customerName < b.customerName;
            }

            return a.getScore() > b.getScore();
        }
    );

    cout << "\n===================== ACTIVE USERS =====================\n";
    cout << left
         << setw(8) << "Rank"
         << setw(24) << "Customer"
         << right
         << setw(10) << "Views"
         << setw(14) << "Purchases"
         << setw(12) << "Score"
         << '\n';
    cout << string(68, '-') << '\n';

    for (int i = 0; i < static_cast<int>(activeUsers.size()); i++)
    {
        cout << left
             << setw(8) << i + 1
             << setw(24) << activeUsers[i].customerName
             << right
             << setw(10) << activeUsers[i].totalViews
             << setw(14) << activeUsers[i].totalPurchases
             << setw(12) << fixed << setprecision(2)
             << activeUsers[i].getScore()
             << '\n';
    }

    cout << "\nScore = Views x 0.2 + Purchases x 0.8\n";
}
