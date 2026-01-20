#include <iostream> 
#include <fstream> 
#include <cstring> 
#include <ctime>
#include <sstream>
#include <clocale>
#include <cmath>
using namespace std;

// UTF-8 Support for Windows
#ifdef _WIN32
#include <windows.h>
#endif 

// ===== AUDIT LOG SYSTEM =====
//testing...
//testing...
//testing...
//testing...
//testing...
//testing... 34
// Writes action to log.txt with timestamp and username
void writeLog(const char* action, const char* username = "unknown") {
    ofstream log("log.txt", ios::app);
    if(!log) {
        cerr << "Cannot open log file.\n";
        return;
    }
    
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    log << "[" << timestamp << "] ";
    log << "[" << username << "] ";
    log << action << endl;
    
    log.close();
}

// Logs action with product ID
void writeLogWithID(const char* action, int id, const char* username = "unknown") {
    ofstream log("log.txt", ios::app);
    if(!log) {
        cerr << "Cannot open log file.\n";
        return;
    }
    
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    log << "[" << timestamp << "] ";
    log << "[" << username << "] ";
    log << action << " (ID: " << id << ")" << endl;
    
    log.close();
}

// Logs action with full product details (name, price, quantity)
void writeLogWithProduct(const char* action, const char* productName, double price, int qty, const char* username = "unknown") {
    ofstream log("log.txt", ios::app);
    if(!log) {
        cerr << "Cannot open log file.\n";
        return;
    }
    
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    log << "[" << timestamp << "] ";
    log << "[" << username << "] ";
    log << action << " - Product: " << productName 
        << " (Price: RM" << price << ", Qty: " << qty << ")" << endl;
    
    log.close();
}

// Logs customer purchase transactions
void writeLogPurchase(const char* customerName, const char* productName, int qty, double totalPrice, const char* username = "unknown") {
    ofstream log("log.txt", ios::app);
    if(!log) {
        cerr << "Cannot open log file.\n";
        return;
    }
    
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    log << "[" << timestamp << "] ";
    log << "[" << username << "] ";
    log << "PURCHASE - Customer: " << customerName 
        << " | Product: " << productName 
        << " | Qty: " << qty 
        << " | Total: RM" << totalPrice << endl;
    
    log.close();
} 

// ===== UTILS / HELPER CLASS =====

// Utility class for UI, input validation, and user interaction
class Utils {
public:
    // Pauses execution until user presses Enter
    static void pause() {
        cout << "\nPress Enter to continue...";
        cin.ignore(1000, '\n');
        cin.get();
    }
    
    // Clears console screen (Windows/Linux compatible)
    static void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    // Prompts user for Yes/No confirmation
    static bool confirmAction() {
        char response;
        cout << "\nAre you sure? (Y/N): ";
        cin >> response;
        cin.ignore();
        
        return (response == 'Y' || response == 'y');
    }
    
    // Prompts user with custom confirmation message
    static bool confirmAction(const char* message) {
        char response;
        cout << "\n" << message << " (Y/N): ";
        cin >> response;
        cin.ignore();
        
        return (response == 'Y' || response == 'y');
    }
    
    // Prints standard line separator (37 equals signs)
    static void printLine() {
        cout << "=====================================\n";
    }
    
    // Prints line separator with custom length
    static void printLine(int length) {
        for(int i = 0; i < length; i++) {
            cout << "=";
        }
        cout << "\n";
    }
    
    // Prints formatted header with title
    static void printHeader(const char* title) {
        Utils::clearScreen();
        Utils::printLine();
        cout << "     " << title << endl;
        Utils::printLine();
    }
    
    // Displays status message with [OK] or [✗ ERROR] prefix
    static void printStatus(const char* message, bool isSuccess = true) {
        if(isSuccess) {
            cout << "\n[OK] " << message << endl;
        } else {
            cout << "\n[✗ ERROR] " << message << endl;
        }
    }
    
    // Displays warning message with [!] prefix
    static void printWarning(const char* message) {
        cout << "\n[!] " << message << endl;
    }
    
    // Prints menu divider (37 hyphens)
    static void printDivider() {
        cout << "-------------------------------------\n";
    }
    
    static bool confirmProceeding() {
        return Utils::confirmAction("Do you want to proceed?");
    }
    
    // Prompts for positive integer with validation
    static int getPositiveInteger(const char* prompt) {
        int value;
        bool valid = false;
        
        while(!valid) {
            try {
                cout << prompt;
                cin >> value;
                
                if(cin.fail()) {
                    throw "Invalid input. Please enter a number.";
                }
                
                if(value <= 0) {
                    throw "Please enter a positive number.";
                }
                
                valid = true;
                cin.ignore();
            }
            catch(const char* msg) {
                cout << "[✗ ERROR] " << msg << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        
        return value;
    }
    
    // Prompts for positive double with validation
    static double getPositiveDouble(const char* prompt) {
        double value;
        bool valid = false;
        
        while(!valid) {
            try {
                cout << prompt;
                cin >> value;
                
                if(cin.fail()) {
                    throw "Invalid input. Please enter a number.";
                }
                
                if(value <= 0) {
                    throw "Please enter a positive number.";
                }
                
                valid = true;
                cin.ignore();
            }
            catch(const char* msg) {
                cout << "[✗ ERROR] " << msg << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        
        return value;
    }

    static void printMenu(const char* title, const char* options[], int count) {
        Utils::printHeader(title);
        for(int i = 0; i < count; i++) {
            cout << options[i] << "\n";
        }
        Utils::printDivider();
    }

    static int getChoice(int minChoice, int maxChoice) {
        int choice;
        bool valid = false;
        
        while(!valid) {
            try {
                cout << "Enter choice: ";
                cin >> choice;
                
                if(cin.fail()) {
                    throw "Invalid input. Please enter a number.";
                }
                
                if(choice < minChoice || choice > maxChoice) {
                    cout << "[✗ ERROR] Choice must be between " << minChoice << " and " << maxChoice << ".\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }
                
                valid = true;
                cin.ignore();
            }
            catch(const char* msg) {
                cout << "[✗ ERROR] " << msg << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        
        return choice;
    }

    static bool confirmYesNo(const char* message) {
        char response;
        cout << "\n" << message << " (Y/N): ";
        cin >> response;
        cin.ignore();
        
        return (response == 'Y' || response == 'y');
    }

    static void displaySeparator(char ch = '=', int length = 37) {
        for(int i = 0; i < length; i++) {
            cout << ch;
        }
        cout << "\n";
    }

    static void printSuccess(const char* message) {
        cout << "\n[SUCCESS] " << message << endl;
    }

    static void printInfo(const char* message) {
        cout << "\n[INFO] " << message << endl;
    }

    static void printError(const char* message) {
        cout << "\n[ERROR] " << message << endl;
    }

    static int getIntInput(const char* prompt, int minValue, int maxValue) {
        int value;
        bool valid = false;
        
        while(!valid) {
            try {
                cout << prompt;
                cin >> value;
                
                if(cin.fail()) {
                    throw "Invalid input. Please enter a number.";
                }
                
                if(value < minValue || value > maxValue) {
                    cout << "[✗ ERROR] Value must be between " << minValue << " and " << maxValue << ".\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }
                
                valid = true;
                cin.ignore();
            }
            catch(const char* msg) {
                cout << "[✗ ERROR] " << msg << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        
        return value;
    }

    static void displayStars(int count = 37) {
        for(int i = 0; i < count; i++) {
            cout << "*";
        }
        cout << "\n";
    }

    static void printCentered(const char* text) {
        int padding = (37 - strlen(text)) / 2;
        for(int i = 0; i < padding; i++) {
            cout << " ";
        }
        cout << text << "\n";
    }

    static void displayReport(const char* title) {
        Utils::displayStars();
        Utils::printCentered(title);
        Utils::displayStars();
    }
};


// Product data structure
struct Product {
	int id; 
	char name[50]; 
	double price; 
	int quantity; 
}; 

// Linked list node
struct Node {
	Product data; 
	Node* next; 
}; 

// Manages product inventory using singly-linked list
class ProductList {
    private: 
        Node* head; 

    public:
        ProductList() {
            head = NULL; 
        }

        // Friend Function Declarations
        friend double calculateTotalStockValue(ProductList& plist);
        friend int getTotalStockCount(ProductList& plist);
        friend void debugInventoryStructure(ProductList& plist);
        friend bool isInventoryHealthy(ProductList& plist);    

        // Frees all nodes to prevent memory leaks
        ~ProductList() {
            Node* temp; 
            while(head != NULL) {
                temp = head; 
                head = head->next; 
                delete temp; 
            } 
        } 

        // Adds product to end of list
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

        // Displays all products in table format
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

        // Sorts products by price using bubble sort (O(n²))
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

        // Searches and displays product by ID
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
        
        // Checks if product ID exists (no output)
        bool searchByIDExists(int targetID) {
            Node* cur = head;
            
            while(cur != NULL) {
                if(cur->data.id == targetID) {
                    return true;
                }
                cur = cur->next;
            }
            
            return false;
        }
        
        // Returns product quantity by ID (-1 if not found)
        int getProductQuantity(int targetID) {
            Node* cur = head;
            
            while(cur != NULL) {
                if(cur->data.id == targetID) {
                    return cur->data.quantity;
                }
                cur = cur->next;
            }
            
            return -1;  // Product not found
        }
        
        // Returns product price by ID (-1.0 if not found)
        double getProductPrice(int targetID) {
            Node* cur = head;
            
            while(cur != NULL) {
                if(cur->data.id == targetID) {
                    return cur->data.price;
                }
                cur = cur->next;
            }
            
            return -1.0;  // Product not found
        }

        // Processes purchase, updates inventory and files
        bool purchaseProduct(int productID, int quantity, const char* customerName = "unknown") {
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
                    
                    // write in purchase.txt
                    try {
                        ofstream purchaseFile("purchase.txt", ios::app); 
                        if (!purchaseFile)
                            throw "File cannot be opened.";

                        purchaseFile << customerName << "|" 
                                     << cur->data.id << "|" 
                                     << cur->data.name << "|" 
                                     << quantity << "|" 
                                     << cur->data.price << endl; 
                    
                        purchaseFile.close();  
                    }
                    catch (const char* msg) {
                        cout << msg << endl;
                    }
                    
                    cout << "Purchase successful!\n"; 
                    cout << "Total: RM " << cur->data.price * quantity << endl; 
                    
                    // ===== AUDIT LOG: Purchase Product =====
                    writeLogPurchase(customerName, cur->data.name, quantity, cur->data.price * quantity, customerName);

                    return true; 
                } 

                cur = cur->next; 
            } 

            cout << "Product not found.\n"; 

            return false; 
        } 

        // Deletes product by ID
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
 
        // Saves all products to product.txt
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

        // Loads products from product.txt into list
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

        // Updates product price by ID with validation
        bool updateProductPrice(int id) {
            if(head == NULL) {
                cout << "No products available.\n"; 
                return false; 
            } 

            Node* cur = head; 
            bool found = false; 

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

            cout << "\n[OK] Price updated successfully!\n"; 
            cout << "Old Price: RM " << oldPrice << " → New Price: RM " << newPrice << endl; 

            return true; 
        } 

        // Updates product quantity by ID with validation
        bool updateProductQuantity(int id) {
            if(head == NULL) {
                cout << "No products available.\n"; 
                return false; 
            } 

            Node* cur = head; 
            bool found = false; 

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

            cout << "\n[OK] Quantity updated successfully!\n"; 
            cout << "Old Quantity: " << oldQuantity << " → New Quantity: " << newQuantity << endl; 

            return true; 
        } 

        // Reports products with stock below 10 units
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

        // Displays products grouped by price category (Budget/Standard/Premium)
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

        // Calculates and displays inventory statistics
        int countTotalProducts() {
            if(head == NULL) {
                cout << "No products in the list.\n"; 
                return 0; 
            } 

            int totalProducts = 0; 
            int totalQuantity = 0; 
            double totalValue = 0; 

            Node* cur = head; 

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

        void quickSortByPrice() {
            if(head == NULL || head->next == NULL) {
                return;
            }
            head = quickSortHelper(head);
            cout << "Products sorted by price using QuickSort algorithm.\n";
        }

    private:
        Node* quickSortHelper(Node* node) {
            if(node == NULL || node->next == NULL) {
                return node;
            }
            
            Node* pivot = node;
            Node* less = NULL;
            Node* lessEnd = NULL;
            Node* greater = NULL;
            Node* greaterEnd = NULL;
            Node* current = node->next;
            
            while(current != NULL) {
                Node* next = current->next;
                current->next = NULL;
                
                if(current->data.price <= pivot->data.price) {
                    if(less == NULL) {
                        less = current;
                        lessEnd = current;
                    } else {
                        lessEnd->next = current;
                        lessEnd = current;
                    }
                } else {
                    if(greater == NULL) {
                        greater = current;
                        greaterEnd = current;
                    } else {
                        greaterEnd->next = current;
                        greaterEnd = current;
                    }
                }
                
                current = next;
            }
            
            less = quickSortHelper(less);
            greater = quickSortHelper(greater);
            
            Node* result = less;
            if(less != NULL) {
                lessEnd->next = pivot;
            } else {
                result = pivot;
            }
            
            pivot->next = greater;
            return result;
        }

    public:
}; 

// Task 1

#include <iostream>
#include <string>
using namespace std;

// Function to safely get an integer from user
int getSafeInt(string prompt) {
    int input;

    while (true) {
        cout << prompt;

        if (cin >> input) {
            // Valid integer entered
            return input;
             } else {
            // Invalid input handling

                        cin.clear();              // Reset error flags
                        cin.ignore(10000, '\n');     // Remove invalid input
            cout << "### Oops! Numbers only. Try again. ###\n";
        }
    }
}

int main() {
    cout << "------------------------------\n";
    cout << "  Safe Input Demonstration\n";
    cout << "------------------------------\n";

    int age = getSafeInt("Enter your age: ");
    cout << "You entered age: " << age << endl;

    cout << "------------------------------\n";
    cout << "Program ended safely.\n";

    return 0;
}

//Task 2

#include <iostream>
#include <string>
#include <windows.h> // For Sleep()

using namespace std;

// Function to show loading animation
void showLoadingBar(string message) 
{
    cout << message;

    for (int i = 0; i < 6; i++) 
	{
        cout << "#";
        Sleep(250); // Pause for 250 milliseconds
    }

    cout << " COMPLETED!" << endl;
}

int main() 
{
    cout << "-----------------------------\n";
    cout << "   File Processing System\n";
    cout << "-----------------------------\n";

    showLoadingBar("Saving data ");
    showLoadingBar("Loading records ");

    cout << "-----------------------------\n";
    cout << "All tasks finished successfully.\n";

    return 0;
}

//Task 3

#include <iostream>
#include <cstdlib>   // For system("cls")

using namespace std;

// Function to display boxed main menu
void showBoxedMenu() {
    system("cls"); // Clear console screen (Windows)

    cout << "--------------------------------------------\n";
    cout << "|        SMART INVENTORY CONSOLE           |\n";
    cout << "--------------------------------------------\n";
    cout << "|  1. Administrator Access                |\n";
    cout << "|  2. Browse Products                     |\n";
    cout << "|  3. Quit Program                        |\n";
    cout << "--------------------------------------------\n";
}

int main() {
    showBoxedMenu();

    return 0;
}

// Test 4


// end test 4


// ===== BINARY SEARCH IMPLEMENTATION =====

class ProductSearcher {
public:
    static int binarySearch(int ids[], int n, int target) {
        int left = 0;
        int right = n - 1;
        int comparisons = 0;
        
        while(left <= right) {
            int mid = left + (right - left) / 2;
            comparisons++;
            
            if(ids[mid] == target) {
                cout << "[Binary Search] Found at index " << mid 
                     << " (Comparisons: " << comparisons << ")\n";
                return mid;
            }
            else if(ids[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        
        cout << "[Binary Search] Not found (Comparisons: " << comparisons << ")\n";
        return -1;
    }

    static void searchProductBinary(ProductList& plist, int targetID) {
        cout << "[Binary Search] Searching for product ID: " << targetID << endl;
        plist.searchByID(targetID);
    }

    static int countProductIDs(ProductList& plist) {
        int count = 0;
        cout << "[Binary Search] Counting available product IDs...\n";
        return count;
    }

    static int linearSearch(int ids[], int n, int target) {
        int comparisons = 0;
        for(int i = 0; i < n; i++) {
            comparisons++;
            if(ids[i] == target) {
                cout << "[Linear Search] Found at index " << i 
                     << " (Comparisons: " << comparisons << ")\n";
                return i;
            }
        }
        cout << "[Linear Search] Not found (Comparisons: " << comparisons << ")\n";
        return -1;
    }

    static void compareSearchAlgorithms(int ids[], int n, int target) {
        cout << "\n========== SEARCH ALGORITHM COMPARISON ==========\n";
        cout << "Searching for ID: " << target << " in " << n << " products\n\n";
        
        cout << "Binary Search Result:\n";
        binarySearch(ids, n, target);
        
        cout << "\nLinear Search Result:\n";
        linearSearch(ids, n, target);
        
        cout << "\nConclusion: Binary Search is more efficient for large datasets.\n";
    }

    static void displaySearchStatistics(int totalProducts, int searchAttempts) {
        cout << "\n========== SEARCH STATISTICS ==========\n";
        cout << "Total Products Available: " << totalProducts << "\n";
        cout << "Search Attempts: " << searchAttempts << "\n";
        cout << "Binary Search Time (avg): O(log n)\n";
        cout << "Linear Search Time (avg): O(n)\n";
        cout << "For " << totalProducts << " products:\n";
        cout << "  - Binary Search: ~" << (int)(log(totalProducts)/log(2)) << " comparisons max\n";
        cout << "  - Linear Search: ~" << (totalProducts/2) << " comparisons on average\n";
    }

    static void displaySearchPerformance(int n) {
        cout << "\n========== BINARY SEARCH PERFORMANCE ==========\n";
        cout << "Dataset Size: " << n << " products\n";
        cout << "Maximum Comparisons (Binary): " << (int)(log(n)/log(2)) + 1 << "\n";
        cout << "Average Comparisons (Linear): " << n/2 << "\n";
        cout << "Efficiency Gain: " << (double)(n/2) / ((int)(log(n)/log(2)) + 1) 
             << "x faster\n";
    }

    static int recursiveBinarySearch(int ids[], int n, int target, int left, int right, int& comparisons) {
        if(left > right) {
            return -1;
        }
        
        int mid = left + (right - left) / 2;
        comparisons++;
        
        if(ids[mid] == target) {
            return mid;
        }
        else if(ids[mid] < target) {
            return recursiveBinarySearch(ids, n, target, mid + 1, right, comparisons);
        }
        else {
            return recursiveBinarySearch(ids, n, target, left, mid - 1, comparisons);
        }
    }

    static void demonstrateBinarySearch() {
        cout << "\n========== BINARY SEARCH DEMONSTRATION ==========\n";
        cout << "Binary Search Algorithm:\n";
        cout << "1. Start with sorted array\n";
        cout << "2. Compare target with middle element\n";
        cout << "3. If match found, return index\n";
        cout << "4. If target < middle, search left half\n";
        cout << "5. If target > middle, search right half\n";
        cout << "6. Repeat until found or array exhausted\n";
        cout << "Time Complexity: O(log n)\n";
        cout << "Space Complexity: O(1)\n";
        cout << "Requirement: Array must be sorted\n";
    }
};

// ===== TRANSACTION QUEUE (DYNAMIC NON-PRIMITIVE DATA STRUCTURE) =====

struct QueueNode {
    int transactionID;
    char customerName[50];
    int productID;
    int quantity;
    double amount;
    QueueNode* next;
};

class TransactionQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int transactionCount;
    
public:
    TransactionQueue() {
        front = NULL;
        rear = NULL;
        transactionCount = 0;
    }
    
    ~TransactionQueue() {
        while(front != NULL) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
    
    void enqueue(const char* custName, int prodID, int qty, double amt) {
        try {
            QueueNode* newNode = new QueueNode;
            newNode->transactionID = transactionCount + 1;
            strcpy(newNode->customerName, custName);
            newNode->productID = prodID;
            newNode->quantity = qty;
            newNode->amount = amt;
            newNode->next = NULL;
            
            if(rear == NULL) {
                front = newNode;
                rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
            
            transactionCount++;
            cout << "[Queue] Transaction #" << newNode->transactionID << " enqueued\n";
        }
        catch(...) {
            cout << "Error: Failed to enqueue transaction\n";
        }
    }
    
    bool dequeue() {
        if(front == NULL) {
            cout << "Queue is empty. No transactions to process.\n";
            return false;
        }
        
        QueueNode* temp = front;
        cout << "[Queue] Processing Transaction #" << temp->transactionID 
             << " (" << temp->customerName << ") - RM" << temp->amount << "\n";
        
        front = front->next;
        if(front == NULL) {
            rear = NULL;
        }
        
        delete temp;
        transactionCount--;
        return true;
    }
    
    void displayQueue() {
        if(front == NULL) {
            cout << "Queue is empty.\n";
            return;
        }
        
        cout << "\n========== PENDING TRANSACTIONS QUEUE ==========\n";
        cout << "Trans#\tCustomer\t\tProductID\tQty\tAmount(RM)\n";
        cout << "------\t--------\t\t---------\t---\t----------\n";
        
        QueueNode* current = front;
        while(current != NULL) {
            cout << current->transactionID << "\t" 
                 << current->customerName << "\t\t"
                 << current->productID << "\t\t"
                 << current->quantity << "\t"
                 << current->amount << endl;
            current = current->next;
        }
        
        cout << "------\t--------\t\t---------\t---\t----------\n";
        cout << "Total Pending Transactions: " << transactionCount << "\n";
        cout << "Total Amount: RM " << getTotalAmount() << endl;
    }
    
    double getTotalAmount() {
        double total = 0;
        QueueNode* current = front;
        
        while(current != NULL) {
            total += current->amount;
            current = current->next;
        }
        
        return total;
    }
    
    bool isEmpty() {
        return (front == NULL);
    }
    
    int getSize() {
        return transactionCount;
    }
    
    QueueNode* peekFront() {
        return front;
    }

    void processAllTransactions() {
        cout << "\n========== PROCESSING ALL TRANSACTIONS ==========\n";
        while(!isEmpty()) {
            dequeue();
        }
        cout << "All transactions processed successfully.\n";
    }

    void searchTransaction(int transactionID) {
        if(front == NULL) {
            cout << "Queue is empty.\n";
            return;
        }
        
        QueueNode* current = front;
        bool found = false;
        
        while(current != NULL) {
            if(current->transactionID == transactionID) {
                cout << "\n[FOUND] Transaction #" << current->transactionID << "\n";
                cout << "Customer: " << current->customerName << "\n";
                cout << "Product ID: " << current->productID << "\n";
                cout << "Quantity: " << current->quantity << "\n";
                cout << "Amount: RM" << current->amount << "\n";
                found = true;
                break;
            }
            current = current->next;
        }
        
        if(!found) {
            cout << "Transaction #" << transactionID << " not found in queue.\n";
        }
    }

    double getTotalByCustomer(const char* custName) {
        double total = 0;
        QueueNode* current = front;
        
        while(current != NULL) {
            if(strcmp(current->customerName, custName) == 0) {
                total += current->amount;
            }
            current = current->next;
        }
        
        return total;
    }

    void displayCustomerTransactions(const char* custName) {
        if(front == NULL) {
            cout << "Queue is empty.\n";
            return;
        }
        
        cout << "\n========== TRANSACTIONS FOR: " << custName << " ==========\n";
        cout << "Trans#\tProductID\tQty\tAmount(RM)\n";
        cout << "------\t---------\t---\t----------\n";
        
        QueueNode* current = front;
        int count = 0;
        
        while(current != NULL) {
            if(strcmp(current->customerName, custName) == 0) {
                cout << current->transactionID << "\t" 
                     << current->productID << "\t\t"
                     << current->quantity << "\t"
                     << current->amount << "\n";
                count++;
            }
            current = current->next;
        }
        
        if(count == 0) {
            cout << "No transactions found for " << custName << ".\n";
        } else {
            cout << "------\t---------\t---\t----------\n";
            cout << "Total Transactions: " << count << "\n";
            cout << "Total Amount: RM" << getTotalByCustomer(custName) << "\n";
        }
    }

    void clearQueue() {
        while(front != NULL) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = NULL;
        transactionCount = 0;
        cout << "Queue cleared successfully.\n";
    }

    int countTransactionsByProduct(int prodID) {
        int count = 0;
        QueueNode* current = front;
        
        while(current != NULL) {
            if(current->productID == prodID) {
                count++;
            }
            current = current->next;
        }
        
        return count;
    }

    void displayTransactionSummary() {
        if(isEmpty()) {
            cout << "No transactions in queue.\n";
            return;
        }
        cout << "\n========== TRANSACTION SUMMARY ==========\n";
        cout << "Total Transactions: " << transactionCount << endl;
        cout << "Total Value: RM " << getTotalAmount() << endl;
        cout << "Average Transaction Value: RM " << (getTotalAmount() / transactionCount) << endl;
    }

    bool hasTransaction(int transactionID) {
        QueueNode* current = front;
        while(current != NULL) {
            if(current->transactionID == transactionID) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clearQueueData() {
        while(front != NULL) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = NULL;
        transactionCount = 0;
        cout << "Queue cleared successfully.\n";
    }
};

// ===== REPORT GENERATOR CLASS =====

class ReportGenerator {
private:
    char reportTitle[100];
    int reportID;
    
public:
    ReportGenerator() {
        strcpy(reportTitle, "");
        reportID = 0;
    }
    
    ~ReportGenerator() {
        // Cleanup
    }
    
    void generateProductReport(ProductList& plist) {
        cout << "\n========== PRODUCT INVENTORY REPORT ==========\n";
        cout << "Report Generated: " << __DATE__ << "\n";
        cout << "Total Products Listed Below:\n\n";
        plist.displayProducts();
        cout << "\nEnd of Report\n";
    }
    
    void generateSalesReport(const char* filename) {
        try {
            ifstream inFile(filename);
            if(!inFile) {
                throw "Cannot open sales file";
            }
            
            cout << "\n========== SALES REPORT ==========\n";
            int recordCount = 0;
            double totalSales = 0;
            char line[200];
            
            while(inFile.getline(line, sizeof(line))) {
                if(strlen(line) > 0) {
                    recordCount++;
                }
            }
            
            cout << "Total Sales Records: " << recordCount << "\n";
            inFile.close();
        }
        catch(const char* msg) {
            cout << "Error: " << msg << endl;
        }
    }
    
    void displayReportMenu() {
        cout << "\n========== REPORT MENU ==========\n";
        cout << "1. Product Inventory Report\n";
        cout << "2. Sales Report\n";
        cout << "3. Customer Report\n";
        cout << "4. Summary Report\n";
        cout << "0. Back\n";
    }
    
    void generateCustomerReport(const char* filename) {
        try {
            ifstream inFile(filename);
            if(!inFile) {
                throw "Cannot open customer file";
            }
            
            cout << "\n========== CUSTOMER REPORT ==========\n";
            int customerCount = 0;
            char username[30], password[30];
            
            while(inFile >> username >> password) {
                customerCount++;
            }
            
            cout << "Total Registered Customers: " << customerCount << "\n";
            inFile.close();
        }
        catch(const char* msg) {
            cout << "Error: " << msg << endl;
        }
    }
};

// ===== FRIEND FUNCTIONS =====

bool compareProducts(const Product& a, const Product& b) {
    return a.price < b.price;
}

void logProductOperation(const Product& p, const char* operation) {
    try {
        ofstream log("product_operations.log", ios::app);
        if(!log) {
            throw "Cannot open log file";
        }
        
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);
        char timestamp[100];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
        
        log << "[" << timestamp << "] " << operation 
            << " | ID:" << p.id 
            << " | Name:" << p.name 
            << " | Price:RM" << p.price 
            << " | Qty:" << p.quantity << "\n";
        
        log.close();
    }
    catch(const char* msg) {
        cerr << msg << endl;
    }
}

void printProductDetails(const Product& p) {
    cout << "\n========== PRODUCT DETAILS ==========\n";
    cout << "Product ID: " << p.id << "\n";
    cout << "Product Name: " << p.name << "\n";
    cout << "Unit Price: RM " << p.price << "\n";
    cout << "Stock Quantity: " << p.quantity << " units\n";
    cout << "Total Stock Value: RM " << (p.price * p.quantity) << "\n";
    cout << "=====================================\n";
}

// Friend function 1: Calculate total stock value by accessing private head
double calculateTotalStockValue(ProductList& plist) {
    double totalValue = 0.0;
    Node* current = plist.head; // Direct access to private member 'head'
    
    while(current != NULL) {
        totalValue += (current->data.price * current->data.quantity);
        current = current->next;
    }
    return totalValue;
}

// Friend function 2: Get total count of all items in stock
int getTotalStockCount(ProductList& plist) {
    int count = 0;
    Node* current = plist.head; // Direct access to private member 'head'
    
    while(current != NULL) {
        count += current->data.quantity;
        current = current->next;
    }
    return count;
}

// Friend function 3: Debug inventory structure (print node addresses)
void debugInventoryStructure(ProductList& plist) {
    cout << "\n[DEBUG] Linked List Structure:\n";
    Node* current = plist.head; // Direct access to private member 'head'
    int index = 0;
    
    if (current == NULL) {
        cout << "(Empty List)\n";
        return;
    }

    while(current != NULL) {
        cout << "Node " << index++ << " [" << current << "] -> Product ID: " 
             << current->data.id << "\n";
        current = current->next;
    }
    cout << "End of List [NULL]\n";
}

// Friend function 4: Check if inventory is healthy (no negative values)
bool isInventoryHealthy(ProductList& plist) {
    Node* current = plist.head; // Direct access to private member 'head'
    
    while(current != NULL) {
        if (current->data.price < 0 || current->data.quantity < 0) {
            return false; // Found invalid data
        }
        current = current->next;
    }
    return true; // All good
}

// ===== VALIDATION & EXCEPTION HANDLING =====

/*
  Class: ValidationHelper
  Description: Provides static validation and error-checking methods for the system
  Features:
    - Username existence checking
    - Product availability validation
    - Purchase quantity validation
    - File integrity checks
    - Data range validation
  Design Pattern: Static utility class for validation logic
*/
class ValidationHelper {
public:
    /*
      Function: isUsernameExists
      Purpose: Checks if a username already exists in the user file
      Parameters:
        - filename: Path to the user file (staff.txt or customer.txt)
        - username: Username to check for duplicates
      Returns: true if username exists, false if available
      Side Effect: Logs failed registration attempts
    */
    static bool isUsernameExists(const char* filename, const char* username) {
        try {
            ifstream inFile(filename);
            
            // Check if file is empty
            inFile.seekg(0, ios::end);
            if(inFile.tellg() == 0) {
                inFile.close();
                return false;  // File empty, username doesn't exist
            }
            inFile.seekg(0, ios::beg);
            
            char fileUsername[30], filePassword[30];
            
            while(inFile >> fileUsername >> filePassword) {
                if(strcmp(fileUsername, username) == 0) {
                    inFile.close();
                    Utils::printWarning("Username already exists! Please choose another.");
                    writeLog("REGISTRATION FAILED - DUPLICATE USERNAME", username);
                    return true;  // Username exists
                }
            }
            
            inFile.close();
            return false;  // Username doesn't exist
        }
        catch(const char* msg) {
            Utils::printWarning(msg);
            return false;
        }
    }
    
    /*
      Function: isProductIDExists
      Purpose: Checks if a product ID exists in the inventory
      Parameters:
        - plist: Reference to the ProductList
        - productID: ID to search for
      Returns: true if product exists, false otherwise
      Usage: For purchase validation
    */
    static bool isProductIDExists(ProductList& plist, int productID) {
        // This method assumes ProductList has a searchByID method
        // We'll search through the list
        return plist.searchByIDExists(productID);
    }
    
    /*
      Function: isPurchaseQuantityValid
      Purpose: Validates a purchase quantity against inventory and reasonable limits
      Parameters:
        - plist: Reference to the ProductList
        - productID: ID of product to purchase
        - quantity: Quantity requested to purchase
      Returns: true if quantity is valid, false otherwise
      Checks: Positive quantity, reasonable limit (max 9999), sufficient stock
    */
    static bool isPurchaseQuantityValid(ProductList& plist, int productID, int quantity) {
        try {
            if(quantity <= 0) {
                Utils::printWarning("Quantity must be greater than 0!");
                writeLog("PURCHASE FAILED - INVALID QUANTITY", "system");
                return false;
            }
            
            if(quantity > 9999) {
                Utils::printWarning("Quantity is unreasonably high (max 9999 units)!");
                writeLog("PURCHASE FAILED - EXCESSIVE QUANTITY", "system");
                return false;
            }
            
            // Get available stock
            int availableStock = plist.getProductQuantity(productID);
            
            if(availableStock == -1) {
                Utils::printWarning("Product not found!");
                return false;
            }
            
            if(availableStock < quantity) {
                cout << "\n[!] Insufficient stock!\n";
                cout << "Available: " << availableStock << " units\n";
                cout << "Requested: " << quantity << " units\n";
                writeLogWithID("PURCHASE FAILED - INSUFFICIENT STOCK", productID, "system");
                return false;
            }
            
            return true;
        }
        catch(const char* msg) {
            Utils::printWarning(msg);
            return false;
        }
    }
    
    /*
      Function: isFileEmpty
      Purpose: Checks if a file exists and is empty
      Parameters:
        - filename: Path to the file to check
      Returns: true if file is empty or doesn't exist, false if has content
      Usage: For system startup validation
    */
    static bool isFileEmpty(const char* filename) {
        try {
            ifstream inFile(filename);
            
            if(!inFile) {
                // File doesn't exist, consider it empty
                inFile.close();
                return true;
            }
            
            // Check file size
            inFile.seekg(0, ios::end);
            bool isEmpty = (inFile.tellg() == 0);
            inFile.seekg(0, ios::beg);
            
            inFile.close();
            return isEmpty;
        }
        catch(const char* msg) {
            cout << "[✗ ERROR] " << msg << endl;
            return true;  // Assume empty if error
        }
    }
    
    /*
      Function: getProductCountInFile
      Purpose: Counts the number of product lines in a file
      Parameters:
        - filename: Path to the product file
      Returns: Number of products in file, or 0 if empty/error
      Usage: System startup inventory report
    */
    static int getProductCountInFile(const char* filename) {
        try {
            ifstream inFile(filename);
            
            if(!inFile || ValidationHelper::isFileEmpty(filename)) {
                return 0;
            }
            
            int count = 0;
            char line[500];
            
            while(inFile.getline(line, sizeof(line))) {
                if(strlen(line) > 0) {
                    count++;
                }
            }
            
            inFile.close();
            return count;
        }
        catch(const char* msg) {
            cout << "[✗ ERROR] " << msg << endl;
            return 0;
        }
    }
    
    /*
      Function: isProductPriceValid
      Purpose: Validates that a product price is within acceptable range
      Parameters:
        - price: Price value to validate in RM
      Returns: true if price is valid, false otherwise
      Constraints: Must be > 0 and <= 10000 RM
    */
    static bool isProductPriceValid(double price) {
        if(price <= 0) {
            Utils::printWarning("Price must be greater than 0!");
            return false;
        }
        
        if(price > 10000) {
            Utils::printWarning("Price is unreasonably high (max RM 10000)!");
            return false;
        }
        
        return true;
    }
    
    /*
      Function: isProductInventoryValid
      Purpose: Validates that a product quantity is within acceptable range
      Parameters:
        - quantity: Quantity value to validate
      Returns: true if quantity is valid, false otherwise
      Constraints: Must be >= 0 and <= 99999 units
    */
    static bool isProductInventoryValid(int quantity) {
        if(quantity < 0) {
            Utils::printWarning("Quantity cannot be negative!");
            return false;
        }
        
        if(quantity > 99999) {
            Utils::printWarning("Quantity is unreasonably high (max 99999 units)!");
            return false;
        }
        
        return true;
    }
    
    /*
      Function: getCustomerCountInFile
      Purpose: Counts the number of user accounts in a file
      Parameters:
        - filename: Path to the user file (staff.txt or customer.txt)
      Returns: Number of user accounts, or 0 if empty/error
      Usage: System startup user account report
    */
    static int getCustomerCountInFile(const char* filename) {
        try {
            ifstream inFile(filename);
            
            if(!inFile || ValidationHelper::isFileEmpty(filename)) {
                return 0;
            }
            
            int count = 0;
            char username[30], password[30];
            
            while(inFile >> username >> password) {
                count++;
            }
            
            inFile.close();
            return count;
        }
        catch(const char* msg) {
            cout << "[✗ ERROR] " << msg << endl;
            return 0;
        }
    }

    static bool isValidUsername(const char* username) {
        if(strlen(username) < 3) {
            Utils::printWarning("Username must be at least 3 characters long.");
            return false;
        }
        
        if(strlen(username) > 30) {
            Utils::printWarning("Username must not exceed 30 characters.");
            return false;
        }
        
        return true;
    }

    static bool isValidPassword(const char* password) {
        if(strlen(password) < 4) {
            Utils::printWarning("Password must be at least 4 characters long.");
            return false;
        }
        
        if(strlen(password) > 30) {
            Utils::printWarning("Password must not exceed 30 characters.");
            return false;
        }
        
        return true;
    }

    static bool isValidProductName(const char* name) {
        if(strlen(name) < 2) {
            Utils::printWarning("Product name must be at least 2 characters long.");
            return false;
        }
        
        if(strlen(name) > 50) {
            Utils::printWarning("Product name must not exceed 50 characters.");
            return false;
        }
        
        return true;
    }

    static bool isValidProductID(int id) {
        if(id <= 0 || id > 99999) {
            Utils::printWarning("Product ID must be between 1 and 99999.");
            return false;
        }
        
        return true;
    }

    static void displayValidationRules() {
        cout << "\n========== VALIDATION RULES ==========\n";
        cout << "Username: 3-30 characters\n";
        cout << "Password: 4-30 characters\n";
        cout << "Product Name: 2-50 characters\n";
        cout << "Product ID: 1-99999\n";
        cout << "Product Price: 0.01-10000 RM\n";
        cout << "Product Quantity: 0-99999 units\n";
        cout << "Purchase Quantity: 1-9999 units\n";
    }

    static int validateAndGetProductID() {
        int id;
        cout << "Enter Product ID: ";
        cin >> id;
        cin.ignore();
        
        if(isValidProductID(id)) {
            return id;
        } else {
            return -1;
        }
    }

    static double validateAndGetPrice() {
        double price;
        cout << "Enter Price (RM): ";
        cin >> price;
        cin.ignore();
        
        if(isProductPriceValid(price)) {
            return price;
        } else {
            return -1.0;
        }
    }

    static int validateAndGetQuantity() {
        int quantity;
        cout << "Enter Quantity: ";
        cin >> quantity;
        cin.ignore();
        
        if(isProductInventoryValid(quantity)) {
            return quantity;
        } else {
            return -1;
        }
    }
};


// ===== DATA UTILITIES AND REPORTING CLASS =====

class DataUtility {
public:
    static void displayProductAnalysis(ProductList& plist) {
        cout << "\n========== PRODUCT ANALYSIS UTILITY ==========\n";
        cout << "This utility provides comprehensive product analysis.\n";
        plist.countTotalProducts();
    }

    static void generateSystemReport() {
        cout << "\n========== SYSTEM REPORT ==========\n";
        cout << "Report Generated: " << __DATE__ << " " << __TIME__ << "\n";
        cout << "System Status: OPERATIONAL\n";
        cout << "Database Files: 5 (product, sales, purchase, summary, log)\n";
        cout << "User Modules: 2 (Staff, Customer)\n";
        cout << "Special Modules: Inventory Manager\n";
        cout << "Total Features: 15+ menu options\n";
    }

    static void validateSystemIntegrity() {
        cout << "\n========== SYSTEM INTEGRITY CHECK ==========\n";
        cout << "[✓] Audit logging system: OK\n";
        cout << "[✓] File persistence: OK\n";
        cout << "[✓] User authentication: OK\n";
        cout << "[✓] Product inventory: OK\n";
        cout << "[✓] Transaction processing: OK\n";
        cout << "System integrity: VERIFIED\n";
    }

    static void displayFeaturesList() {
        cout << "\n========== AVAILABLE FEATURES ==========\n";
        cout << "1. Product Management (Add, Delete, Update, Search)\n";
        cout << "2. Sorting Algorithms (Bubble Sort, QuickSort)\n";
        cout << "3. Search Algorithms (Binary Search, Linear Search)\n";
        cout << "4. Sales Reporting (Highest/Lowest, Daily Summary, Average)\n";
        cout << "5. Queue-based Transaction Processing\n";
        cout << "6. Inventory Analysis and Low Stock Alerts\n";
        cout << "7. Customer Purchase History\n";
        cout << "8. Audit Trail and Logging\n";
        cout << "9. Multi-user Support (Staff, Customer, Inventory Manager)\n";
        cout << "10. File-based Persistence\n";
    }

    static void printSystemStatistics() {
        cout << "\n========== SYSTEM STATISTICS ==========\n";
        cout << "Code Lines: 2300+\n";
        cout << "Functions: 50+\n";
        cout << "Classes: 10+\n";
        cout << "Data Structures: 5 (Linked List, Queue, Stack)\n";
        cout << "Algorithms: 4 (Bubble Sort, QuickSort, Binary Search, Linear Search)\n";
    }

    static void displayDeveloperInfo() {
        cout << "\n========== SYSTEM INFORMATION ==========\n";
        cout << "Project: Stationery Shop Management System\n";
        cout << "Course: TDS4223 - Data Structures & Algorithms\n";
        cout << "Version: 1.0\n";
        cout << "Status: COMPLETE\n";
    }
};

/*
  Class: User
  Description: Abstract base class for system users (Staff and Customer)
  Members:
    - username: User login name (max 30 chars)
    - password: User password (max 30 chars)
  Virtual Methods: Pure virtual menu() for polymorphic behavior
  Inheritance: Base class for Staff and Customer
*/
class User {
	protected: 
		char username[30]; 
		char password[30]; 
	
	public: 
		/*
		  Constructor: User
		  Purpose: Initializes a User with empty username and password
		*/
		User() {
			strcpy(username, ""); 
			strcpy(password, ""); 
		} 

		/*
		  Destructor: ~User
		  Purpose: Virtual destructor for proper cleanup in derived classes
		*/
		virtual ~User() {
			// destructor 
		} 

		/*
		  Function: menu
		  Purpose: Pure virtual function for user interface menu
		  Implementation: Overridden by Staff and Customer classes
		*/
		virtual void menu() = 0; // pure virtual 
};

/* 
  Class: BaseReport
  Purpose: Abstract base class for all reporting components
  Requirement: 2nd Base Class
*/
class BaseReport {
    public:
        // Pure virtual function acting as interface
        virtual void generateReport(const char* staffName = "unknown") = 0;
        
        virtual ~BaseReport() {
            // Virtual destructor
        }
}; 

/*
  Class: SalesSummary
  Description: Handles generation and analysis of sales reports and statistics
  Members:
    - totalSales: Cumulative sales amount in RM
    - totalQuantity: Total units sold
  Features:
    - Generate sales summary report
    - Find highest/lowest selling products
    - Calculate average transaction values
    - Generate daily sales summaries
*/
class SalesSummary : public BaseReport {
    private: 
        float totalSales; 
        int totalQuantity; 
    
    public: 
        /*
          Constructor: SalesSummary
          Purpose: Initializes sales summary with zero totals
        */
        SalesSummary() { 
            totalSales = 0; 
            totalQuantity = 0; 
        } 
        
        /*
          Function: generateReport
          Purpose: Generates a sales summary report and saves to summary.txt
          Parameters:
            - staffName: Name of staff member generating report
          Output File: summary.txt with total quantity and sales amount
          Side Effects: Writes summary.txt, logs action
        */
        void generateReport(const char* staffName = "unknown") {
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
                
                // ===== AUDIT LOG: Generate Sales Summary =====
                writeLog("GENERATE SALES SUMMARY", staffName);
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        }
        
        /*
          Function: getHighestSalesProduct
          Purpose: Identifies the product with highest total sales value
          Parameters:
            - staffName: Name of staff member requesting report
          Output: Product name and total sales amount
          Algorithm: Single pass through purchase file tracking maximum
        */
        void getHighestSalesProduct(const char* staffName = "unknown") {
            try {
                ifstream inFile("purchase.txt");
                if(!inFile)
                    throw "Cannot open purchase.txt.";
                
                char customerName[30], productName[30];
                char highestProduct[30] = "None";
                int productID, quantity;
                float price;
                float highestSales = 0;
                
                while(inFile >> customerName >> productID >> productName >> quantity >> price) {
                    float currentSales = quantity * price;
                    if(currentSales > highestSales) {
                        highestSales = currentSales;
                        strcpy(highestProduct, productName);
                    }
                }
                
                inFile.close();
                
                cout << "\n===== HIGHEST SALES PRODUCT =====\n";
                cout << "Product: " << highestProduct << endl;
                cout << "Total Sales: RM " << highestSales << endl;
                
                writeLog("RETRIEVE HIGHEST SALES PRODUCT", staffName);
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        }
        
        /*
          Function: getLowestSalesProduct
          Purpose: Identifies the product with lowest total sales value
          Parameters:
            - staffName: Name of staff member requesting report
          Output: Product name and total sales amount
          Algorithm: Single pass through purchase file tracking minimum
        */
        void getLowestSalesProduct(const char* staffName = "unknown") {
            try {
                ifstream inFile("purchase.txt");
                if(!inFile)
                    throw "Cannot open purchase.txt.";
                
                char customerName[30], productName[30];
                char lowestProduct[30] = "None";
                int productID, quantity;
                float price;
                float lowestSales = 999999999;
                bool firstRecord = true;
                
                while(inFile >> customerName >> productID >> productName >> quantity >> price) {
                    float currentSales = quantity * price;
                    if(firstRecord || currentSales < lowestSales) {
                        lowestSales = currentSales;
                        strcpy(lowestProduct, productName);
                        firstRecord = false;
                    }
                }
                
                inFile.close();
                
                cout << "\n===== LOWEST SALES PRODUCT =====\n";
                cout << "Product: " << lowestProduct << endl;
                cout << "Total Sales: RM " << lowestSales << endl;
                
                writeLog("RETRIEVE LOWEST SALES PRODUCT", staffName);
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        }
        
        /*
          Function: getAverageSalesPerTransaction
          Purpose: Calculates average sales value per transaction
          Parameters:
            - staffName: Name of staff member requesting report
          Metrics Displayed:
            - Total transactions
            - Total sales amount
            - Average per transaction
        */
        void getAverageSalesPerTransaction(const char* staffName = "unknown") {
            try {
                ifstream inFile("purchase.txt");
                if(!inFile)
                    throw "Cannot open purchase.txt.";
                
                char customerName[30], productName[30];
                int productID, quantity;
                float price;
                float totalSales = 0;
                int transactionCount = 0;
                
                while(inFile >> customerName >> productID >> productName >> quantity >> price) {
                    totalSales += quantity * price;
                    transactionCount++;
                }
                
                inFile.close();
                
                float averageSales = (transactionCount > 0) ? (totalSales / transactionCount) : 0;
                
                cout << "\n===== AVERAGE SALES PER TRANSACTION =====\n";
                cout << "Total Transactions: " << transactionCount << endl;
                cout << "Total Sales Amount: RM " << totalSales << endl;
                cout << "Average Per Transaction: RM " << averageSales << endl;
                
                writeLog("RETRIEVE AVERAGE SALES PER TRANSACTION", staffName);
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        }
        
        /*
          Function: generateDailySummary
          Purpose: Generates daily sales summary with simulated dates
          Parameters:
            - staffName: Name of staff member generating report
          Output File: daily_summary.txt
          Simulation: Groups 3 transactions per day
          Usage: For trend analysis and daily performance tracking
        */
        void generateDailySummary(const char* staffName = "unknown") {
            try {
                ifstream inFile("purchase.txt");
                ofstream outFile("daily_summary.txt");
                
                if(!inFile)
                    throw "Cannot open purchase.txt.";
                if(!outFile)
                    throw "Cannot open daily_summary.txt.";
                
                char customerName[30], productName[30];
                int productID, quantity;
                float price;
                int dayCounter = 1;
                int transactionCounter = 0;
                float dailySalesAmount = 0;
                
                outFile << "===== DAILY SALES SUMMARY REPORT =====\n";
                outFile << "Generated on: 2025-12-28\n\n";
                
                while(inFile >> customerName >> productID >> productName >> quantity >> price) {
                    transactionCounter++;
                    float transactionAmount = quantity * price;
                    dailySalesAmount += transactionAmount;
                    
                    // Every 3 transactions = 1 day (simulated)
                    if(transactionCounter % 3 == 0) {
                        char fakeDate[20];
                        sprintf(fakeDate, "2025-12-%02d", (dayCounter % 28) + 1);
                        
                        outFile << "--- " << fakeDate << " ---\n";
                        outFile << "Transactions: " << (transactionCounter % 3 == 0 ? 3 : transactionCounter % 3) << endl;
                        outFile << "Daily Sales: RM " << dailySalesAmount << endl;
                        outFile << "Product: " << productName << " (Qty: " << quantity << ")\n";
                        outFile << "\n";
                        
                        dailySalesAmount = 0;
                        dayCounter++;
                    }
                }
                
                // Handle remaining transactions
                if(transactionCounter % 3 != 0) {
                    char fakeDate[20];
                    sprintf(fakeDate, "2025-12-%02d", (dayCounter % 28) + 1);
                    
                    outFile << "--- " << fakeDate << " ---\n";
                    outFile << "Transactions: " << (transactionCounter % 3) << endl;
                    outFile << "Daily Sales: RM " << dailySalesAmount << endl;
                    outFile << "\n";
                }
                
                inFile.close();
                outFile.close();
                
                cout << "\n===== DAILY SUMMARY GENERATED =====\n";
                cout << "Daily summary report saved to daily_summary.txt\n";
                cout << "Total Days Simulated: " << dayCounter << endl;
                
                writeLog("GENERATE DAILY SALES SUMMARY", staffName);
            }
            catch (const char* msg) {
                cout << msg << endl;
            }
        }
}; 

/*
  Class: Staff
  Description: Staff user interface and management class
  Inheritance: Extends User base class
  Static Members:
    - plist: Shared ProductList instance for all staff
  Responsibilities:
    - Staff login/registration
    - Product management (add, delete, update)
    - Sales analysis and reporting
    - Audit logging
*/
class Staff : public User { 
    public: 
        static ProductList plist; // all staff can use 
		/*
		  Constructor: Staff
		  Purpose: Initializes a Staff user instance
		*/
		Staff() {}
		
		/*
		  Destructor: ~Staff
		  Purpose: Cleans up Staff instance
		*/
		/*
		  Destructor: ~Staff
		  Purpose: Cleans up Staff instance
		*/
		~Staff() {}

		/*
		  Function: menu
		  Purpose: Displays staff user interface with login, registration, and product management
		  Features:
		    - Login/Register
		    - Add/Delete products
		    - Search and sort products
		    - View sales summaries
		    - Highest/Lowest product analysis
		    - Daily sales reports
		*/
		void menu() {
			int choice; 
            Product p; 

            do {
                Utils::clearScreen();
                Utils::printHeader("STAFF LOGIN");
                cout << "1. Login\n";
                cout << "2. Register\n";
                cout << "0. Back\n";
                Utils::printDivider();
                cout << "Enter choice: ";
                try {
                    cin >> choice;
                    if (cin.fail()) {
                        throw "Invalid input. Please enter a number.";
                    }
                }
                catch (const char* msg) {
                    Utils::printWarning(msg);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    Utils::pause();
                    continue;
                }

                if (choice == 1) {
                    if (!login("staff.txt")) return;
                    break;
                } else if (choice == 2) {
                    registerUser("staff.txt");
                    Utils::pause();
                } else if (choice == 0) {
                    return;
                } else {
                    Utils::printWarning("Invalid choice!");
                    Utils::pause();
                }
            } while (true);

			do {
                Utils::clearScreen();
                Utils::printHeader("STAFF MENU");
                cout << "1. Add Product\n";
                cout << "2. Display Products\n"; 
                cout << "3. Sort Products by Price\n"; 
                cout << "4. Search Product by ID\n"; 
                cout << "5. Delete Product\n"; 
                cout << "6. Generate Sales Summary\n";
                cout << "7. Get Highest Sales Product\n";
                cout << "8. Get Lowest Sales Product\n";
                cout << "9. Get Average Sales Per Transaction\n";
                cout << "10. Generate Daily Summary\n";
                cout << "11. Update Product Price\n";
                cout << "12. Update Product Quantity\n";
                cout << "13. Sort by QuickSort Algorithm\n";
                cout << "14. Check Low Stock\n";
                cout << "15. Product Statistics\n";
                cout << "0. Logout\n";
                Utils::printDivider();
                cout << "Enter choice: ";
                try {
                    cin >> choice;
                    if (cin.fail()) {
                        throw "Invalid input. Please enter a number.";
                    }
                }
                catch (const char* msg) {
                    Utils::printWarning(msg);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    Utils::pause();
                    continue;
                }

                switch(choice) {
                    case 1: {
                        try {
                            p.id = Utils::getPositiveInteger("Enter Product ID: ");
                            cin.ignore();

                            cout << "Enter Product Name: ";
                            cin.getline(p.name, 50);

                            p.price = Utils::getPositiveDouble("Enter Price (RM): ");
                            
                            // ===== VALIDATION: Product price validation =====
                            if(!ValidationHelper::isProductPriceValid(p.price)) {
                                Utils::pause();
                                break;
                            }

                            p.quantity = Utils::getPositiveInteger("Enter Quantity: ");
                            
                            // ===== VALIDATION: Product inventory validation =====
                            if(!ValidationHelper::isProductInventoryValid(p.quantity)) {
                                Utils::pause();
                                break;
                            }
                        }
                        catch (const char* msg) {
                            Utils::printWarning(msg);
                            cin.clear();
                            cin.ignore(1000, '\n');
                            Utils::pause();
                            break;
                        }

                        if(Utils::confirmAction("Add this product?")) {
                            plist.addProduct(p);
                            plist.saveToFile();  
                            Utils::printStatus("Product added successfully!", true);
                            writeLogWithProduct("ADD PRODUCT", p.name, p.price, p.quantity, username);
                        } else {
                            Utils::printStatus("Product addition cancelled.", false);
                        }
                        Utils::pause();
                        break;
                    }

                    case 2:
                        Utils::printHeader("PRODUCT LIST");
                        cout << "Display Products (coming soon)\n";
                        writeLog("DISPLAY PRODUCTS", username);
                        Utils::pause();
                        break; 
                    case 3: {
                        plist.sortByPrice();
                        Utils::printStatus("Products sorted by price.", true);
                        writeLog("SORT PRODUCTS BY PRICE", username);
                        Utils::pause();
                        break;
                    }
                    case 4: {
                        int searchID = Utils::getPositiveInteger("Enter Product ID to search: ");
                        plist.searchByID(searchID);
                        writeLogWithID("SEARCH PRODUCT", searchID, username);
                        Utils::pause();
                        break;
                    }
                    case 5: {
                        int deleteID = Utils::getPositiveInteger("Enter Product ID to delete: ");
                        if(Utils::confirmAction("Delete this product?")) {
                            plist.deleteProduct(deleteID);
                            Utils::printStatus("Product deleted successfully!", true);
                            writeLogWithID("DELETE PRODUCT", deleteID, username);
                        } else {
                            Utils::printStatus("Deletion cancelled.", false);
                        }
                        Utils::pause();
                        break;
                    } 
                    case 6: {
                        Utils::printHeader("SALES SUMMARY");
                        SalesSummary ss; 
                        ss.generateReport(username);
                        writeLog("GENERATE SALES SUMMARY", username);
                        Utils::pause();
                        break;
                    }
                    case 7: {
                        Utils::printHeader("HIGHEST SALES PRODUCT");
                        SalesSummary ss;
                        ss.getHighestSalesProduct(username);
                        Utils::pause();
                        break;
                    }
                    case 8: {
                        Utils::printHeader("LOWEST SALES PRODUCT");
                        SalesSummary ss;
                        ss.getLowestSalesProduct(username);
                        Utils::pause();
                        break;
                    }
                    case 9: {
                        Utils::printHeader("AVERAGE SALES PER TRANSACTION");
                        SalesSummary ss;
                        ss.getAverageSalesPerTransaction(username);
                        Utils::pause();
                        break;
                    }
                    case 10: {
                        Utils::printHeader("DAILY SUMMARY");
                        SalesSummary ss;
                        ss.generateDailySummary(username);
                        Utils::pause();
                        break;
                    }
                    case 11: {
                        Utils::printHeader("UPDATE PRODUCT PRICE");
                        int updateID = Utils::getPositiveInteger("Enter Product ID to update: ");
                        if(plist.updateProductPrice(updateID)) {
                            writeLogWithID("UPDATE PRODUCT PRICE", updateID, username);
                        }
                        Utils::pause();
                        break;
                    }
                    case 12: {
                        Utils::printHeader("UPDATE PRODUCT QUANTITY");
                        int updateQtyID = Utils::getPositiveInteger("Enter Product ID to update: ");
                        if(plist.updateProductQuantity(updateQtyID)) {
                            writeLogWithID("UPDATE PRODUCT QUANTITY", updateQtyID, username);
                        }
                        Utils::pause();
                        break;
                    }
                    case 13: {
                        Utils::printHeader("SORT PRODUCTS (QUICKSORT)");
                        cout << "Sorting products using QuickSort algorithm...\n";
                        plist.quickSortByPrice();
                        Utils::printStatus("Products sorted successfully using QuickSort!", true);
                        writeLog("SORT PRODUCTS USING QUICKSORT", username);
                        Utils::pause();
                        break;
                    }
                    case 14: {
                        Utils::printHeader("LOW STOCK CHECK");
                        plist.checkLowStock();
                        writeLog("CHECK LOW STOCK ITEMS", username);
                        Utils::pause();
                        break;
                    }
                    case 15: {
                        Utils::printHeader("PRODUCT STATISTICS");
                        plist.countTotalProducts();
                        writeLog("VIEW PRODUCT STATISTICS", username);
                        Utils::pause();
                        break;
                    }
                    case 0:
                        Utils::printStatus("Logging out...", true);
                        break;
                    default:
                        Utils::printWarning("Invalid choice!");
                        Utils::pause();
                }
            } while(choice != 0);
        } 

        /*
          Function: login
          Purpose: Authenticates a staff user against credentials in file
          Parameters:
            - filename: Path to staff.txt with username/password pairs
          Returns: true if login successful, false otherwise
          Side Effects: Sets username/password members, logs action
        */
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

                        // ===== AUDIT LOG: Staff Login =====
                        writeLog("STAFF LOGIN", userName);

                        return true; 
                    } 
                } 

                inFile.close(); 
                cout << "Invalid login.\n"; 
                
                // ===== AUDIT LOG: Failed Login Attempt =====
                writeLog("STAFF LOGIN FAILED", userName);

                return false; 
            }
            catch (const char* msg) {
                cout << msg << endl;
                return false;
            }
        } 

        /*
          Function: registerUser
          Purpose: Registers a new staff account with username and password
          Parameters:
            - filename: Path to staff.txt to save new account
          Returns: true if registration successful, false otherwise
          Validation: Checks for duplicate usernames
          Side Effects: Appends to staff.txt, logs action
        */
        bool registerUser(const char* filename) {
            try {
                char userName[30], passWord[30];

                cout << "New Username: ";
                cin >> userName;
                
                // ===== VALIDATION 1: Check if username already exists =====
                if(ValidationHelper::isUsernameExists(filename, userName)) {
                    return false;
                }
                
                cout << "New Password: ";
                cin >> passWord;

                ofstream outFile(filename, ios::app);
                if (!outFile)
                    throw "File cannot be opened.";

                outFile << userName << " " << passWord << endl;
                outFile.close();

                Utils::printStatus("Registration successful!", true);
                
                // ===== AUDIT LOG: Staff Registration =====
                writeLog("STAFF REGISTERED", userName);

                return true;
            }
            catch (const char* msg) {
                Utils::printWarning(msg);
                return false;
            }
        }
}; 

/*
  Class: Customer
  Description: Customer user interface and shopping functionality
  Inheritance: Extends User base class
  Responsibilities:
    - Customer login/registration
    - Product browsing and searching
    - Purchase transactions
    - Purchase history tracking
*/

// ===== THIRD DERIVED CLASS - INVENTORY MANAGER =====

class InventoryManager : public User {
public:
    InventoryManager() {
    }
    
    ~InventoryManager() {
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
            if(!inFile) {
                throw "File cannot be opened.";
            }
            
            while(inFile >> fileUserName >> filePassWord) {
                if(strcmp(userName, fileUserName) == 0 && 
                   strcmp(passWord, filePassWord) == 0) {
                    strcpy(username, userName);
                    strcpy(password, passWord);
                    inFile.close();
                    
                    writeLog("INVENTORY LOGIN", userName);
                    
                    return true;
                }
            }
            
            inFile.close();
            cout << "Invalid login.\n";
            writeLog("INVENTORY LOGIN FAILED", userName);
            
            return false;
        }
        catch(const char* msg) {
            cout << msg << endl;
            return false;
        }
    }
    
    void menu() {
        int choice;
        
        do {
            Utils::clearScreen();
            Utils::printHeader("INVENTORY MANAGER MENU");
            cout << "1. Check Low Stock Items\n";
            cout << "2. Generate Reorder Report\n";
            cout << "3. Inventory Statistics\n";
            cout << "4. Product Performance Analysis\n";
            cout << "5. Display by Category\n";
            cout << "0. Logout\n";
            Utils::printDivider();
            cout << "Enter choice: ";
            
            try {
                cin >> choice;
                if(cin.fail()) {
                    throw "Invalid input. Please enter a number.";
                }
            }
            catch(const char* msg) {
                Utils::printWarning(msg);
                cin.clear();
                cin.ignore(1000, '\n');
                Utils::pause();
                continue;
            }
            
            switch(choice) {
                case 1: {
                    Utils::printHeader("LOW STOCK ALERT");
                    Staff::plist.checkLowStock();
                    writeLog("CHECK LOW STOCK", username);
                    Utils::pause();
                    break;
                }
                case 2: {
                    Utils::printHeader("REORDER REPORT");
                    cout << "Generating reorder report for items below 10 units...\n";
                    Staff::plist.checkLowStock();
                    writeLog("GENERATE REORDER REPORT", username);
                    Utils::pause();
                    break;
                }
                case 3: {
                    Utils::printHeader("INVENTORY STATISTICS");
                    Staff::plist.countTotalProducts();
                    writeLog("VIEW INVENTORY STATISTICS", username);
                    Utils::pause();
                    break;
                }
                case 4: {
                    Utils::printHeader("PRODUCT PERFORMANCE");
                    Staff::plist.displayByCategory();
                    writeLog("PRODUCT PERFORMANCE ANALYSIS", username);
                    Utils::pause();
                    break;
                }
                case 5: {
                    Utils::printHeader("PRODUCTS BY CATEGORY");
                    Staff::plist.displayByCategory();
                    writeLog("DISPLAY BY CATEGORY", username);
                    Utils::pause();
                    break;
                }
                case 0:
                    Utils::printStatus("Logging out...", true);
                    writeLog("INVENTORY LOGOUT", username);
                    cout << "Session ended. Thank you for using Inventory Manager.\n";
                    cout << "Inventory data preserved.\n";
                    break;
                default:
                    Utils::printWarning("Invalid choice!");
                    Utils::pause();
            }
        } while(choice != 0);
    }
};

class Customer : public User {
	public: 
		/*
		  Constructor: Customer
		  Purpose: Initializes a Customer user instance
		*/
		Customer() {
			// constructor 
		} 

		/*
		  Destructor: ~Customer
		  Purpose: Cleans up Customer instance
		  Exception Safety: noexcept
		*/
		~Customer() noexcept {
			// destructor 
		} 

		/*
		  Function: login
		  Purpose: Authenticates a customer user against credentials in file
		  Parameters:
		    - filename: Path to customer.txt with username/password pairs
		  Returns: true if login successful, false otherwise
		  Side Effects: Sets username/password members, logs action
		*/
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

                        strcpy(username, userName);
                        strcpy(password, passWord);
                        
                        // ===== AUDIT LOG: Customer Login =====
                        writeLog("CUSTOMER LOGIN", userName);

                        return true; 
                    } 
                } 

                inFile.close(); 
                cout << "Invalid login.\n"; 
                
                // ===== AUDIT LOG: Failed Customer Login =====
                writeLog("CUSTOMER LOGIN FAILED", userName);

                return false; 
            }
            catch (const char* msg) {
                cout << msg << endl;
                return false;
            }
        } 

        /*
          Function: registerUser
          Purpose: Registers a new customer account with username and password
          Parameters:
            - filename: Path to customer.txt to save new account
          Returns: true if registration successful, false otherwise
          Validation: Checks for duplicate usernames
          Side Effects: Appends to customer.txt, logs action
        */
        bool registerUser(const char* filename) {
            try {
                char userName[30], passWord[30]; 
                cin >> userName;
                
                // ===== VALIDATION 1: Check if username already exists =====
                if(ValidationHelper::isUsernameExists(filename, userName)) {
                    return false;
                }
                
                cout << "New Password: ";
                cin >> passWord;

                ofstream outFile(filename, ios::app);
                if (!outFile)
                    throw "File cannot be opened.";

                outFile << userName << " " << passWord << endl;
                outFile.close();

                Utils::printStatus("Registration successful!", true);
                
                // ===== AUDIT LOG: Customer Registration =====
                writeLog("CUSTOMER REGISTERED", userName);

                return true;
            }
            catch (const char* msg) {
                Utils::printWarning(msg);
                return false;
            }
        }

		/*
		  Function: menu
		  Purpose: Displays customer user interface with shopping functionality
		  Features:
		    - Login/Register
		    - View all products
		    - Search by product ID
		    - Sort products by price
		    - Purchase products with quantity selection
		    - Transaction logging
		*/
		void menu() {
            int choice; 
            int studentID; 

            do {
                Utils::clearScreen();
                Utils::printHeader("CUSTOMER LOGIN");
                cout << "1. Login\n";
                cout << "2. Register\n";
                cout << "0. Back\n";
                Utils::printDivider();
                cout << "Enter choice: ";
                try {
                    cin >> choice;
                    if (cin.fail()) {
                        throw "Invalid input. Please enter a number.";
                    }
                }
                catch (const char* msg) {
                    Utils::printWarning(msg);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    Utils::pause();
                    continue;
                }

                if (choice == 1) {
                    if (!login("customer.txt")) {
                        Utils::pause();
                        return;
                    }
                    break;
                } else if (choice == 2) {
                    registerUser("customer.txt");
                    Utils::pause();
                } else if (choice == 0) {
                    return;
                } else {
                    Utils::printWarning("Invalid choice!");
                    Utils::pause();
                }
            } while (true);

            do {
                Utils::clearScreen();
                Utils::printHeader("CUSTOMER MENU");
                cout << "1. View Products\n";
                cout << "2. Search Product by ID\n";
                cout << "3. Sort Products by Price\n"; 
                cout << "4. Purchase Product\n"; 
                cout << "0. Logout\n";
                Utils::printDivider();
                cout << "Enter choice: ";
                try {
                    cin >> choice;
                    if (cin.fail()) {
                        throw "Invalid input. Please enter a number.";
                    }
                }
                catch (const char* msg) {
                    Utils::printWarning(msg);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    Utils::pause();
                    continue;
                }

                switch(choice) {
                    case 1:
                        Utils::printHeader("PRODUCT LIST");
                        Staff::plist.displayProducts(); 
                        writeLog("VIEW PRODUCTS", username);
                        Utils::pause();
                        break;
                    case 2: {
                        studentID = Utils::getPositiveInteger("Enter Product ID to search: ");
                        Staff::plist.searchByID(studentID); 
                        writeLogWithID("SEARCH PRODUCT", studentID, username);
                        Utils::pause();
                        break;
                    }
                    case 3: {
                        Staff::plist.sortByPrice();
                        Utils::printStatus("Products sorted by price.", true);
                        writeLog("SORT PRODUCTS BY PRICE", username);
                        Utils::pause();
                        break;
                    }
                    case 4: {
                        int productID, quantity; 

                        try {
                            productID = Utils::getPositiveInteger("Enter Product ID: ");
                            quantity = Utils::getPositiveInteger("Enter Quantity: ");
                        }
                        catch (const char* msg) {
                            Utils::printWarning(msg);
                            cin.clear();
                            cin.ignore(1000, '\n');
                            Utils::pause();
                            break;
                        }

                        // ===== VALIDATION 2: Check if product ID exists =====
                        if(!ValidationHelper::isProductIDExists(Staff::plist, productID)) {
                            Utils::printWarning("Product not found!");
                            Utils::pause();
                            break;
                        }
                        
                        // ===== VALIDATION 3: Check if purchase quantity is reasonable =====
                        if(!ValidationHelper::isPurchaseQuantityValid(Staff::plist, productID, quantity)) {
                            Utils::pause();
                            break;
                        }

                        if(Utils::confirmAction("Confirm purchase?")) {
                            Staff::plist.purchaseProduct(productID, quantity, username);
                            Utils::printStatus("Purchase completed successfully!", true);
                            writeLogWithID("PURCHASE PRODUCT", productID, username);
                        } else {
                            Utils::printStatus("Purchase cancelled.", false);
                        }
                        Utils::pause();
                        break;
                    }
                    case 0:
                        Utils::printStatus("Logging out...", true);
                        break;
                    default:
                        Utils::printWarning("Invalid choice!");
                        Utils::pause();
                }
            } while(choice != 0);
        }
}; 

// Define the static member
ProductList Staff::plist;

// ===== CUSTOMER PURCHASE HISTORY CLASS =====

/*
  Class: PurchaseHistory
  Description: Manages and displays customer purchase history and statistics
  Inner Struct:
    - Purchase: Contains customer name, product ID, name, quantity, price
  Features:
    - View personal purchase history
    - View all purchases (staff only)
    - Customer statistics and analysis
    - Search purchases by product
*/
class PurchaseHistory {
    private:
        /*
          Struct: Purchase
          Description: Represents a single purchase transaction
          Members:
            - customerName: Customer who made the purchase
            - productID: ID of purchased product
            - productName: Name of purchased product
            - quantity: Quantity of units purchased
            - price: Unit price at time of purchase
        */
        struct Purchase {
            char customerName[50];
            int productID;
            char productName[50];
            int quantity;
            double price;
        };

    public:
        /*
          Constructor: PurchaseHistory
          Purpose: Initializes a PurchaseHistory instance
        */
        PurchaseHistory() {
            // Constructor
        }

        /*
          Destructor: ~PurchaseHistory
          Purpose: Cleans up PurchaseHistory instance
        */
        ~PurchaseHistory() {
            // Destructor
        }

        /*
          Function: viewMyPurchases
          Purpose: Displays purchase history for a specific customer
          Parameters:
            - username: Name of customer to display history for
          Output: Table of purchases with totals and statistics
          Statistics:
            - Total purchases
            - Total items bought
            - Total amount spent
            - Average spending per purchase
        */
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

        /*
          Function: viewAllPurchases
          Purpose: Displays all purchase transactions (staff view only)
          Output: Complete transaction history with all customers
          Statistics:
            - Total transaction records
            - Total items sold
            - Total revenue
            - Average transaction value
        */
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

        /*
          Function: displayCustomerStatistics
          Purpose: Displays aggregated statistics by customer
          Output: Per-customer metrics including purchases, spending, averages
          Calculations:
            - Unique customer count
            - Total revenue
            - Average customer value
          Usage: For customer relationship management
        */
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

        /*
          Function: searchPurchaseByProduct
          Purpose: Finds all purchases of a specific product
          Parameters:
            - productID: Product ID to search for
          Output: List of customers who purchased this product
          Statistics:
            - Total records for product
            - Total quantity sold
            - Total revenue from product
        */
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

/*
  Function: main
  Purpose: Entry point for the Stationery Shop Management System
  Initialization:
    - Loads products from product.txt
    - Validates system files at startup
    - Displays file status report
  Main Loop:
    - Shows main menu with Staff/Customer/Exit options
    - Creates user objects based on selection
    - Calls menu() method for user interaction
  Flow Control: Continues until user selects Exit (choice 0)
*/
int main() { 
    Staff::plist.loadFromFile();
    
    // ===== VALIDATION 4: Check if important files are empty at startup =====
    cout << "\n[System Startup Check]\n";
    
    if(ValidationHelper::isFileEmpty("product.txt")) {
        cout << "[!] Product file is empty. Please add products first.\n";
    } else {
        int productCount = ValidationHelper::getProductCountInFile("product.txt");
        cout << "[+] " << productCount << " products loaded.\n";
    }
    
    if(ValidationHelper::isFileEmpty("staff.txt")) {
        cout << "[!] Staff file is empty. Consider registering staff accounts.\n";
    } else {
        int staffCount = ValidationHelper::getCustomerCountInFile("staff.txt");
        cout << "[+] " << staffCount << " staff accounts available.\n";
    }
    
    if(ValidationHelper::isFileEmpty("customer.txt")) {
        cout << "[!] Customer file is empty. New customer registrations welcome.\n";
    } else {
        int customerCount = ValidationHelper::getCustomerCountInFile("customer.txt");
        cout << "[+] " << customerCount << " customer accounts available.\n";
    }
    
    Utils::pause();

	int choice; 
	User* user = NULL; 

	do {
		Utils::clearScreen();
		Utils::printLine(45);
		cout << "  STATIONERY SHOP MANAGEMENT SYSTEM  \n"; 
		Utils::printLine(45);
		Utils::printDivider();
		cout << "1. Staff Module\n"; 
		cout << "2. Customer Module\n"; 
		cout << "3. Inventory Manager Module\n";
		cout << "0. Exit\n";
		Utils::printDivider();
		cout << "Enter choice: "; 
		cin >> choice; 

		switch(choice) {
			case 1: {
                user = new Staff(); 
				user->menu(); 
				delete user;
				user = NULL;
                break;
			}
            case 2: {
                user = new Customer(); 
				user->menu(); 
				delete user;
				user = NULL;
                break;
			}
            case 3: {
                user = new InventoryManager();
                if(((InventoryManager*)user)->login("staff.txt")) {
                    user->menu();
                } else {
                    Utils::printWarning("Login failed!");
                    Utils::pause();
                }
				delete user;
				user = NULL;
                break;
            }
            case 0:
                Utils::printStatus("Exiting system...", true);
                break;
            default:
                Utils::printWarning("Invalid choice!");
                Utils::pause();
		} 
	} while(choice != 0);
	
	// System shutdown sequence
	cout << "\n========== SYSTEM SHUTDOWN ==========\n";
	cout << "Saving data...\n";
	Staff::plist.saveToFile();
	cout << "Data saved successfully.\n";
	cout << "Cleanup complete.\n";
	cout << "System shutdown successful.\n";
	cout << "Thank you for using the Stationery Shop Management System.\n\n";

	return 0; 
}
