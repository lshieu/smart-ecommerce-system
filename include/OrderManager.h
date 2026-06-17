#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "Order.h"

class OrderManager
{
public:
    int getNextOrderId();

    void saveOrder(const Order& order);
};

#endif