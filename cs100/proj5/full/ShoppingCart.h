// stubs and struct for shopping cart
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ItemToPurchase.h"

/* cart struct */
typedef struct _cart
{
	char customerName[64];
	char currentDate[64];
	ItemToPurchase cartItems[10];
	int cartSize;
} ShoppingCart;

/* function stubs */
// adds an item to the shopping cart
ShoppingCart AddItem(ItemToPurchase item, ShoppingCart cart);

// removes an item from the shopping cart
ShoppingCart RemoveItem(char * itemName, ShoppingCart cart);

// Changes the aspects of an item in the cart
ShoppingCart ModifyItem(ItemToPurchase item, ShoppingCart cart);

// gets quantity of items in cart (total items)
int GetNumItemsInCart(ShoppingCart cart);

// gets total cost of cart
int GetCostOfCart(ShoppingCart cart);

// gets number of items in cart (unique items)
void PrintTotal(ShoppingCart cart);

// prints descriptions of each item
void PrintDescriptions(ShoppingCart cart);


