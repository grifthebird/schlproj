/* Project 1: Baker's Inventory
 * Write a program to track the
 * inventory of 4 different 
 * items, and restock them
 * apporpriately */
#include <stdio.h>
#include <math.h>

int main(void) {
	// item costs
	const double breadCost = 2.50;
	const double croissantCost = 1.20;
	const double muffinCost = 0.80;
	const double cookieCost = 0.50;

	// full item stock
	const int bread = 150;
	const int croissant = 200;
	const int muffin = 300;
	const int cookie = 500;

	// current item stock
	int curBread;
	int curCroissant;
	int curMuffin;
	int curCookie;

	// get current s%tock
	printf("Enter the number of bread, croissants, muffins, and cookies remaining:\n");
	scanf("%d %d %d %d", &curBread, &curCroissant, &curMuffin, &curCookie);
	
	// calc restock
	int reBread = bread - curBread;
	int reCroissant = croissant - curCroissant;
	int reMuffin = muffin - curMuffin;
	int reCookie = cookie - curCookie;

	// print restock
	printf("\nNeed: %d bread loaves, %d croissants, %d muffins, and %d cookies\n", reBread, reCroissant, reMuffin, reCookie);

	// total cost
	double total = (reBread * breadCost) + (reCroissant * croissantCost) + (reMuffin * muffinCost) + (reCookie * cookieCost);
	int dollars = (int)(total);
	int tmp = round(100 * total); 
	int cents = tmp % 100;
	printf("Cost: %d dollars and %d cents\n", dollars, cents);

	// average sold
	double avgBread = ((bread - curBread) / 7.0);
	double avgCroissant = ((croissant - curCroissant) / 7.0);
	double avgMuffin = ((muffin - curMuffin) / 7.0);
	double avgCookie = ((cookie - curCookie) / 7.0);

	// print average
	printf("Average sold: %.2lf bread loaves, %.2lf croissants, %.2f muffins, and %.2f cookies per day\n", avgBread, avgCroissant, avgMuffin, avgCookie);
	
	// return
	return 0;
}

