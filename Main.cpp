#include "include/Product_Manager.h"
#include "include/Customer.h"
#include "include/Manager.h"

#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main()
{
    ProductManager pm;

    pm.loadProducts();

    Manager manager;

    int choice;

    do
    {
        cout << "\n===== SMART E-COMMERCE SYSTEM =====\n";
        cout << "1. Customer\n";
        cout << "2. Manager\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                string customerName;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter customer name: ";
                getline(cin, customerName);

                Customer customer(customerName);

                customer.customerMenu(pm);

                break;
            }

            case 2:
                manager.managerMenu(pm);
                break;

            case 0:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}