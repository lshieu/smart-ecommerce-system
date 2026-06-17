#include "../include/Recommendation_Engine.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

namespace
{
struct InteractionRecord
{
    string customerName;
    int productId;
    int viewCount;
    int purchaseCount;
};

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

void RecommendationEngine::updateInteraction(
    string customerName,
    int productId,
    int viewIncrease,
    int purchaseIncrease)
{
    vector<InteractionRecord> records;
    ifstream fin("data/interactions.txt");
    string line;
    bool found = false;

    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string name;
        string productIdStr;
        string viewStr;
        string purchaseStr;

        getline(ss, name, '|');
        getline(ss, productIdStr, '|');
        getline(ss, viewStr, '|');
        getline(ss, purchaseStr, '|');

        InteractionRecord record;
        record.customerName = name;
        record.productId = stoi(productIdStr);
        record.viewCount = stoi(viewStr);
        record.purchaseCount = stoi(purchaseStr);

        if (record.customerName == customerName &&
            record.productId == productId)
        {
            record.viewCount += viewIncrease;
            record.purchaseCount += purchaseIncrease;
            found = true;
        }

        records.push_back(record);
    }

    if (!found)
    {
        records.push_back({
            customerName,
            productId,
            viewIncrease,
            purchaseIncrease
        });
    }

    ofstream fout("data/interactions.txt");

    for (const auto& record : records)
    {
        fout << record.customerName << "|"
             << record.productId << "|"
             << record.viewCount << "|"
             << record.purchaseCount << '\n';
    }
}

void RecommendationEngine::recordView(string customerName, int productId)
{
    updateInteraction(customerName, productId, 1, 0);
}

void RecommendationEngine::recordPurchase(
    string customerName,
    int productId,
    int quantity)
{
    updateInteraction(customerName, productId, 0, quantity);
}

void RecommendationEngine::recommendProducts(
    string customerName,
    ProductManager& pm,
    int topN)
{
    ifstream fin("data/interactions.txt");
    map<int, pair<int, int>> userInteractions;
    string line;

    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string name;
        string productIdStr;
        string viewStr;
        string purchaseStr;

        getline(ss, name, '|');
        getline(ss, productIdStr, '|');
        getline(ss, viewStr, '|');
        getline(ss, purchaseStr, '|');

        if (name == customerName)
        {
            userInteractions[stoi(productIdStr)] =
                make_pair(stoi(viewStr), stoi(purchaseStr));
        }
    }

    vector<Product>& products = pm.getProducts();

    if (products.empty())
    {
        cout << "No products available.\n";
        return;
    }

    vector<pair<double, Product>> scoredProducts;

    if (userInteractions.empty())
    {
        cout << "\nNo personal interaction history found.\n";
        cout << "Showing popular products instead.\n";

        for (const Product& product : products)
        {
            double score =
                product.getTotalViews() * 0.2 +
                product.getTotalSold() * 0.8;

            scoredProducts.push_back(make_pair(score, product));
        }
    }
    else
    {
        map<string, double> categoryScores;

        for (const auto& entry : userInteractions)
        {
            Product* product = pm.findProductById(entry.first);

            if (product != nullptr)
            {
                double categoryScore =
                    entry.second.first * 0.2 +
                    entry.second.second * 0.8;

                categoryScores[product->getCategory()] += categoryScore;
            }
        }

        string favoriteCategory;
        double bestCategoryScore = -1;

        for (const auto& entry : categoryScores)
        {
            if (entry.second > bestCategoryScore)
            {
                bestCategoryScore = entry.second;
                favoriteCategory = entry.first;
            }
        }

        for (const Product& product : products)
        {
            int viewCount = 0;
            int purchaseCount = 0;

            if (userInteractions.find(product.getId()) != userInteractions.end())
            {
                viewCount = userInteractions[product.getId()].first;
                purchaseCount = userInteractions[product.getId()].second;
            }

            double categoryBonus =
                product.getCategory() == favoriteCategory ? 2.0 : 0.0;

            double score =
                viewCount * 0.2 +
                purchaseCount * 0.8 +
                categoryBonus;

            scoredProducts.push_back(make_pair(score, product));
        }
    }

    sort(
        scoredProducts.begin(),
        scoredProducts.end(),
        [](const pair<double, Product>& a,
           const pair<double, Product>& b)
        {
            return a.first > b.first;
        }
    );

    int limit = min(topN, static_cast<int>(scoredProducts.size()));

    cout << "\n====================== TOP "
         << limit
         << " RECOMMENDED PRODUCTS ======================\n";
    cout << left
         << setw(7) << "Rank"
         << setw(7) << "ID"
         << setw(24) << "Product name"
         << setw(16) << "Category"
         << setw(12) << "Color"
         << right
         << setw(18) << "Price"
         << setw(10) << "Score"
         << '\n';
    cout << string(94, '-') << '\n';

    for (int i = 0; i < limit; i++)
    {
        const Product& product = scoredProducts[i].second;

        cout << left
             << setw(7) << i + 1
             << setw(7) << product.getId()
             << setw(24) << product.getName()
             << setw(16) << product.getCategory()
             << setw(12) << product.getColor()
             << right
             << setw(18) << formatMoney(product.getPrice())
             << setw(10) << fixed << setprecision(2) << scoredProducts[i].first
             << '\n';
    }
}
