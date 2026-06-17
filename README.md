# smart-ecommerce-system
## 1. Introduction
This project is a Smart E-Commerce System developed in C++ using Object-Oriented Programming. The system simulates a simple online shopping platform where customers can browse products, add products to cart, purchase products, and receive product recommendations based on their behavior.

The system also provides manager features such as adding, editing, deleting products, and viewing system statistics. All data is stored in text files so that product data, order history, and user interactions can be saved after the program ends.

The main purpose of this project is not only to build an e-commerce system, but also to demonstrate how OOP concepts such as encapsulation, abstraction, composition, and class interaction can be applied in a real program.

## 2. Object-Oriented Design 
The system is divided into multiple classes. Each class has one main responsibility. This makes the program easier to understand, maintain, and extend.
### Product Class :
It stores product information such as:

Product ID
Product name
Category
Color
Price
Stock
Total views
Total sold quantity

The Product class also provides getter and setter functions. Other classes do not directly access product attributes. Instead, they use public functions such as getId(), getName(), getPrice(), getStock(), setStock(), increaseView(), and increaseSold().

This shows encapsulation because the product data is protected inside the class.

### Product_Manager Class :
It is responsible for:

Loading products from products.txt
Saving products to products.txt
Displaying products
Finding a product by ID
Adding new products
Editing products
Deleting products
Showing most viewed products
Showing best-selling products

The reason for separating ProductManager from Product is that one Product only represents a single item, while ProductManager manages many products.
### For Example :
when a customer enters a product ID, the Customer class does not search the product list by itself. Instead, it calls:
" pm.findProductById(id); "
This keeps the searching logic inside Product_Manager.

### Cart_Item Class :
It contains:

A Product
Quantity
Subtotal
The subtotal is calculated from : subtotal = product price * quantity
-> This class is useful because the same product can appear in the cart with a specific quantity.

### Cart Class :
It supports:

Adding products to cart
Removing products from cart
Updating quantity
Displaying cart items
Calculating total price
Clearing the cart after checkout
-> The Customer class owns a Cart object. This is an example of composition because a customer “has a” cart.
-> This design is logical because each customer should have their own shopping cart.

### Customer Class :
It allows the customer to:

Browse products
Add products to cart
View cart
Update quantity
Remove products
Checkout
Receive recommendations
-> The Customer class does not store all products directly. Instead, it receives a ProductManager object as a parameter.
### For example :  " customer.customerMenu(pm); " 
-> Inside the customer menu, the customer can use the product manager to browse or search products. This shows object interaction because Customer depends on ProductManager to access product data.

### Order Class :
It stores:

Order ID
Customer name
Purchased items
Total price
-> An order is created during checkout. It is not created when the customer only adds products to cart. This is because an order should only exist after the customer confirms the purchase.

### Order_Manager Class :
It is responsible for:

Generating the next order ID
Saving order history to orders.txt
-> This keeps file handling for orders separate from the Customer class. The customer only performs checkout, while OrderManager handles how the order is stored.

### Manager Class :
The manager can:

Add products
Edit products
Delete products
View most viewed products
View best-selling products
View active users
-> The Manager class also uses Product_Manager because product management should be handled through the product manager.

### Recommendation_Engine Class :
It uses interaction history from interactions.txt, including:

Product views
Product purchases
Category preference
Using formular :  score = view_count * 0.2 + purchase_count * 0.8 + category_bonus
-> Purchases have a higher weight than views because buying a product shows stronger interest than only viewing it.


### 3. Main Program Flow 
1) creates a ProductManager object and loads products from file:
   ProductManager pm;
   pm.loadProducts();
2) creates a Manager object:
   Manager manager;
3) main menu is displayed:
   1. Customer
   2. Manager
   0. Exit
4) If choose Customer then program asks for the customer name and create a " Customer " object :
    Customer customer(customerName);
    customer.customerMenu(pm);
5) If Choose Manager, then the program opens the manager menu :
    manager.managerMenu(pm);

## 4. Customer Flow
- When the customer browses products, the Customer class calls: " pm.displayProducts(); "
-  Then the customer can enter a product ID to view details. The system searches for the product: " Product* product = pm.findProductById(id); "
-  If the product exists, the view count is increased: " product->increaseView(); "
-  At the same time, the recommendation engine records this behavior: " engine.recordView(name, id); "
->   So one browsing action affects both:
      Product statistics
      User interaction history

## 5. Check out Flow
Checkout is one of the most important flows in the system.
- First, the system checks whether the cart is empty. If the cart is empty, checkout is stopped.
- The system checks whether all products in the cart still have enough stock.
- After validation, the system creates an order:
     Order order(orderId, name, cart.getItems(), cart.calculateTotal());
- Then the order is saved by Order_Manager:
     om.saveOrder(order);
- After that, the product stock is reduced and sold count is increased:
    product->setStock(product->getStock() - quantity);
    product->increaseSold(quantity);
- The purchase is also recorded for recommendation:
    engine.recordPurchase(name, productId, quantity);
- Finally, product data is saved and the cart is cleared:
    pm.saveProducts();
    cart.clearCart();

  -> This flow shows how several objects cooperate:
  Customer
→ Cart
→ Order
→ OrderManager
→ ProductManager
→ RecommendationEngine

## 6. Data Storage
The system uses text files to store data.
1) products.txt : Store product information : ProductID|Name|Category|Color|Price|Stock|TotalViews|TotalSold
2) orders.txt : Stores order history 
OrderID|CustomerName|ProductID|Quantity|Subtotal
3) interacts.txt : Stores customer behavior for recommendation
CustomerName|ProductID|ViewCount|PurchaseCount

## 7. Recommendation Logic
- The recommendation engine reads customer interaction history from interactions.txt.
- For each product, it calculates a score:
  score = view_count * 0.2 + purchase_count * 0.8 + category_bonus
-> The system then sorts products by score in descending order and displays the Top N recommended products.
->  The category bonus helps recommend products from categories that the customer has shown interest in before.

## 8. OOP Concepts Applied
1) Encapsulation
- Class attributes are kept private, and other classes access them through public methods.

- For example, product stock is not changed directly. It is updated through functions such as:
setStock()
increaseSold()

2) Abstraction
- Each class hides its internal implementation.

- For example, the Customer class does not need to know how products are loaded from file. It only calls functions from Product_Manager.

3) Composition
- The Customer class contains a Cart object. This means a customer has a cart.

- The Cart class contains multiple CartItem objects.

4) Separation of Responsibilities:

Product → stores product data
ProductManager → manages products
Cart → manages cart items
Customer → handles customer actions
Order → stores order information
OrderManager → saves order history
Manager → handles admin features
RecommendationEngine → recommends products 

## 9. Conclusion
- This project successfully implements a Smart E-Commerce System using Object-Oriented Programming in C++. The system supports customer shopping features, cart management, order processing, product management, system statistics, and a basic recommendation engine.

- Through this project, I learned how different classes interact with each other in a real program. The project demonstrates important OOP concepts such as encapsulation, abstraction, composition, separation of responsibilities, and object collaboration.

## 10. How to run the projectt 
### 1. Clone the repository

```bash
git clone https://github.com/lshieu/smart-ecommerce-system.git
```
### 2. Then go to the project folder:
```bash
cd smart-ecommerce-system
```
### 3. Check g++ version ( if not installed then install g++ )
```bash
g++ --version
```
### 4. Compile
```bash
g++ main.cpp src/*.cpp -o app
```
### 5. Run the program
```bash
.\app.exe
```
   
   
   





