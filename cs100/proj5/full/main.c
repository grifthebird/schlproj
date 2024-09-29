#include "ShoppingCart.h"
#include <stdio.h>
#include <string.h>

void PrintMenu(ShoppingCart cart);

ItemToPurchase MakeItem(void);

void RefreshInput(void);

int main(void)
{
	// get user info
	ShoppingCart cart;
	printf("Enter Customer's Name:\n");
	fgets(cart.customerName, 64, stdin);
	cart.customerName[strlen(cart.customerName) - 1] = '\0';

	printf("Enter Today's Date:\n");
	fgets(cart.currentDate, 64, stdin);
	cart.currentDate[strlen(cart.currentDate) - 1] = '\0';

	printf("\nCustomer Name: %s\n", cart.customerName);
	printf("Today's Date: %s\n", cart.currentDate);

	cart.cartSize = 0;

	// go shopping
	PrintMenu(cart);
	return 0;
}

void PrintMenu(ShoppingCart cart)
{
	int done = 1;
	char input;
	char remove[64];
	ItemToPurchase change;
	while (done)
	{
		printf("\nMENU\n"
		       "a - Add item to cart\n"
		       "r - Remove item from cart\n"
		       "c - Change item quantity\n"
		       "i - Output items' descriptions\n"
		       "o - Output shopping cart\n"
		       "q - Quit\n"
		       "\nChoose an option:\n"
		       );
		scanf(" %c", &input);
		while (input != 'q' && input != 'a' && input != 'r' && input != 'c' && input != 'i' && input != 'o')
		{
			printf("Choose an option:\n");
			scanf(" %c", &input);
		}
		switch (input) {;
			case 'q':
				done = 0;
				break;
			case 'a':
				printf("ADD ITEM TO CART\n");
				cart = AddItem(MakeItem(), cart);
				break;
			case 'r':
				printf("REMOVE ITEM FROM CART\n");
				printf("Enter name of item to remove:\n");
				RefreshInput();
				fgets(remove, 64, stdin);
				remove[strlen(remove) - 1] = '\0';
				cart = RemoveItem(remove, cart);
				break;
			case 'c':
				printf("CHANGE ITEM QUANTITY\n");
				RefreshInput();
				printf("Enter the item name:\n");
				fgets(change.itemName, 64, stdin);
				change.itemName[strlen(change.itemName) - 1] = '\0';
				printf("Enter the new quantity:\n");
				scanf("%d", &change.itemQuantity);
				cart = ModifyItem(change, cart);
				break;
			case 'i':
				printf("OUTPUT ITEMS' DESCRIPTIONS\n");
				PrintDescriptions(cart);
				break;
			case 'o':
				printf("OUTPUT SHOPPING CART\n");
				PrintTotal(cart);
				break;
		}
	}
	return;
}

ItemToPurchase MakeItem(void)
{
	RefreshInput();

	ItemToPurchase item;
	printf("Enter the item name:\n");
	fgets(item.itemName, 64, stdin);
	item.itemName[strlen(item.itemName) - 1] = '\0';

	printf("Enter the item description:\n");
	fgets(item.itemDescription, 64, stdin);
	item.itemDescription[strlen(item.itemDescription) - 1] = '\0';

	printf("Enter the item price:\n");
	scanf("%d", &item.itemPrice);

	printf("Enter the item quantity:\n");
	scanf("%d", &item.itemQuantity);
	return item;
}

void RefreshInput(void)
{
	char c = getchar();
	while(c != '\n' && c != EOF) {
		c = getchar();
	}

	return;
}
