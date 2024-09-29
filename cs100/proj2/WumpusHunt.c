// wumpus hunt simulation
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// prototypes, declare functions before using
void choice1();

// second
void forest();
void river();
void cave();
void cliffs();

// third
void downstream();
void cavern();
void peaks();
void ledges();
void redwood();
void pine();
void hardwood();

// fourth
void nearside();
void high();
void treeline();
void maple();
void ground();

// fifth
void pancakes();
void waffles();

// first location
void choice1(void) {
	char choice[50];
	scanf("%s", choice);
	if (0 == strcmp(choice, "river")) {
		river();
	}
	else if (0 == strcmp(choice, "cave")) {
		cave();
	}
	else if (0 == strcmp(choice, "forest")) {
		forest();
	}
	else if (0 == strcmp(choice, "cliffs")) {
		cliffs();
	}
	else if (0 == strcmp(choice, "hardwood")) {
		hardwood();
	}
}

// second location
void river(void) {
	char choice[50];
	printf("upstream or downstream?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "upstream")) {
		printf("THE HUNT IS OVER!\n You lost your paddle!\n");
	}
	else if (0 == strcmp(choice, "downstream")) {
		downstream();
	}
}

void cave(void) {
	char choice[50];
	printf("tunnel or cavern?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "tunnel")) {
		printf("THE HUNT IS OVER! You found a bear. He was Hungry!\n");
	}
	else if (0 == strcmp(choice, "cavern")) {
		cavern();
	}
}

void forest(void) {
	char choice[50];
	printf("redwood or pine or hardwood?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "redwood")) {
		redwood();
	}
	else if (0 == strcmp(choice, "pine")) {
		pine();
	}
	else if (0 == strcmp(choice, "hardwood")) {
		hardwood();
	}
}

void cliffs(void) {
	char choice[50];
	printf("ledges or peaks?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "ledges")) {
		ledges();
	}
	else if (0 == strcmp(choice, "peaks")) {
		peaks();
	}
}

// third location
// river
void downstream(void) {
	char choice[50];
	printf("rapids or calm?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "rapids")) {
		printf("THE HUNT IS OVER! You capsized and lost all your equipment!\n");
	}
	else if (0 == strcmp(choice, "calm")) {
		printf("THE HUNT IS OVER! You are dead in the water. Mosquitos feast on your unlucky route!\n");
	}
}

// cave
void cavern(void) {
	char choice[50];
	printf("nearside or farside?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "nearside")) {
		nearside();
	}
	else if (0 == strcmp(choice, "farside")) {
		printf("THE HUNT IS WON! You found the Wumpus. Quick Shoot.\n");
	}
}

// cliffs
void ledges(void) {
	char choice[50];
	printf("high or low?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "high")) {
		high();
	}
	else if (0 == strcmp(choice, "low")) {
		printf("The HUNT IS OVER! Your hunt was uneventful.");
	}
}

void peaks(void) {
	char choice[50];
	printf("snow or tree-line?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "snow")) {
		printf("THE HUNT IS OVER! An avalanche buries your party.\n");
	}
	else if (0 == strcmp(choice, "tree-line")) {
		treeline();
	}
}

// forest
void redwood(void) {
	char choice[50];
	printf("ground or canopy?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "ground")) {
		ground();
	}
	else if (0 == strcmp(choice, "canopy")) {
		printf("THE HUNT IS OVER! You fell from the top of a very tall tree!\n");
	}
}

void pine(void) {
	char choice[50];
	printf("conifer or shrub?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "conifer")) {
		printf("THE HUNT IS OVER! It is a sappy ending!\n");
	}
	else if (0 == strcmp(choice, "shrub")) {
		printf("THE HUNT IS OVER! You caught a snipe, but not a wumpus!\n");
	}
}

// hardwood
void hardwood(void) {
	char choice[50];
	printf("oak or maple?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "oak")) {
		printf("THE HUNT IS OVER! You are lost!\n");
	}
	else if (0 == strcmp(choice, "maple")) {
		maple();
	}
}

// fourth locations
// cave -> cavern
void nearside(void) {
	char choice[50];
	printf("lookup or lookdown?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "lookup")) {
		printf("THE HUNT IS OVER! You fell in a bottomless pit!d\n");
	}
	else if (0 == strcmp(choice, "lookdown")) {
		printf("THE HUNT IS OVER! A giant bat carried you off!\n");
	}
}

// cliffs -> ledges
void high(void) {
	char choice[50];
	printf("eagle or rattlesnake?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "eagle")) {
		printf("THE HUNT IS OVER! An eagle plucked your eyes out!\n");
	}
	else if (0 == strcmp(choice, "rattlesnake")) {
		printf("THE HUNT IS OVER! Why? Of course, it bit you!\n");
	}
}

// cliffs -> peaks
void treeline(void) {
	char choice[50];
	printf("crag or cave?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "crag")) {
		printf("THE HUNT IS OVER! Though, you smelled wumpus in the area!\n");
	}
	else if (0 == strcmp(choice, "cave")) {
		printf("THE HUNT IS WON! You found the wumpus!\n");
	}
}

// forest -> redwood
void ground(void) {
	char choice[50];
	printf("humboldt or calaveras?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "humboldt")) {
		printf("THE HUNT IS OVER! Hippies surround you in a drum circle!\n");
	}
	else if (0 == strcmp(choice, "calaveras")) {
		printf("THE HUNT IS OVER! Loggers stopped you to count your rings!\n");
	}
}

// forest -> hardwood
void maple(void) {
	char choice[50];
	printf("pancakes, waffles, or frenchtoast?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "pancakes")) {
		pancakes();
	}
	else if (0 == strcmp(choice, "waffles")) {
		waffles();
	}
	else if (0 == strcmp(choice, "frenchtoast")) {
		printf("THE HUNT IS OVER!\n But french toast is not a bad idea!\n");
	}
}

// fifth location
// hardwood -> maple
void pancakes(void) {
	char choice[50];
	printf("chocolatechip or blueberry?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "chocolatechip")) {
		printf("THE HUNT IS OVER! You are distracted!\n");
	}
	else if (0 == strcmp(choice, "blueberry")) {
		printf("THE HUNT IS OVER! You take the bait\n");
	}
}

void waffles(void) {
	char choice[50];
	printf("regular or wholewheat?\n");
	scanf("%s", choice);
	if (0 == strcmp(choice, "regular")) {
		printf("THE HUNT IS OVER!\n You fell asleep\n");
	}
	else if (0 == strcmp(choice, "wholewheat")) {
		printf("THE HUNT IS OVER!\n Nature calls!\n");
	}
}

// actual function
int main(void) {
	printf("You are at the beginning of a Wumpus Hunt. Where shall we hunt?: river, cave, forest, or cliffs?\n");
	choice1();
	//printf("%s\n", firstHunt);
	return 0;
}
