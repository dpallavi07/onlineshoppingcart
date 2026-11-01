
#include <stdio.h>

#define PRODUCTS 5

struct Product {
    int id;
    char name[30];
    float price;
};

struct Product catalog[PRODUCTS] = {
    {1, "T-Shirt", 499.00},
    {2, "Jeans", 899.00},
    {3, "Shoes", 1499.00},
    {4, "Watch", 799.00},
    {5, "Backpack", 999.00}
};

int cart[PRODUCTS] = {0};

/* Display product catalog */
void displayProducts(void)
{
    int i;

    printf("\n========== PRODUCT CATALOG ==========\n");
    printf("%-5s %-15s %10s\n", "ID", "Product", "Price");
    printf("-------------------------------------\n");

    for (i = 0; i < PRODUCTS; i++) {
        printf("%-5d %-15s Rs. %7.2f\n",
               catalog[i].id,
               catalog[i].name,
               catalog[i].price);
    }
}

/* Add product to cart */
void addToCart(void)
{
    int id, quantity;

    displayProducts();

    printf("\nEnter product ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }

    if (id < 1 || id > PRODUCTS) {
        printf("Product not found!\n");
        return;
    }

    printf("Enter quantity: ");
    if (scanf("%d", &quantity) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }

    if (quantity <= 0) {
        printf("Quantity must be greater than zero!\n");
        return;
    }

    cart[id - 1] += quantity;

    printf("%s added to cart successfully!\n",
           catalog[id - 1].name);
}

/* View cart */
void viewCart(void)
{
    int i, found = 0;
    float subtotal = 0;

    printf("\n========== YOUR SHOPPING CART ==========\n");
    printf("%-15s %8s %10s %10s\n",
           "Product", "Quantity", "Price", "Amount");
    printf("------------------------------------------------\n");

    for (i = 0; i < PRODUCTS; i++) {
        if (cart[i] > 0) {
            float amount = catalog[i].price * cart[i];

            printf("%-15s %8d %10.2f %10.2f\n",
                   catalog[i].name,
                   cart[i],
                   catalog[i].price,
                   amount);

            subtotal += amount;
            found = 1;
        }
    }

    if (!found) {
        printf("Your cart is empty!\n");
    } else {
        printf("------------------------------------------------\n");
        printf("Subtotal: Rs. %.2f\n", subtotal);
    }
}

/* Remove item from cart */
void removeItem(void)
{
    int id;

    viewCart();

    printf("\nEnter product ID to remove: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }

    if (id < 1 || id > PRODUCTS) {
        printf("Invalid product ID!\n");
        return;
    }

    if (cart[id - 1] == 0) {
        printf("This product is not in your cart!\n");
        return;
    }

    cart[id - 1] = 0;

    printf("%s removed from cart!\n", catalog[id - 1].name);
}

/* Calculate bill and discount */
void calculateBill(void)
{
    int i, found = 0;
    float subtotal = 0;
    float discount = 0;
    float total;

    printf("\n========== FINAL BILL ==========\n");

    for (i = 0; i < PRODUCTS; i++) {
        if (cart[i] > 0) {
            float amount = catalog[i].price * cart[i];

            printf("%s x %d = Rs. %.2f\n",
                   catalog[i].name, cart[i], amount);

            subtotal += amount;
            found = 1;
        }
    }

    if (!found) {
        printf("Your cart is empty! Add products first.\n");
        return;
    }

    if (subtotal >= 1000.00) {
        discount = subtotal * 0.10;
    }

    total = subtotal - discount;

    printf("---------------------------------\n");
    printf("Subtotal       : Rs. %.2f\n", subtotal);
    printf("Discount (10%%) : Rs. %.2f\n", discount);
    printf("Final Amount   : Rs. %.2f\n", total);
    printf("=================================\n");
}

/* Main menu */
int main(void)
{
    int choice;

    while (1) {
        printf("\n====== ONLINE SHOPPING CART ======\n");
        printf("1. View Product Catalog\n");
        printf("2. Add Product to Cart\n");
        printf("3. Remove Item from Cart\n");
        printf("4. View Shopping Cart\n");
        printf("5. Calculate Bill\n");
        printf("6. Exit\n");
        printf("==================================\n");
        printf("Enter your choice: ");
        fflush(stdout);

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            continue;
        }

        switch (choice) {
            case 1:
                displayProducts();
                break;

            case 2:
                addToCart();
                break;

            case 3:
                removeItem();
                break;

            case 4:
                viewCart();
                break;

            case 5:
                calculateBill();
                break;

            case 6:
                printf("Thank you for shopping!\n");
                return 0;

            default:
                printf("Invalid choice! Enter 1 to 6.\n");
        }
    }

    return 0;
}
