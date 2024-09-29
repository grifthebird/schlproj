#include <stdio.h>
#include <string.h>
#include "ItemToPurchase.h"

int main(void)
{
	// helper variables
	char buffer[64];
	int price;
	int qty;
	int totalCost = 0;

	/* get items */
	// item 1
	printf("Item 1\n");
	ItemToPurchase item1;
	MakeItemBlank(&item1);

	printf("Enter the item name:\n");
	fgets(buffer, 64, stdin);
	buffer[strlen(buffer) - 1] = '\0';
	strcpy(item1.itemName, buffer);

	printf("Enter the item price:\n");
	scanf("%d", &price);
	item1.itemPrice = price;

	printf("Enter the item quantity:\n");
	scanf("%d", &qty);
	item1.itemQuantity = qty;
	printf("\n");
	totalCost += item1.itemPrice * item1.itemQuantity;

	char c = getchar();
	while(c != '\n' && c != EOF) {
		c = getchar();
	}

	// item 2
	printf("Item 2\n");
	ItemToPurchase item2;
	MakeItemBlank(&item2);

	printf("Enter the item name:\n");
	fgets(buffer, 64, stdin);
	buffer[strlen(buffer) - 1] = '\0';
	strcpy(item2.itemName, buffer);

	printf("Enter the item price:\n");
	scanf("%d", &price);
	item2.itemPrice = price;

	printf("Enter the item quantity:\n");
	scanf("%d", &qty);
	item2.itemQuantity = qty;
	totalCost += item2.itemPrice * item2.itemQuantity;
	
	/* get total */
	printf("\nTOTAL COST\n");
	PrintItemCost(item1);
	PrintItemCost(item2);
	printf("\nTotal: $%d\n", totalCost);
	return 0;
}
