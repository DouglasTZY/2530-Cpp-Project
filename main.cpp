#include <iostream> 
#include <fstream> 
#include <cstring> 
using namespace std; 

struct Product {
	int id; 
	char name[50]; 
	double price; 
	int quantity; 
}; 

struct Node {
	Product data; 
	Node* next; 
}; 

class ProductList {
    private: 
        Node* head; 

    public: 
        ProductList() {
            head = NULL; 
        }    

        ~ProductList() {
            Node* temp; 
            while(head != NULL) {
                temp = head; 
                head = head->next; 
                delete temp; 
            } 
        } 

        void addProduct(Product p) {
            Node* newNode = new Node; 
            newNode->data = p; 
            newNode->next = NULL; 

            if(head == NULL) {
                head = newNode; 
            } else {
                Node* cur = head; 
                while(cur->next != NULL) {
                    cur = cur->next; 
                } 
                cur->next = newNode; 
            }
        } 

        void displayProducts() {
            Node* cur = head; 
            if(cur == NULL) {
                cout << "No products available.\n"; 
                return; 
            } 

            cout << "\nID\tName\t\tPrice\tQty\n"; 
            while(cur != NULL) {
                cout << cur->data.id << "\t"
                     << cur->data.name << "\t\t"
                     << cur->data.price << "\t"
                     << cur->data.quantity << endl;
                cur = cur->next;
            }
        } 

        void sortByPrice() {
            if(head == NULL || head->next == NULL) {
                return; 
            } 

            bool swapped; 
            Node* ptr1; 
            Node* lptr = NULL; 

            do {
                swapped = false; 
                ptr1 = head; 

                while(ptr1->next != lptr) {
                    if(ptr1->data.price > ptr1->next->data.price) {
                        Product temp = ptr1->data; 
                        ptr1->data = ptr1->next->data; 
                        ptr1->next->data = temp; 
                        swapped = true; 
                    } 
                    ptr1 = ptr1->next; 
                } 
                lptr = ptr1; 
            } while(swapped); 
        } 

        bool searchByID(int targetID) {
            Node* cur = head; 

            while(cur != NULL) {
                if(cur->data.id == targetID) {
                    cout << "\nProduct Found: \n"; 
                    cout << "ID: " << cur->data.id << endl; 
                    cout << "Name: " << cur->data.name << endl; 
                    cout << "Price: " << cur->data.price << endl; 
                    cout << "Quantity: " << cur->data.quantity << endl; 

                    return true; 
                } 
                cur = cur->next; 
            } 

            cout << "Product not found.\n"; 

            return false; 
        } 

        bool purchaseProduct(int productID, int quantity) {
            Node* cur = head; 

            while(cur != NULL) {
                if(cur->data.id == productID) {

                    if(cur->data.quantity < quantity) {
                        cout << "Not enough stock.\n"; 

                        return false; 
                    } 

                    cur->data.quantity -= quantity; 
                    saveToFile(); // update product.txt 

                    // write in sales.txt 
                    try {
                        ofstream saleFile("sales.txt", ios::app); 
                        if (!saleFile)
                            throw "File cannot be opened.";

                        saleFile << cur->data.id << "|" 
                                 << cur->data.name << "|" 
                                 << quantity << "|" 
                                 << cur->data.price * quantity << endl; 
                    
                        saleFile.close();  
                    }
                    catch (const char* msg) {
                        cout << msg << endl;
                    }
                    
                    cout << "Purchase successful!\n"; 
                    cout << "Total: RM " << cur->data.price * quantity << endl; 

                    return true; 
                } 

                cur = cur->next; 
            } 

            cout << "Product not found.\n"; 

            return false; 
        } 

        bool deleteProduct(int productID) {
            if(head == NULL) {
                cout << "No products to delete.\n"; 

                return false; 
            } 

            // if want to delete the first node 
            if(head->data.id == productID) {
                Node* temp = head; 
                head = head->next; 
                delete temp; 
                saveToFile(); 

                cout << "Product deleted successfully.\n"; 

                return true; 
            } 

            Node* cur = head; 
            Node* prev = NULL; 

            while(cur != NULL && cur->data.id != productID) {
                prev = cur; 
                cur = cur->next; 
            } 

            if(cur == NULL) {
                cout << "Product not found.\n"; 

                return false; 
            } 

            prev->next = cur->next; 
            delete cur; 
            saveToFile(); 

            cout << "Product deleted successfully.\n"; 

            return true; 
        } 
 
        void saveToFile() {
            try {
                ofstream outFile("product.txt"); 
                if (!outFile)
                    throw "File cannot be opened.";

                Node* cur = head; 
                while(cur != NULL) {
                    outFile << cur->data.id << "|"
                            << cur->data.name << "|" 
                            << cur->data.price << "|" 
                            << cur->data.quantity << endl; 
                    cur = cur->next;       
                } 

                outFile.close(); 
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        } 

        void loadFromFile() {
            try {
                ifstream inFile("product.txt"); 
                if(!inFile)
                    throw "File cannot be opened.";

                Product p; 
                char line[200]; 

                while(inFile.getline(line, 200)) {
                    sscanf(line, "%d|%[^|]|%lf|%d", &p.id, p.name, &p.price, &p.quantity); 
                    addProduct(p); 
                } 

                inFile.close(); 
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        } 

        // ===== PRODUCT MODULE EXTENSION =====

        // Update product price by ID
        bool updateProductPrice(int id) {
            if(head == NULL) {
                cout << "No products available.\n"; 
                return false; 
            } 

            Node* cur = head; 
            bool found = false; 

            // Traverse the linked list to find the product
            while(cur != NULL) {
                if(cur->data.id == id) {
                    found = true; 
                    break; 
                } 
                cur = cur->next; 
            } 

            if(!found) {
                cout << "Product with ID " << id << " not found.\n"; 
                return false; 
            } 

            cout << "\n========== Update Product Price ==========\n"; 
            cout << "Current Product Details:\n"; 
            cout << "ID: " << cur->data.id << endl; 
            cout << "Name: " << cur->data.name << endl; 
            cout << "Current Price: RM " << cur->data.price << endl; 
            cout << "Quantity: " << cur->data.quantity << endl; 

            double newPrice; 
            cout << "\nEnter new price (RM): "; 
            cin >> newPrice; 

            if(newPrice < 0) {
                cout << "Invalid price. Price cannot be negative.\n"; 
                return false; 
            } 

            double oldPrice = cur->data.price; 
            cur->data.price = newPrice; 
            saveToFile(); 

            cout << "\n✓ Price updated successfully!\n"; 
            cout << "Old Price: RM " << oldPrice << " → New Price: RM " << newPrice << endl; 

            return true; 
        } 

        // Update product quantity by ID
        bool updateProductQuantity(int id) {
            if(head == NULL) {
                cout << "No products available.\n"; 
                return false; 
            } 

            Node* cur = head; 
            bool found = false; 

            // Traverse linked list to search for product ID
            while(cur != NULL) {
                if(cur->data.id == id) {
                    found = true; 
                    break; 
                } 
                cur = cur->next; 
            } 

            if(!found) {
                cout << "Product with ID " << id << " not found.\n"; 
                return false; 
            } 

            cout << "\n========== Update Product Quantity ==========\n"; 
            cout << "Current Product Details:\n"; 
            cout << "ID: " << cur->data.id << endl; 
            cout << "Name: " << cur->data.name << endl; 
            cout << "Price: RM " << cur->data.price << endl; 
            cout << "Current Quantity: " << cur->data.quantity << " units\n"; 

            int newQuantity; 
            cout << "\nEnter new quantity: "; 
            cin >> newQuantity; 

            if(newQuantity < 0) {
                cout << "Invalid quantity. Quantity cannot be negative.\n"; 
                return false; 
            } 

            int oldQuantity = cur->data.quantity; 
            cur->data.quantity = newQuantity; 
            saveToFile(); 

            cout << "\n✓ Quantity updated successfully!\n"; 
            cout << "Old Quantity: " << oldQuantity << " → New Quantity: " << newQuantity << endl; 

            return true; 
        } 

        // Check low stock (Quantity < 10) 
        void checkLowStock() {
            if(head == NULL) {
                cout << "No products available.\n"; 
                return; 
            } 

            cout << "\n========== Low Stock Report ==========\n"; 
            cout << "Products with quantity below 10 units:\n\n"; 

            Node* cur = head; 
            int lowStockCount = 0; 
            const int LOW_STOCK_THRESHOLD = 10; 

            // Traverse the entire linked list to find low stock products
            while(cur != NULL) {
                if(cur->data.quantity < LOW_STOCK_THRESHOLD) {
                    lowStockCount++; 
                    cout << "ID: " << cur->data.id << " | "; 
                    cout << "Name: " << cur->data.name << " | "; 
                    cout << "Price: RM " << cur->data.price << " | "; 
                    cout << "Quantity: " << cur->data.quantity << " units"; 

                    if(cur->data.quantity == 0) {
                        cout << " [OUT OF STOCK]"; 
                    } else if(cur->data.quantity < 5) {
                        cout << " [CRITICAL]"; 
                    } 

                    cout << endl; 
                } 
                cur = cur->next; 
            } 

            if(lowStockCount == 0) {
                cout << "All products have sufficient stock (>= 10 units).\n"; 
            } else {
                cout << "\nTotal low stock products: " << lowStockCount << endl; 
            } 
        } 

        // Display products by category
        void displayByCategory() {
            if(head == NULL) {
                cout << "No products available.\n"; 
                return; 
            } 

            cout << "\n========== Products by Category ==========\n"; 

            cout << "\n--- Budget Products (< RM 50) ---\n"; 
            cout << "ID\tName\t\tPrice\tQty\n"; 
            Node* cur = head; 
            int budgetCount = 0; 

            // First traversal: budget category
            while(cur != NULL) {
                if(cur->data.price < 50) {
                    budgetCount++; 
                    cout << cur->data.id << "\t" 
                         << cur->data.name << "\t\t" 
                         << cur->data.price << "\t" 
                         << cur->data.quantity << endl; 
                } 
                cur = cur->next; 
            } 
            if(budgetCount == 0) {
                cout << "No budget products available.\n"; 
            } 

            cout << "\n--- Standard Products (RM 50 - RM 150) ---\n"; 
            cout << "ID\tName\t\tPrice\tQty\n"; 
            cur = head; 
            int standardCount = 0; 

            // Second traversal: standard category
            while(cur != NULL) {
                if(cur->data.price >= 50 && cur->data.price <= 150) {
                    standardCount++; 
                    cout << cur->data.id << "\t" 
                         << cur->data.name << "\t\t" 
                         << cur->data.price << "\t" 
                         << cur->data.quantity << endl; 
                } 
                cur = cur->next; 
            } 
            if(standardCount == 0) {
                cout << "No standard products available.\n"; 
            } 

            cout << "\n--- Premium Products (> RM 150) ---\n"; 
            cout << "ID\tName\t\tPrice\tQty\n"; 
            cur = head; 
            int premiumCount = 0; 

            // Third traversal: premium category
            while(cur != NULL) {
                if(cur->data.price > 150) {
                    premiumCount++; 
                    cout << cur->data.id << "\t" 
                         << cur->data.name << "\t\t" 
                         << cur->data.price << "\t" 
                         << cur->data.quantity << endl; 
                } 
                cur = cur->next; 
            } 
            if(premiumCount == 0) {
                cout << "No premium products available.\n"; 
            } 

            cout << "\n--- Category Summary ---\n"; 
            cout << "Budget Products: " << budgetCount << endl; 
            cout << "Standard Products: " << standardCount << endl; 
            cout << "Premium Products: " << premiumCount << endl; 
        } 

        // Count total products
        int countTotalProducts() {
            if(head == NULL) {
                cout << "No products in the list.\n"; 
                return 0; 
            } 

            int totalProducts = 0; 
            int totalQuantity = 0; 
            double totalValue = 0; 

            Node* cur = head; 

            // Traverse linked list to count products and calculate statistics
            while(cur != NULL) {
                totalProducts++; 
                totalQuantity += cur->data.quantity; 
                totalValue += (cur->data.price * cur->data.quantity); 
                cur = cur->next; 
            } 

            cout << "\n========== Product Inventory Statistics ==========\n"; 
            cout << "Total Product Types: " << totalProducts << endl; 
            cout << "Total Units in Stock: " << totalQuantity << endl; 
            cout << "Total Inventory Value: RM " << totalValue << endl; 

            cout << "\n--- Average Values ---\n"; 
            if(totalProducts > 0) {
                double avgPrice = 0; 
                cur = head; 
                while(cur != NULL) {
                    avgPrice += cur->data.price; 
                    cur = cur->next; 
                } 
                avgPrice /= totalProducts; 

                double avgQuantity = (double)totalQuantity / totalProducts; 
                cout << "Average Price: RM " << avgPrice << endl; 
                cout << "Average Quantity per Product: " << avgQuantity << " units" << endl; 
            } 

            cout << "\n--- Product Type Breakdown ---\n"; 
            cur = head; 
            int count = 1; 
            while(cur != NULL) {
                cout << count << ". " << cur->data.name 
                     << " - Qty: " << cur->data.quantity 
                     << ", Value: RM " << (cur->data.price * cur->data.quantity) << endl; 
                count++; 
                cur = cur->next; 
            } 

            return totalProducts; 
        } 
}; 

class User {
	protected: 
		char username[30]; 
		char password[30]; 
	
	public: 
		User() {
			strcpy(username, ""); 
			strcpy(password, ""); 
		} 

		virtual ~User() {
			// destructor 
		} 

		virtual void menu() = 0; // pure virtual 
}; 

class SalesSummary {
    private: 
        float totalSales; 
        int totalQuantity; 
    
    public: 
        SalesSummary() { 
            totalSales = 0; 
            totalQuantity = 0; 
        } 
        
        void generateReport() {
            try {
                ifstream inFile("purchase.txt"); 
                ofstream outFile("summary.txt"); 

                if(!inFile)
                    throw "Cannot open purchase.txt.";
                if(!outFile)
                    throw "Cannot open summary.txt.";

                char customerName[30], productName[30]; 
                int productID, quantity; 
                float price; 

                while(inFile >> customerName >> productID >> productName >> quantity >> price) {
                    totalQuantity += quantity; 
                    totalSales += quantity * price; 
                } 

                outFile << "===== SALES SUMMARY REPORT =====\n";
                outFile << "Total Quantity Sold: " << totalQuantity << endl;
                outFile << "Total Sales Amount: RM " << totalSales << endl;

                inFile.close();
                outFile.close();

                cout << "Summary report generated successfully.\n";
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        } 
}; 

class Staff : public User { 
    public: 
        static ProductList plist; // all staff can use 
		Staff() {} 
		~Staff() {} 

		void menu() {
			int choice; 
            Product p; 

            do {
                cout << "\n--- Staff ---\n";
                cout << "1. Login\n";
                cout << "2. Register\n";
                cout << "0. Back\n";
                cout << "Enter choice: ";
                try {
                    cin >> choice;
                    if (cin.fail()) {
                        throw "Invalid input. Please enter a number.";
                    }
                }
                catch (const char* msg) {
                    cout << msg << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                if (choice == 1) {
                    if (!login("staff.txt")) return;
                    break;
                } else if (choice == 2) {
                    registerUser("staff.txt");
                } else if (choice == 0) {
                    return;
                }
            } while (true);

			do {
                cout << "\n--- Staff Menu ---\n";
                cout << "1. Add Product\n";
                cout << "2. Display Products\n"; 
                cout << "3. Sort Products by Price\n"; 
                cout << "4. Search Product by ID\n"; 
                cout << "5. Delete Product\n"; 
                cout << "6. Generate Sales Summary\n"; 
                cout << "0. Logout\n";
                cout << "Enter choice: ";
                try {
                    cin >> choice;
                    if (cin.fail()) {
                        throw "Invalid input. Please enter a number.";
                    }
                }
                catch (const char* msg) {
                    cout << msg << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                switch(choice) {
                    case 1: {
                        try {
                            cout << "Enter Product ID: ";
                            cin >> p.id;
                            if (p.id <= 0) throw "Invalid Product ID";
                            cin.ignore();

                            cout << "Enter Product Name: ";
                            cin.getline(p.name, 50);

                            cout << "Enter Price: ";
                            cin >> p.price;
                            if (p.price <= 0) throw "Invalid Price";

                            cout << "Enter Quantity: ";
                            cin >> p.quantity;
                            if (p.quantity < 0) throw "Invalid Quantity";
                        }
                        catch (const char* msg) {
                            cout << msg << endl;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            break;
                        }

                        plist.addProduct(p);
                        plist.saveToFile();  

                        cout << "Product added successfully!\n";
                        break;
                    }

                    case 2:
                        cout << "Display Products (coming soon)\n";
                        break; 
                    case 3: 
                        plist.sortByPrice(); 
                        cout << "Products sorted by price.\n"; 
                        break;     
                    case 4: 
                        int searchID;
                        cout << "Enter Product ID to search: ";
                        cin >> searchID;
                        plist.searchByID(searchID);
                        break;
                    case 5: 
                        int deleteID;
                        cout << "Enter Product ID to delete: ";
                        cin >> deleteID;
                        plist.deleteProduct(deleteID);
                        break; 
                    case 6: {
                        SalesSummary ss; 
                        ss.generateReport(); 
                        break;
                    }     
                    case 0:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid choice!\n";
                }
            } while(choice != 0);
        } 

        bool login(const char* filename) {
            try {
                char userName[30], passWord[30]; 
                char fileUserName[30], filePassWord[30]; 

                cout << "Username: "; 
                cin >> userName; 
                cout << "Password: "; 
                cin >> passWord; 

                ifstream inFile(filename); 
                if(!inFile)
                    throw "File cannot be opened.";

                while(inFile >> fileUserName >> filePassWord) {
                    if(strcmp(userName, fileUserName) == 0 && strcmp(passWord, filePassWord) == 0) {
                        strcpy(username, userName); 
                        strcpy(password, passWord); 
                        inFile.close(); 

                        return true; 
                    } 
                } 

                inFile.close(); 
                cout << "Invalid login.\n"; 

                return false; 
            }
            catch (const char* msg) {
                cout << msg << endl;
                return false;
            }
        } 

        bool registerUser(const char* filename) {
            try {
                char userName[30], passWord[30];

                cout << "New Username: ";
                cin >> userName;
                cout << "New Password: ";
                cin >> passWord;

                ofstream outFile(filename, ios::app);
                if (!outFile)
                    throw "File cannot be opened.";

                outFile << userName << " " << passWord << endl;
                outFile.close();

                cout << "Registration successful.\n"; 

                return true;
            }
            catch (const char* msg) {
                cout << msg << endl;
                return false;
            }
        }
}; 

class Customer : public User {
	public: 
		Customer() {
			// constructor 
		} 

		~Customer() noexcept {
			// destructor 
		} 

		bool login(const char* filename) { 
            try {
                char userName[30], passWord[30]; 
                char fileUserName[30], filePassWord[30]; 

                cout << "Username: "; 
                cin >> userName; 
                cout << "Password: "; 
                cin >> passWord; 

                ifstream inFile(filename); 
                if(!inFile)
                    throw "File cannot be opened.";

                while(inFile >> fileUserName >> filePassWord) {
                    // cout << "[DEBUG] read: " << fileUserName << " " << filePassWord << endl; 

                    if(strcmp(userName, fileUserName) == 0 && strcmp(passWord, filePassWord) == 0) {
                        inFile.close(); 

                        return true; 
                    } 
                } 

                inFile.close(); 
                cout << "Invalid login.\n"; 

                return false; 
            }
            catch (const char* msg) {
                cout << msg << endl;
                return false;
            }
        } 

        bool registerUser(const char* filename) {
            try {
                char userName[30], passWord[30];

                cout << "New Username: ";
                cin >> ws; 
                cin >> userName;
                cout << "New Password: ";
                cin >> passWord;

                ofstream outFile(filename, ios::app);
                if (!outFile)
                    throw "File cannot be opened.";

                outFile << userName << " " << passWord << endl;
                outFile.close();

                cout << "Registration successful.\n"; 

                return true;
            }
            catch (const char* msg) {
                cout << msg << endl;
                return false;
            }
        }

		void menu() {
            int choice; 
            int studentID; 

            do {
                cout << "\n--- Customer ---\n";
                cout << "1. Login\n";
                cout << "2. Register\n";
                cout << "0. Back\n";
                cout << "Enter choice: ";
                try {
                    cin >> choice;
                    if (cin.fail()) {
                        throw "Invalid input. Please enter a number.";
                    }
                }
                catch (const char* msg) {
                    cout << msg << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                if (choice == 1) {
                    if (!login("customer.txt")) return;
                    break;
                } else if (choice == 2) {
                    registerUser("customer.txt");
                } else if (choice == 0) {
                    return;
                }
            } while (true);

            do {
                cout << "\n--- Customer Menu ---\n";
                cout << "1. View Products\n";
                cout << "2. Search Product by ID\n";
                cout << "3. Sort Products by Price\n"; 
                cout << "4. Purchase Product\n"; 
                cout << "0. Logout\n";
                cout << "Enter choice: ";
                try {
                    cin >> choice;
                    if (cin.fail()) {
                        throw "Invalid input. Please enter a number.";
                    }
                }
                catch (const char* msg) {
                    cout << msg << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                switch(choice) {
                    case 1:
                        Staff::plist.displayProducts(); 
                        break;
                    case 2:
                        cout << "Enter Product ID to search: "; 
                        cin >> studentID; 
                        Staff::plist.searchByID(studentID); 
                        break; 
                    case 3: 
                        Staff::plist.sortByPrice(); 
                        cout << "Products sorted by price.\n"; 
                        break; 
                    case 4: {
                        int productID, quantity; 

                        try {
                            cout << "Enter Product ID: "; 
                            cin >> productID;
                            if (productID <= 0)
                                throw "Product ID must be greater than 0";

                            cout << "Enter Quantity: "; 
                            cin >> quantity;

                            if (quantity <= 0)
                                throw "Quantity must be greater than 0";
                        }
                        catch (const char* msg) {
                            cout << msg << endl;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            break;
                        }

                        Staff::plist.purchaseProduct(productID, quantity); 
                        break; 
                    } 
                    case 0:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid choice!\n";
                } 
            } while(choice != 0); 
        }
}; 

// Define the static member
ProductList Staff::plist;

// ===== CUSTOMER PURCHASE HISTORY CLASS =====
class PurchaseHistory {
    private:
        struct Purchase {
            char customerName[50];
            int productID;
            char productName[50];
            int quantity;
            double price;
        };

    public:
        PurchaseHistory() {
            // Constructor
        }

        ~PurchaseHistory() {
            // Destructor
        }

        // View my purchases
        void viewMyPurchases(char username[]) {
            if(strlen(username) == 0) {
                cout << "Invalid username.\n";
                return;
            }

            try {
                ifstream purchaseFile("purchase.txt");
                if(!purchaseFile) {
                    throw "Purchase file cannot be opened.";
                }

                cout << "\n========================================\n";
                cout << "     MY PURCHASE HISTORY\n";
                cout << "     Username: " << username << endl;
                cout << "========================================\n\n";

                string line;
                int purchaseCount = 0;
                double totalSpent = 0;
                int totalItems = 0;

                // Display table header
                cout << "Date\t\tProduct ID\tProduct Name\t\tQty\tPrice\tTotal\n";
                cout << "----\t\t----------\t------------\t\t---\t-----\t-----\n";

                // Read file and filter by customer
                while(getline(purchaseFile, line)) {
                    if(line.empty()) continue;

                    Purchase p;
                    char temp[50];

                    // Parse the line: customerName|productID|productName|quantity|price
                    sscanf(line.c_str(), "%[^|]|%d|%[^|]|%d|%lf",
                           p.customerName, &p.productID, p.productName,
                           &p.quantity, &p.price);

                    // Filter by customer name
                    if(strcmp(p.customerName, username) == 0) {
                        purchaseCount++;
                        totalItems += p.quantity;
                        double itemTotal = p.price * p.quantity;
                        totalSpent += itemTotal;

                        cout << purchaseCount << "\t\t" << p.productID << "\t\t"
                             << p.productName << "\t\t"
                             << p.quantity << "\t" << p.price << "\t"
                             << itemTotal << endl;
                    }
                }

                purchaseFile.close();

                cout << "\n----\t\t----------\t------------\t\t---\t-----\t-----\n";

                if(purchaseCount == 0) {
                    cout << "No purchase records found for user: " << username << endl;
                } else {
                    cout << "Total Purchases: " << purchaseCount << endl;
                    cout << "Total Items: " << totalItems << endl;
                    cout << "Total Amount Spent: RM " << totalSpent << endl;
                    double avgSpending = totalSpent / purchaseCount;
                    cout << "Average Spending per Purchase: RM " << avgSpending << endl;
                }

                cout << "\n=========================================\n\n";
            }
            catch(const char* msg) {
                cout << msg << endl;
            }
        }

        // View all aurchases: staff only
        void viewAllPurchases() {
            try {
                ifstream purchaseFile("purchase.txt");
                if(!purchaseFile) {
                    throw "Purchase file cannot be opened.";
                }

                cout << "\n==========================================\n";
                cout << "   ALL CUSTOMER PURCHASE HISTORY (STAFF)\n";
                cout << "==========================================\n\n";

                string line;
                int totalRecords = 0;
                double totalRevenue = 0;
                int totalQuantitySold = 0;

                // Display table header
                cout << "No.\tCustomer Name\t\tProduct ID\tProduct Name\tQty\tPrice\tTotal\n";
                cout << "---\t--------------\t\t----------\t------------\t---\t-----\t-----\n";

                // Read and display all purchase records
                while(getline(purchaseFile, line)) {
                    if(line.empty()) continue;

                    Purchase p;
                    sscanf(line.c_str(), "%[^|]|%d|%[^|]|%d|%lf",
                           p.customerName, &p.productID, p.productName,
                           &p.quantity, &p.price);

                    totalRecords++;
                    totalQuantitySold += p.quantity;
                    double itemTotal = p.price * p.quantity;
                    totalRevenue += itemTotal;

                    cout << totalRecords << "\t" << p.customerName << "\t\t"
                         << p.productID << "\t\t" << p.productName << "\t"
                         << p.quantity << "\t" << p.price << "\t"
                         << itemTotal << endl;
                }

                purchaseFile.close();

                cout << "\n---\t--------------\t\t----------\t------------\t---\t-----\t-----\n";

                if(totalRecords == 0) {
                    cout << "No purchase records found.\n";
                } else {
                    cout << "Total Records: " << totalRecords << endl;
                    cout << "Total Items Sold: " << totalQuantitySold << endl;
                    cout << "Total Revenue: RM " << totalRevenue << endl;
                    double avgTransaction = totalRevenue / totalRecords;
                    cout << "Average Transaction Value: RM " << avgTransaction << endl;
                }

                cout << "\n==========================================\n\n";
            }
            catch(const char* msg) {
                cout << msg << endl;
            }
        }

        // Customer purchase statistics
        void displayCustomerStatistics() {
            try {
                ifstream purchaseFile("purchase.txt");
                if(!purchaseFile) {
                    throw "Purchase file cannot be opened.";
                }

                cout << "\n==========================================\n";
                cout << "   CUSTOMER PURCHASE STATISTICS\n";
                cout << "==========================================\n\n";

                string line;
                char customers[100][50];
                double customerSpending[100];
                int customerPurchases[100];
                int uniqueCustomers = 0;

                // Initialize arrays
                for(int i = 0; i < 100; i++) {
                    strcpy(customers[i], "");
                    customerSpending[i] = 0;
                    customerPurchases[i] = 0;
                }

                // Read and process purchase records
                while(getline(purchaseFile, line)) {
                    if(line.empty()) continue;

                    Purchase p;
                    sscanf(line.c_str(), "%[^|]|%d|%[^|]|%d|%lf",
                           p.customerName, &p.productID, p.productName,
                           &p.quantity, &p.price);

                    int found = -1;

                    // Search for existing customer in array
                    for(int i = 0; i < uniqueCustomers; i++) {
                        if(strcmp(customers[i], p.customerName) == 0) {
                            found = i;
                            break;
                        }
                    }

                    if(found == -1) {
                        // New customer
                        strcpy(customers[uniqueCustomers], p.customerName);
                        customerSpending[uniqueCustomers] = p.price * p.quantity;
                        customerPurchases[uniqueCustomers] = 1;
                        uniqueCustomers++;
                    } else {
                        // Existing customer
                        customerSpending[found] += p.price * p.quantity;
                        customerPurchases[found]++;
                    }
                }

                purchaseFile.close();

                // Display statistics
                cout << "Customer Name\t\tPurchases\tTotal Spent\tAvg Per Purchase\n";
                cout << "--------------\t\t---------\t-----------\t-----------------\n";

                double totalRevenue = 0;
                for(int i = 0; i < uniqueCustomers; i++) {
                    double avgPerPurchase = customerSpending[i] / customerPurchases[i];
                    totalRevenue += customerSpending[i];

                    cout << customers[i] << "\t\t" << customerPurchases[i] << "\t\t"
                         << customerSpending[i] << "\t\t" << avgPerPurchase << endl;
                }

                cout << "\n--------------\t\t---------\t-----------\t-----------------\n";
                cout << "Total Unique Customers: " << uniqueCustomers << endl;
                cout << "Total Revenue: RM " << totalRevenue << endl;

                if(uniqueCustomers > 0) {
                    double avgCustomerValue = totalRevenue / uniqueCustomers;
                    cout << "Average Customer Value: RM " << avgCustomerValue << endl;
                }

                cout << "\n==========================================\n\n";
            }
            catch(const char* msg) {
                cout << msg << endl;
            }
        }

        // Search purchase by product
        void searchPurchaseByProduct(int productID) {
            try {
                ifstream purchaseFile("purchase.txt");
                if(!purchaseFile) {
                    throw "Purchase file cannot be opened.";
                }

                cout << "\n==========================================\n";
                cout << "   PURCHASE SEARCH BY PRODUCT ID\n";
                cout << "   Product ID: " << productID << endl;
                cout << "==========================================\n\n";

                string line;
                int recordCount = 0;
                int totalQuantity = 0;
                double totalRevenue = 0;

                cout << "Customer Name\t\tQty\tPrice\tTotal\n";
                cout << "--------------\t\t---\t-----\t-----\n";

                // Filter purchases by product ID
                while(getline(purchaseFile, line)) {
                    if(line.empty()) continue;

                    Purchase p;
                    sscanf(line.c_str(), "%[^|]|%d|%[^|]|%d|%lf",
                           p.customerName, &p.productID, p.productName,
                           &p.quantity, &p.price);

                    if(p.productID == productID) {
                        recordCount++;
                        totalQuantity += p.quantity;
                        double itemTotal = p.price * p.quantity;
                        totalRevenue += itemTotal;

                        cout << p.customerName << "\t\t" << p.quantity << "\t"
                             << p.price << "\t" << itemTotal << endl;
                    }
                }

                purchaseFile.close();

                cout << "\n--------------\t\t---\t-----\t-----\n";

                if(recordCount == 0) {
                    cout << "No purchases found for Product ID: " << productID << endl;
                } else {
                    cout << "Total Records: " << recordCount << endl;
                    cout << "Total Quantity Sold: " << totalQuantity << endl;
                    cout << "Total Revenue: RM " << totalRevenue << endl;
                }

                cout << "\n==========================================\n\n";
            }
            catch(const char* msg) {
                cout << msg << endl;
            }
        }
};

int main() { 
    Staff::plist.loadFromFile(); 

	int choice; 
	User* user = NULL; 

	do {
		cout << "\n===== Stationery Shop Management System =====\n"; 
		cout << "1. Staff Module\n"; 
		cout << "2. Customer Module\n"; 
		cout << "0. Exit\n"; 
		cout << "Enter choice: "; 
		cin >> choice; 

		switch(choice) {
			case 1:
                user = new Staff(); 
				user->menu(); 
				delete user; 
                break;
            case 2:
                user = new Customer(); 
				user->menu(); 
				delete user;
                break;
            case 0:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid choice!\n";
		} 
	} while(choice != 0); 

	return 0; 
} 
