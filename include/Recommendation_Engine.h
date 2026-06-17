#ifndef RECOMMENDATIONENGINE_H
#define RECOMMENDATIONENGINE_H

#include <string>
#include "Product_Manager.h"

using namespace std;

class RecommendationEngine
{
private:
    void updateInteraction(
        string customerName,
        int productId,
        int viewIncrease,
        int purchaseIncrease
    );

public:
    void recordView(string customerName, int productId);

    void recordPurchase(
        string customerName,
        int productId,
        int quantity
    );

    void recommendProducts(
        string customerName,
        ProductManager& pm,
        int topN
    );
};

#endif