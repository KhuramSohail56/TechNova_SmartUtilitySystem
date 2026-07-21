#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Item {
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    Item(int id, string name, double price, int quantity) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setQuantity(int q) { quantity = q; }

    void displayItem() const {
        cout << left << setw(10) << id 
             << setw(20) << name 
             << setw(12) << fixed << setprecision(2) << price 
             << setw(10) << quantity << endl;
    }
};

struct CartItem {
    int id;
    string name;
    double price;
    int quantity;
    double total;
};

class UtilitySystem {
private:
    vector<Item> inventory;
    const string filename = "inventory_data.txt";

public:
    UtilitySystem() {
        loadFromFile();
    }

    ~UtilitySystem() {
        saveToFile();
    }

    void addItem() {
        int id, qty;
        string name;
        double price;

        cout << "\n--- Add New Item ---\n";
        cout << "Enter Item ID: ";
        cin >> id;
        
        for (const auto& item : inventory) {
            if (item.getId() == id) {
                cout << "Error: Item with ID " << id << " already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Item Name: ";
        getline(cin, name);
        cout << "Enter Price: PKR ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> qty;

        inventory.push_back(Item(id, name, price, qty));
        saveToFile();
        cout << "Item added successfully!\n";
    }

    void displayAllItems() const {
        if (inventory.empty()) {
            cout << "\nNo items available in the inventory.\n";
            return;
        }

        cout << "\n=================== CURRENT INVENTORY ===================\n";
        cout << left << setw(10) << "ID" 
             << setw(20) << "Item Name" 
             << setw(12) << "Price (PKR)" 
             << setw(10) << "Stock Qty" << endl;
        cout << "---------------------------------------------------------\n";

        for (const auto& item : inventory) {
            item.displayItem();
        }
        cout << "=========================================================\n";
    }

    void generateBill() {
        if (inventory.empty()) {
            cout << "\nInventory is empty. Cannot process order.\n";
            return;
        }

        vector<CartItem> cart;
        string input;

        displayAllItems();
        cout << "\n--- Start Purchasing ---\n";
        cout << "(Enter Item ID to add, or type 'done' to finish order)\n";

        while (true) {
            cout << "\nEnter Item ID (or 'done'): ";
            cin >> input;

            if (input == "done" || input == "DONE" || input == "Done") {
                break;
            }

            int id;
            try {
                id = stoi(input);
            } catch (...) {
                cout << "Invalid input! Please enter a valid Item ID or 'done'.\n";
                continue;
            }

            bool found = false;
            for (auto& item : inventory) {
                if (item.getId() == id) {
                    found = true;
                    int qty;
                    cout << "Enter Quantity for " << item.getName() << ": ";
                    cin >> qty;

                    if (qty <= 0) {
                        cout << "Quantity must be greater than 0!\n";
                        break;
                    }

                    if (qty > item.getQuantity()) {
                        cout << "Insufficient stock! Available: " << item.getQuantity() << endl;
                        break;
                    }

                    double itemTotal = qty * item.getPrice();
                    item.setQuantity(item.getQuantity() - qty);

                    cart.push_back({item.getId(), item.getName(), item.getPrice(), qty, itemTotal});
                    cout << "-> Added " << qty << " x " << item.getName() << " to cart.\n";
                    break;
                }
            }

            if (!found) {
                cout << "Invalid Item ID! Please try again.\n";
            }
        }

        if (cart.empty()) {
            cout << "\nNo items were added to the cart. Order cancelled.\n";
            return;
        }

        double grandTotal = 0.0;
        cout << "\n=========================================================\n";
        cout << "                    FINAL BILL RECEIPT                   \n";
        cout << "=========================================================\n";
        cout << left << setw(20) << "Item Name" 
             << setw(10) << "Qty" 
             << setw(12) << "Price" 
             << setw(12) << "Total" << endl;
        cout << "---------------------------------------------------------\n";

        for (const auto& cartItem : cart) {
            cout << left << setw(20) << cartItem.name 
                 << setw(10) << cartItem.quantity 
                 << setw(12) << fixed << setprecision(2) << cartItem.price 
                 << setw(12) << cartItem.total << endl;
            grandTotal += cartItem.total;
        }

        cout << "---------------------------------------------------------\n";
        cout << "GRAND TOTAL: PKR " << fixed << setprecision(2) << grandTotal << endl;
        cout << "=========================================================\n";

        saveToFile();
    }

    void saveToFile() const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error opening file for writing!\n";
            return;
        }

        for (const auto& item : inventory) {
            outFile << item.getId() << ","
                    << item.getName() << ","
                    << item.getPrice() << ","
                    << item.getQuantity() << "\n";
        }
        outFile.close();
    }

    void loadFromFile() {
        inventory.clear();
        ifstream inFile(filename);
        if (!inFile) {
            return;
        }

        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                int id = stoi(line.substr(0, pos1));
                string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                double price = stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
                int qty = stoi(line.substr(pos3 + 1));

                inventory.push_back(Item(id, name, price, qty));
            }
        }
        inFile.close();
    }
};

int main() {
    UtilitySystem system;
    int choice;

    do {
        cout << "\n=========================================\n";
        cout << "  SMART UTILITY & BILLING MANAGEMENT SYSTEM\n";
        cout << "=========================================\n";
        cout << "1. Display All Items\n";
        cout << "2. Add New Item\n";
        cout << "3. Generate Order / Bill\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.displayAllItems();
                break;
            case 2:
                system.addItem();
                break;
            case 3:
                system.generateBill();
                break;
            case 4:
                cout << "\nSaving data and exiting application... Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}