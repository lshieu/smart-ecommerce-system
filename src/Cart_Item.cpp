#include "../include/Cart_Item.h"

CartItem::CartItem(Product product, int quantity)
{
    this->product = product;
    this->quantity = quantity;
}

Product CartItem::getProduct() const
{
    return product;
}

int CartItem::getQuantity() const
{
    return quantity;
}

void CartItem::setQuantity(int quantity)
{
    this->quantity = quantity;
}

long long CartItem::getSubtotal() const
{
    return product.getPrice() * quantity;
}