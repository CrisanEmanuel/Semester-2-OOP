#pragma once

typedef struct{
    char* type;
    float area;
    char* address;
    float price;
} Offer;

/**
 * Create a new offer
 */
Offer createOffer(char *type, float area, char *address, float price);

/**
 * Deallocate memory occupied by offer
 */
void destroyOffer(Offer *o);

/**
 * Verifica daca doua oferte sunt la fel, daca da returneaza 1, 0 altfel
 */
int eq(Offer o, Offer other);