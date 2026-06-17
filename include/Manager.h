#ifndef MANAGER_H
#define MANAGER_H

#include "Product_Manager.h"

class Manager
{
public:
    void managerMenu(ProductManager& pm);

    void addProductMenu(ProductManager& pm);

    void editProductMenu(ProductManager& pm);

    void deleteProductMenu(ProductManager& pm);

    void displayActiveUsers();
};

#endif