#include "../include/OrderManager.h"

#include <fstream>
#include <sstream>

using namespace std;
int OrderManager::getNextOrderId()
{
    ifstream fin("data/orders.txt");

    string line;
    int maxOrderId = 1000;

    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        // Lấy phần Order ID đứng trước dấu |
        size_t separator = line.find('|');

        if (separator == string::npos)
        {
            continue;
        }

        string orderIdText = line.substr(0, separator);

        try
        {
            int orderId = stoi(orderIdText);

            if (orderId > maxOrderId)
            {
                maxOrderId = orderId;
            }
        }
        catch (const invalid_argument&)
        {
            
            continue;
        }
        catch (const out_of_range&)
        {
            continue;
        }
    }

    fin.close();

    return maxOrderId + 1;
}
void OrderManager::saveOrder(const Order& order)
{
    ofstream fout(
        "data/orders.txt",
        ios::app
    );

    for (const auto& item : order.getItems())
    {
        fout
            << order.getOrderId()
            << "|"

            << order.getCustomerName()
            << "|"

            << item.getProduct().getId()
            << "|"

            << item.getQuantity()
            << "|"

            << item.getSubtotal()

            << endl;
    }

    fout.close();
}