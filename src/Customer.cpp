#include "../include/Customer.h"
#include "../include/Order.h"
#include "../include/OrderManager.h"
#include "../include/Recommendation_Engine.h"

#include <iostream>

using namespace std;
Customer::Customer()
{
    name = "Guest";
}

Customer::Customer(string name)
{
    this->name = name;
}

string Customer::getName() const
{
    return name;
}

void Customer::browseProducts(ProductManager& pm)
{
    pm.displayProducts();

    int id;

    cout << "Enter Product ID to view detail, or 0 to go back: ";
    cin >> id;

    if (id == 0)
    {
        return;
    }

    Product* product = pm.findProductById(id);

    if (product == nullptr)
    {
        cout << "Product not found.\n";
        return;
    }

    product->increaseView();

    RecommendationEngine engine;

    engine.recordView(
        name,
        id
    );

    product->display();

    pm.saveProducts();
}

void Customer::addProductToCart(ProductManager& pm)
{
    int id;
    int quantity;

    cout << "Enter Product ID: ";
    cin >> id;

    cout << "Enter Quantity: ";
    cin >> quantity;

    Product* product = pm.findProductById(id);

    if (product == nullptr)
    {
        cout << "Product not found.\n";
        return;
    }

    if (quantity <= 0)
    {
    cout << "Quantity must be greater than 0.\n";
    return;
    }

    if (quantity > product->getStock())
    {
    cout << "Not enough stock.\n";
    cout << "Available stock: " << product->getStock() << endl;
    return;
    }
    

    cart.addProduct(*product, quantity);

    cout << "Added successfully.\n";
}

void Customer::viewCart()
{
    cart.displayCart();
}

void Customer::updateQuantity()
{
    int id;
    int quantity;

    cout << "Enter Product ID: ";
    cin >> id;

    cout << "Enter New Quantity: ";
    cin >> quantity;

    cart.updateQuantity(id, quantity);
}

void Customer::removeProduct()
{
    int id;

    cout << "Enter Product ID: ";
    cin >> id;

    cart.removeProduct(id);
}
void Customer::checkout(ProductManager& pm)
{
    if (cart.isEmpty())
    {
        cout << "Cart is empty.\n";
        return;
    }

    // Check stock before checkout
    for (const auto& item : cart.getItems())
    {
        int productId = item.getProduct().getId();
        int quantity = item.getQuantity();

        Product* product = pm.findProductById(productId);

        if (product == nullptr)
        {
            cout << "Product not found.\n";
            return;
        }

        if (quantity > product->getStock())
        {
            cout << "Not enough stock for product: "
                 << product->getName()
                 << endl;

            cout << "Available stock: "
                 << product->getStock()
                 << endl;

            cout << "Requested quantity: "
                 << quantity
                 << endl;

            return;
        }
    }
    // Step 2: Create order
    OrderManager om;

    int orderId = om.getNextOrderId();

    Order order(
    orderId,
    name,
    cart.getItems(),
    cart.calculateTotal()
);
    cout << "\n===== CHECKOUT =====\n";

    order.display();

    // Step 3: Save order to orders.txt
    om.saveOrder(order);
    RecommendationEngine engine;

    // Step 4: Update product stock and sold count
    for (const auto& item : cart.getItems())
    {
        int productId = item.getProduct().getId();
        int quantity = item.getQuantity();

        Product* product = pm.findProductById(productId);

        if (product != nullptr)
        {
            product->setStock(
                product->getStock() - quantity
            );

            product->increaseSold(quantity);
              engine.recordPurchase(
                name,
                productId,
                quantity
            );
        }
    }

    // Step 5: Save updated products.txt
    pm.saveProducts();

    // Step 6: Clear cart
    cart.clearCart();

    cout << "\nOrder saved successfully.\n";
}
void Customer::receiveRecommendations(ProductManager& pm)
{
    int topN;

    cout << "Enter number of recommendations: ";
    cin >> topN;

    if (topN <= 0)
    {
        cout << "Invalid number.\n";
        return;
    }

    RecommendationEngine engine;

    engine.recommendProducts(
        name,
        pm,
        topN
    );
}
void Customer::customerMenu(ProductManager& pm)
{
    int choice;

    do
    {
        cout << "\n===== CUSTOMER =====\n";

        cout << "1. Browse Products\n";
        cout << "2. Add Product To Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Update Quantity\n";
        cout << "5. Remove Product\n";
        cout << "6. Check out\n" ;
        cout << "7. Receive Recommendations\n";
        cout << "0. Back\n";

        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                browseProducts(pm);
                break;

            case 2:
                addProductToCart(pm);
                break;

            case 3:
                viewCart();
                break;

            case 4:
                updateQuantity();
                break;

            case 5:
                removeProduct();
                break;
            case 6:
                checkout(pm);
                break;
            case 7:
                receiveRecommendations(pm);
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}