#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 10
#define MAX_ENEMIES 3
#define MAX_ROOMS 5

void room1();
void room2();
void room3();
void room4();
void room5();
void battle();
void display_inventory();
void save_game();
void load_game();

char inventory[MAX_ITEMS][20]; // Array to hold items
int item_count = 0; // Current count of items in inventory
int health = 100;   // Player health
int current_room = 1; // Tracks the current room

void save_game() {
    FILE *file = fopen("savegame.txt", "w");
    if (file) {
        fprintf(file, "%d\n", health);
        fprintf(file, "%d\n", item_count);
        for (int i = 0; i < item_count; i++) {
            fprintf(file, "%s\n", inventory[i]);
        }
        fclose(file);
        printf("Game saved successfully.\n");
    } else {
        printf("Error saving the game.\n");
    }
}

void load_game() {
    FILE *file = fopen("savegame.txt", "r");
    if (file) {
        fscanf(file, "%d", &health);
        fscanf(file, "%d", &item_count);
        for (int i = 0; i < item_count; i++) {
            fscanf(file, "%s", inventory[i]);
        }
        fclose(file);
        printf("Game loaded successfully.\n");
    } else {
        printf("No saved game found.\n");
    }
}

void room1() {
    int choice;
    printf("You are in a dark room. There are two doors: one to the left and one to the right.\n");
    printf("1. Go through the left door.\n");
    printf("2. Go through the right door.\n");
    printf("3. Save Game\n");
    printf("4. Load Game\n");
    printf("What do you want to do? ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            current_room = 2;
            room2();
            break;
        case 2:
            current_room = 3;
            room3();
            break;
        case 3:
            save_game();
            room1();
            break;
        case 4:
            load_game();
            room1();
            break;
        default:
            printf("Invalid choice. Try again.\n");
            room1();
            break;
    }
}

void room2() {
    int choice;
    printf("You enter a room filled with treasure! What do you want to do?\n");
    printf("1. Take some treasure.\n");
    printf("2. Go to the next room.\n");
    printf("3. Go back to the previous room.\n");
    printf("What do you want to do? ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (item_count < MAX_ITEMS) {
                strcpy(inventory[item_count], "Treasure");
                item_count++;
                printf("You took some treasure! You can use it later.\n");
            } else {
                printf("Your inventory is full!\n");
            }
            room2();
            break;
        case 2:
            current_room = 4;
            room4();
            break;
        case 3:
            current_room = 1;
            room1();
            break;
        default:
            printf("Invalid choice. Try again.\n");
            room2();
            break;
    }
}

void room3() {
    int choice;
    printf("You enter a room with a fierce dragon!\n");
    printf("1. Fight the dragon.\n");
    printf("2. Run away back to the previous room.\n");
    printf("What do you want to do? ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            battle();
            break;
        case 2:
            current_room = 1;
            room1();
            break;
        default:
            printf("Invalid choice. Try again.\n");
            room3();
            break;
    }
}

void room4() {
    int choice;
    printf("You find yourself in a mysterious forest. There's a shiny sword on the ground!\n");
    printf("1. Pick up the sword.\n");
    printf("2. Leave the sword and go back.\n");
    printf("3. Combine items (if you have two items).\n");
    printf("What do you want to do? ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (item_count < MAX_ITEMS) {
                strcpy(inventory[item_count], "Sword");
                item_count++;
                printf("You picked up a sword! You can use it in battles.\n");
            } else {
                printf("Your inventory is full!\n");
            }
            room1();
            break;
        case 2:
            current_room = 1;
            room1();
            break;
        case 3:
            // Combine items (basic example)
            if (item_count >= 2) {
                printf("You combined items successfully!\n");
                // For simplicity, just remove one item
                item_count--;
            } else {
                printf("You don't have enough items to combine.\n");
            }
            room4();
            break;
        default:
            printf("Invalid choice. Try again.\n");
            room4();
            break;
    }
}

void battle() {
    printf("You engage in battle with the dragon!\n");
    int dragon_health = 80;
    int damage = 20;

    while (dragon_health > 0 && health > 0) {
        printf("Your Health: %d | Dragon's Health: %d\n", health, dragon_health);
        printf("1. Attack with sword.\n");
        printf("2. Use health potion (only if you have one).\n");
        printf("3. Run away.\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("You attack the dragon with your sword!\n");
                dragon_health -= damage;
                printf("You deal %d damage to the dragon.\n", damage);
                break;
            case 2:
                if (item_count > 0 && strcmp(inventory[item_count - 1], "Health Potion") == 0) {
                    health += 30; // Heal 30 health points
                    printf("You used a Health Potion and healed 30 points! Your health is now %d.\n", health);
                    item_count--; // Remove health potion from inventory
                } else {
                    printf("You have no health potion!\n");
                }
                break;
            case 3:
                printf("You run away safely!\n");
                current_room = 1;
                room1();
                return;
            default:
                printf("Invalid choice. Try again.\n");
                continue;
        }

        // Dragon attacks
        int dragon_attack = 15;
        health -= dragon_attack;
        printf("The dragon attacks you! You take %d damage. Your health is now %d.\n", dragon_attack, health);
    }

    if (dragon_health <= 0) {
        printf("You defeated the dragon! You win!\n");
        exit(0);
    } else {
        printf("You have been defeated. Game over.\n");
        exit(0);
    }
}

void display_inventory() {
    printf("Your Inventory:\n");
    for (int i = 0; i < item_count; i++) {
        printf("- %s\n", inventory[i]);
    }
}

int main() {
    printf("Welcome to the Adventure Game!\n");
    while (1) {
        room1();
    }
    return 0;
}
