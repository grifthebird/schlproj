#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ItemToPurchase.h"

void MakeItemBlank(ItemToPurchase *item)
{
	strcpy(item->itemName, "none");
	item->itemPrice = 0;
	item->itemQuantity = 0;
	return;
}

void PrintItemCost(ItemToPurchase item)
{
	printf("%s %d @ $%d = $%d\n", item.itemName, item.itemQuantity, item.itemPrice, (item.itemQuantity * item.itemPrice)); 
	return;
}
