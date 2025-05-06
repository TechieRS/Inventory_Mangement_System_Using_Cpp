#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

class Item
{
private:
    int id;
    string name;
    int quantity;
    float price;
    string supplier;

public:
    Item() {}

    Item(int i, string n, int q, float p, string s)
    {
        id = i;
        name = n;
        quantity = q;
        price = p;
        supplier = s;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    float getPrice() const { return price; }
    string getSupplier() const { return supplier; }

    void setQuantity(int q) { quantity = q; }
    void setPrice(float p) { price = p; }

    void display() const
    {
        cout << left << setw(5) << id << setw(20) << name << setw(10) << quantity
            << setw(10) << fixed << setprecision(2) << price << setw(20) << supplier << endl;
    }
};

class Inventory
{
private:
    vector<Item> items;
    string filename = "inventory.txt";
    int lowStockThreshold = 5;

    bool idExists(int id) const
    {
        return any_of(items.begin(), items.end(), [id](const Item &i)
                    { return i.getId() == id; });
    }

public:
    Inventory() { loadFromFile(); }

    void addItem()
    {
        int id, quantity;
        float price;
        string name, supplier;

        cout << "Enter Item ID: ";
        cin >> id;
        if (idExists(id))
        {
            cout << "Error: Duplicate ID not allowed.\n";
            return;
        }

        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Quantity: ";
        cin >> quantity;
        if (quantity < 0)
        {
            cout << "Error: Quantity can't be negative.\n";
            return;
        }

        cout << "Enter Price: ";
        cin >> price;
        if (price < 0)
        {
            cout << "Error: Price can't be negative.\n";
            return;
        }

        cin.ignore();
        cout << "Enter Supplier: ";
        getline(cin, supplier);

        items.emplace_back(id, name, quantity, price, supplier);
        cout << "Item added successfully!\n";
    }

    void updateItem()
    {
        int id;
        cout << "Enter Item ID to update: ";
        cin >> id;
        for (auto &item : items)
        {
            if (item.getId() == id)
            {
                int quantity;
                float price;
                cout << "Enter New Quantity: ";
                cin >> quantity;
                if (quantity < 0)
                {
                    cout << "Quantity can't be negative.\n";
                    return;
                }
                item.setQuantity(quantity);

                cout << "Enter New Price: ";
                cin >> price;
                if (price < 0)
                {
                    cout << "Price can't be negative.\n";
                    return;
                }
                item.setPrice(price);

                cout << "Item updated.\n";
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void deleteItem()
    {
        int id;
        cout << "Enter Item ID to delete: ";
        cin >> id;
        auto it = remove_if(items.begin(), items.end(), [id](const Item &i)
                            { return i.getId() == id; });
        if (it != items.end())
        {
            items.erase(it, items.end());
            cout << "Item deleted.\n";
        }
        else
        {
            cout << "Item not found.\n";
        }
    }

    void searchItem()
    {
        string key;
        cin.ignore();
        cout << "Search by (name or ID): ";
        getline(cin, key);

        bool found = false;
        for (const auto &item : items)
        {
            if (to_string(item.getId()) == key || item.getName() == key)
            {
                item.display();
                found = true;
            }
        }
        if (!found)
            cout << "Item not found.\n";
    }

    void sortItems()
    {
        int choice;
        cout << "Sort by:\n1. Name\n2. Price\n3. Quantity\nChoice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            sort(items.begin(), items.end(), [](const Item &a, const Item &b)
                { return a.getName() < b.getName(); });
            break;
        case 2:
            sort(items.begin(), items.end(), [](const Item &a, const Item &b)
                { return a.getPrice() < b.getPrice(); });
            break;
        case 3:
            sort(items.begin(), items.end(), [](const Item &a, const Item &b)
                { return a.getQuantity() < b.getQuantity(); });
            break;
        default:
            cout << "Invalid choice.\n";
            return;
        }
        cout << "Items sorted.\n";
    }

    void showLowStock()
    {
        cout << "Items with low stock (quantity < " << lowStockThreshold << "):\n";
        for (const auto &item : items)
        {
            if (item.getQuantity() < lowStockThreshold)
            {
                item.display();
            }
        }
    }

    void updateLowStock()
    {
        cout << "Current low stock threshold: " << lowStockThreshold << endl;
        cout << "Enter new low stock threshold: ";
        cin >> lowStockThreshold;
        cout << "Threshold updated.\n";
    }

    void supplierView()
    {
        string supplier;
        cin.ignore();
        cout << "Enter Supplier Name: ";
        getline(cin, supplier);
        for (const auto &item : items)
        {
            if (item.getSupplier() == supplier)
            {
                item.display();
            }
        }
    }

    void inventoryValue()
    {
        float total = 0;
        for (const auto &item : items)
        {
            total += item.getPrice() * item.getQuantity();
        }
        cout << "Total Inventory Value: " << fixed << setprecision(2) << total << "\n";
    }

    void displayItems()
    {
        cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Qty"
            << setw(10) << "Price" << setw(20) << "Supplier" << endl;
        cout << string(65, '-') << endl;
        for (const auto &item : items)
            item.display();
    }

    void saveToFile()
    {
        ofstream out(filename);
        for (const auto &item : items)
        {
            out << item.getId() << "," << item.getName() << "," << item.getQuantity() << ","
                << item.getPrice() << "," << item.getSupplier() << "\n";
        }
        out.close();
        cout << "Inventory saved to file.\n";
    }

    void loadFromFile()
    {
        ifstream in(filename);
        items.clear();
        string line;
        while (getline(in, line))
        {
            int id, qty;
            float price;
            string name, supplier;

            size_t pos;
            pos = line.find(",");
            id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(",");
            name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            qty = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(",");
            price = stof(line.substr(0, pos));
            line.erase(0, pos + 1);

            supplier = line;

            items.emplace_back(id, name, qty, price, supplier);
        }
        in.close();
    }
};

string hashPassword(const string &password)
{
    int hash = 0;
    for (char c : password)
        hash += c * 31;
    return to_string(hash);
}

bool login()
{
    const string correctUsername = "admin";
    const string correctPasswordHash = hashPassword("admin123");

    string user, pass;
    while (true)
    {
        cout << "Enter username: ";
        cin >> user;
        cout << "Enter password: ";
        cin >> pass;

        if (user == correctUsername && hashPassword(pass) == correctPasswordHash)
        {
            cout << "Login successful.\n";
            return true;
        }
        else
        {
            cout << "Login failed. Try again.\n";
        }
    }
}

int main()
{
    Inventory inv;

    cout << "==== Inventory Management System ====\n";
    login();

    int choice;
    do
    {
        cout << "\n1. Add Item\n2. Update Item\n3. Delete Item\n4. Search Item\n"
            << "5. Sort Items\n6. Show Low Stock\n7. Update Low Stock\n"
            << "8. Inventory Value\n9. Display All Items\n10. Supplier View\n11. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            inv.addItem();
            break;
        case 2:
            inv.updateItem();
            break;
        case 3:
            inv.deleteItem();
            break;
        case 4:
            inv.searchItem();
            break;
        case 5:
            inv.sortItems();
            break;
        case 6:
            inv.showLowStock();
            break;
        case 7:
            inv.updateLowStock();
            break;
        case 8:
            inv.inventoryValue();
            break;
        case 9:
            inv.displayItems();
            break;
        case 10:
            inv.supplierView();
            break;
        case 11:
            inv.saveToFile();
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 11);

    return 0;
}