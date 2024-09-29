// function prototypes for ItemToPurcahse.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* structs */
// item struct
typedef struct _shopItem {
	char itemName[64];
	char itemDescription[64];
	int itemPrice;
	int itemQuantity;
} ItemToPurchase;

/* function declarations */
// remove item
void MakeItemBlank(ItemToPurchase * item);

// print cost
void PrintItemCost(ItemToPurchase item);

// print description of item
void PrintItemDescription(ItemToPurchase item);

