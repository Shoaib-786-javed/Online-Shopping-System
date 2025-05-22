#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Product class with category
class Product {
private:
    int id;
    string name;
    string category;
    double price;
public:
    Product(int i, string n, string c, double p) : id(i), name(n), category(c), price(p) {}
    int getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getPrice() const { return price; }
};

// User class with signup/login
class User {
private:
    string username;
public:
    User(string uname) : username(uname) {}
    string getUsername() const { return username; }
};

// Shopping Cart class
class ShoppingCart {
private:
    vector<Product> items;
public:
    void addProduct(const Product& p) {
        items.push_back(p);
        cout << p.getName() << " added to cart!" << endl;
    }
    void showCart() const {
        if (items.empty()) {
            cout << "\nYour cart is empty." << endl;
            return;
        }
        cout << "\nYour Cart:" << endl;
        double total = 0;
        for (size_t i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].getName() << " (" << items[i].getCategory() << ") - Rs. " << items[i].getPrice() << endl;
            total += items[i].getPrice();
        }
        cout << "Total: Rs. " << total << endl;
    }
    vector<Product> getItems() const { return items; }
    void clearCart() { items.clear(); }
    bool isEmpty() const { return items.empty(); }
};

// Order class
class Order {
private:
    vector<Product> orderedItems;
    string username;
    double totalAmount;
public:
    Order(const vector<Product>& items, const string& uname) : orderedItems(items), username(uname), totalAmount(0) {
        for (const auto& item : orderedItems) {
            totalAmount += item.getPrice();
        }
    }
    void showOrder() const {
        cout << "\nOrder placed by: " << username << endl;
        cout << "Order details:" << endl;
        for (size_t i = 0; i < orderedItems.size(); i++) {
            cout << i + 1 << ". " << orderedItems[i].getName() << " (" << orderedItems[i].getCategory() << ") - Rs. " << orderedItems[i].getPrice() << endl;
        }
        cout << "Total Amount: Rs. " << totalAmount << endl;
    }
};

int main() {
    // Predefined products with categories
    vector<Product> products = {
        // Clothes
        Product(1, "Shirt", "Clothes", 1200),
        Product(2, "Pants", "Clothes", 1500),
        Product(3, "Trousers", "Clothes", 1800),
        // Jewelry
        Product(4, "Necklace", "Jewelry", 5000),
        Product(5, "Earrings", "Jewelry", 3000),
        Product(6, "Bangles", "Jewelry", 2500),
        // Makeup
        Product(7, "Concealer", "Makeup", 800),
        Product(8, "Foundation", "Makeup", 1500),
        Product(9, "Lipstick", "Makeup", 600),
        // Shoes
        Product(10, "Joggers", "Shoes", 2200),
        Product(11, "Sandals", "Shoes", 1300),
        Product(12, "Slippers", "Shoes", 700)
    };

    vector<string> registeredUsers; // to store signed up usernames
    string uname;
    int signupChoice;

    cout << "Welcome! Please select:\n1. Sign Up\n2. Sign In\nEnter choice: ";
    cin >> signupChoice;
    cin.ignore(10000, '\n');

    if (signupChoice == 1) {
        cout << "Sign Up - Enter a new username: ";
        getline(cin, uname);
        // Simple check to avoid duplicate usernames
        bool exists = false;
        for (const auto& user : registeredUsers) {
            if (user == uname) {
                exists = true;
                break;
            }
        }
        if (exists) {
            cout << "Username already exists. Please restart and sign in." << endl;
            return 0;
        }
        registeredUsers.push_back(uname);
        cout << "Sign up successful! Please sign in now." << endl;
        cout << "Enter your username to login: ";
        getline(cin, uname);
    } else if (signupChoice == 2) {
        cout << "Enter your username to login: ";
        getline(cin, uname);
    } else {
        cout << "Invalid choice. Exiting." << endl;
        return 0;
    }

    User user(uname);
    ShoppingCart cart;
    vector<Order> orderHistory;
    int choice;

    cout << "\nWelcome, " << user.getUsername() << "!" << endl;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Browse Products by Category\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Place Order\n";
        cout << "5. View Order History\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        switch (choice) {
            case 1: {
                cout << "\nCategories:\n1. Clothes\n2. Jewelry\n3. Makeup\n4. Shoes\n";
                cout << "Enter category number to browse: ";
                int catChoice;
                if (!(cin >> catChoice)) {
                    cout << "Invalid input!" << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }
                cin.ignore(10000, '\n');
                string category;
                switch (catChoice) {
                    case 1: category = "Clothes"; break;
                    case 2: category = "Jewelry"; break;
                    case 3: category = "Makeup"; break;
                    case 4: category = "Shoes"; break;
                    default:
                        cout << "Invalid category choice." << endl;
                        continue;
                }
                cout << "\nProducts in " << category << ":" << endl;
                for (const auto& product : products) {
                    if (product.getCategory() == category) {
                        cout << product.getId() << ". " << product.getName() << " - Rs. " << product.getPrice() << endl;
                    }
                }
                break;
            }
            case 2: {
                cout << "\nEnter product ID to add to cart: ";
                int prodId;
                if (!(cin >> prodId)) {
                    cout << "Invalid input! Please enter a valid product ID." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }
                cin.ignore(10000, '\n');
                bool found = false;
                for (const auto& product : products) {
                    if (product.getId() == prodId) {
                        cart.addProduct(product);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Product ID not found. Please try again." << endl;
                }
                break;
            }
            case 3: {
                cart.showCart();
                break;
            }
            case 4: {
                if (cart.isEmpty()) {
                    cout << "Your cart is empty. Add products before placing an order." << endl;
                } else {
                    Order newOrder(cart.getItems(), user.getUsername());
                    orderHistory.push_back(newOrder);
                    newOrder.showOrder();
                    cart.clearCart();
                }
                break;
            }
            case 5: {
                if (orderHistory.empty()) {
                    cout << "No orders placed yet." << endl;
                } else {
                    cout << "\nOrder History:" << endl;
                    for (size_t i = 0; i < orderHistory.size(); i++) {
                        cout << "\nOrder #" << i + 1 << ":" << endl;
                        orderHistory[i].showOrder();
                    }
                }
                break;
            }
            case 0: {
                cout << "Thank you for shopping with us. Goodbye!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        } // <-- closes switch
    } // <-- closes while
    return 0;
} // <-- closes main
