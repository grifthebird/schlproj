// function definitions
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include "ShoppingCart.h"

// add an item to the shopping cart
ShoppingCart AddItem(ItemToPurchase item, ShoppingCart cart)
{
	ShoppingCart holder = cart;
	holder.cartItems[holder.cartSize] = item;
	holder.cartSize++;
	return holder;
}

// remove an item from the shopping cart
ShoppingCart RemoveItem(char * itemName, ShoppingCart cart)
{	
	int itemIndex = -1;
	ItemToPurchase currItem;
	for (int i = 0; i < cart.cartSize; i++)
	{
		currItem = cart.cartItems[i];
		if (0 == strcmp(itemName, currItem.itemName))
		{
			itemIndex = i;
		}
	}

	if (itemIndex == -1)
	{
		printf("Item not found in cart. Nothing removed.\n");
		return cart;
	}

	for (int i = itemIndex + 1; i < cart.cartSize; i++)
	{
		currItem = cart.cartItems[i];
		cart.cartItems[i - 1] = currItem;
	}

	cart.cartSize--;
	return cart;
}

// modify parts of an item
ShoppingCart ModifyItem(ItemToPurchase item, ShoppingCart cart)
{
	ItemToPurchase changeItem;
	for (int i = 0; i < cart.cartSize; i++)
	{
		changeItem = cart.cartItems[i];
		if (0 == strcmp(item.itemName, changeItem.itemName))
		{
			changeItem.itemQuantity = item.itemQuantity;
			cart.cartItems[i] = changeItem;
			return cart;
		}
	}
	printf("Item not found in cart. Nothing modified.\n");
	return cart;
}

// get total number of things in cart
int GetNumItemsInCart(ShoppingCart cart)
{
	int total = 0;
	ItemToPurchase currItem;
	for (int i = 0; i < cart.cartSize; i++)
	{
		currItem = cart.cartItems[i];
		total += currItem.itemQuantity;
	}

	return total;
}

// get the total cost of the cart
int GetCostOfCart(ShoppingCart cart)
{
	int cost = 0;
	ItemToPurchase currItem;
	for (int i = 0; i < cart.cartSize; i++)
	{
		currItem = cart.cartItems[i];
		cost += currItem.itemQuantity * currItem.itemPrice;
	}

	return cost;
}

// print the entire cart
void PrintTotal(ShoppingCart cart)
{
	// formatting data
	printf("%s's Shopping Cart - %s\n", cart.customerName, cart.currentDate);
	printf("Number of Items: %d\n\n", GetNumItemsInCart(cart));

	if (GetNumItemsInCart(cart) == 0)
	{
		printf("SHOPPING CART IS EMPTY\n");
		printf("\n");
		printf("Total: $0\n");
		return;
	}

	// print cart items and prices
	for (int i = 0; i < cart.cartSize; i++)
	{
		PrintItemCost(cart.cartItems[i]);
	}

	// print total
	printf("\nTotal: $%d\n", GetCostOfCart(cart));
	return;
}

// print descriptions of each item
void PrintDescriptions(ShoppingCart cart)
{
	// formatting
	printf("%s's Shopping Cart - %s\n\n", cart.customerName, cart.currentDate);
	printf("Item Descriptions\n");
	for (int i = 0; i < cart.cartSize; i++)
	{
		PrintItemDescription(cart.cartItems[i]);
	}

	return;
}
