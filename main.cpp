#include <iostream> 
#include <fstream> 
#include <cstring> 
#include <ctime>
#include <sstream>
#include <clocale>
using namespace std;

// UTF-8 Support for Windows
#ifdef _WIN32
#include <windows.h>
#endif 

// ===== AUDIT LOG SYSTEM =====

/*
  Function: writeLog 1
  Purpose: Writes a generic audit log entry to log.txt with timestamp and username
  Parameters:
    - action: The action being logged (e.g., "LOGIN", "DELETE PRODUCT")
    - username: The user who performed the action (default: "unknown")
  Returns: void
  Usage: Called whenever a significant action occurs in the system
*/
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

/*
  Function: writeLogWithID
  Purpose: Writes an audit log entry with additional product ID information
  Parameters:
    - action: The action being logged (e.g., "DELETE PRODUCT")
    - id: The product ID involved in the action
    - username: The user who performed the action (default: "unknown")
  Returns: void
  Usage: Used when logging actions that involve a specific product ID
*/
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

/*
  Function: writeLogWithProduct
  Purpose: Writes an audit log entry with detailed product information
  Parameters:
    - action: The action being logged (e.g., "ADD PRODUCT", "UPDATE PRICE")
    - productName: The name of the product being logged
    - price: The price of the product in RM
    - qty: The quantity affected by the action
    - username: The user who performed the action (default: "unknown")
  Returns: void
  Usage: Logs detailed product operations for audit trail
*/
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

/*
  Function: writeLogPurchase
  Purpose: Writes an audit log entry for customer purchase transactions
  Parameters:
    - customerName: Name of the customer making the purchase
    - productName: Name of the product being purchased
    - qty: Quantity of units purchased
    - totalPrice: Total transaction amount in RM
    - username: The staff member processing the purchase (default: "unknown")
  Returns: void
  Usage: Logs all purchase activities for business auditing
*/
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

/*
  Class: Utils
  Description: Utility class providing static helper methods for UI, input validation, and user interaction
  Features:
    - Screen management (clear screen, print headers)
    - User confirmations and prompts
    - Input validation for numeric values
    - Status and warning messages
    - Line separators and formatting
  Design Pattern: Static utility class (similar to Java utils)
*/
class Utils {
public:
    /*
      Function: pause
      Purpose: Pauses program execution and waits for user to press Enter
      Usage: Used before clearing screen or returning to previous menu
    */
    static void pause() {
        cout << "\nPress Enter to continue...";
        cin.ignore(1000, '\n');
        cin.get();
    }
    
    /*
      Function: clearScreen
      Purpose: Clears the console screen (works on Windows and Linux)
      Platform Support: Windows (cls), Unix/Linux (clear)
    */
    static void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    /*
      Function: confirmAction
      Purpose: Asks user to confirm an action with Yes/No prompt
      Returns: true if user enters 'Y' or 'y', false otherwise
      Usage: For critical operations like deletion
    */
    static bool confirmAction() {
        char response;
        cout << "\nAre you sure? (Y/N): ";
        cin >> response;
        cin.ignore();
        
        return (response == 'Y' || response == 'y');
    }
    
    /*
      Function: confirmAction (overloaded)
      Purpose: Asks user to confirm with a custom message
      Parameters:
        - message: Custom confirmation message to display
      Returns: true if user confirms, false otherwise
    */
    static bool confirmAction(const char* message) {
        char response;
        cout << "\n" << message << " (Y/N): ";
        cin >> response;
        cin.ignore();
        
        return (response == 'Y' || response == 'y');
    }
    
    /*
      Function: printLine
      Purpose: Prints a standard line separator (default 37 equals signs)
      Usage: For visual separation between sections
    */
    static void printLine() {
        cout << "=====================================\n";
    }
    
    /*
      Function: printLine (overloaded)
      Purpose: Prints a line separator with custom length
      Parameters:
        - length: Number of equals signs to print
      Usage: For custom-width separators
    */
    static void printLine(int length) {
        for(int i = 0; i < length; i++) {
            cout << "=";
        }
        cout << "\n";
    }
    
    /*
      Function: printHeader
      Purpose: Prints a formatted section header with title and line separators
      Parameters:
        - title: The title to display in the header
      Side Effects: Clears screen before printing
    */
    static void printHeader(const char* title) {
        Utils::clearScreen();
        Utils::printLine();
        cout << "     " << title << endl;
        Utils::printLine();
    }
    
    /*
      Function: printStatus
      Purpose: Displays a formatted status message (success or error)
      Parameters:
        - message: The status message to display
        - isSuccess: true for [OK] message, false for [✗ ERROR] message
    */
    static void printStatus(const char* message, bool isSuccess = true) {
        if(isSuccess) {
            cout << "\n[OK] " << message << endl;
        } else {
            cout << "\n[✗ ERROR] " << message << endl;
        }
    }
    
    /*
      Function: printWarning
      Purpose: Displays a warning message with [!] prefix
      Parameters:
        - message: The warning message to display
    */
    static void printWarning(const char* message) {
        cout << "\n[!] " << message << endl;
    }
    
    /*
      Function: printDivider
      Purpose: Prints a menu section divider (37 hyphens)
      Usage: Separates menu items from input area
    */
    static void printDivider() {
        cout << "-------------------------------------\n";
    }
    
    /*
      Function: confirmProceeding
      Purpose: Asks user if they want to proceed with an operation
      Returns: true if user confirms, false otherwise
    */
    static bool confirmProceeding() {
        return Utils::confirmAction("Do you want to proceed?");
    }
    
    /*
      Function: getPositiveInteger
      Purpose: Prompts user for a positive integer with validation
      Parameters:
        - prompt: The prompt message to display
      Returns: A positive integer value (> 0)
      Error Handling: Catches invalid input and re-prompts user
    */
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
    
    /*
      Function: getPositiveDouble
      Purpose: Prompts user for a positive decimal number with validation
      Parameters:
        - prompt: The prompt message to display
      Returns: A positive double value (> 0)
      Error Handling: Catches invalid input and re-prompts user
    */
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
};

/*
  Struct: Product
  Description: Represents a product in the stationery shop inventory
  Members:
    - id: Unique product identifier
    - name: Product name (max 50 characters)
    - price: Product price in RM
    - quantity: Number of units in stock
*/
struct Product {
	int id; 
	char name[50]; 
	double price; 
	int quantity; 
}; 

/*
  Struct: Node
  Description: Node structure for the linked list implementation
  Members:
    - data: Product object stored in this node
    - next: Pointer to the next node in the list
  Design Pattern: Standard singly-linked list node
*/
struct Node {
	Product data; 
	Node* next; 
}; 

/*
  Class: ProductList
  Description: Manages the inventory of products using a singly-linked list data structure
  Data Structure: Singly-linked list
  Key Operations: Add, Delete, Search, Sort, Update, Purchase
  File Operations: Load from and save to product.txt
  Features:
    - Dynamic memory allocation for products
    - Sorting by price
    - Search by ID with details
    - Purchase with quantity checks
    - Category display (Budget/Standard/Premium)
    - Stock analysis and statistics
*/
class ProductList {
    private: 
        Node* head; 

    public:
        /*
          Constructor: ProductList
          Purpose: Initializes an empty product list
          Initial State: head pointer set to NULL
        */
        ProductList() {
            head = NULL; 
        }    

        /*
          Destructor: ~ProductList
          Purpose: Frees all allocated memory when the list is destroyed
          Implementation: Traverses and deletes each node
          Importance: Prevents memory leaks
        */
        ~ProductList() {
            Node* temp; 
            while(head != NULL) {
                temp = head; 
                head = head->next; 
                delete temp; 
            } 
        } 

        /*
          Function: addProduct
          Purpose: Adds a new product to the end of the linked list
          Parameters:
            - p: Product struct containing id, name, price, quantity
          Implementation: Creates new node and appends to end
        */
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

        /*
          Function: displayProducts
          Purpose: Displays all products in a formatted table
          Output Format: ID | Name | Price | Quantity
          Handles: Empty list case
        */
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

        /*
          Function: sortByPrice
          Purpose: Sorts products by price in ascending order
          Algorithm: Bubble sort on linked list
          Time Complexity: O(n²)
          Stability: Sorts in-place without creating new list
        */
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

        /*
          Function: searchByID
          Purpose: Searches for a product by ID and displays its details
          Parameters:
            - targetID: The product ID to search for
          Returns: true if product found, false otherwise
          Side Effect: Prints product details to console
        */
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
        
        /*
          Function: searchByIDExists
          Purpose: Checks if a product ID exists without printing output
          Parameters:
            - targetID: The product ID to check
          Returns: true if product exists, false otherwise
          Usage: For validation purposes
        */
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
        
        /*
          Function: getProductQuantity
          Purpose: Retrieves the quantity of a product by its ID
          Parameters:
            - targetID: The product ID to query
          Returns: Quantity in stock, or -1 if product not found
          Usage: For inventory checking during purchase
        */
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
        
        /*
          Function: getProductPrice
          Purpose: Retrieves the price of a product by its ID
          Parameters:
            - targetID: The product ID to query
          Returns: Price in RM, or -1.0 if product not found
          Usage: For price validation and purchase calculations
        */
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

        /*
          Function: purchaseProduct
          Purpose: Processes a customer purchase and updates inventory
          Parameters:
            - productID: ID of product to purchase
            - quantity: Number of units to purchase
            - customerName: Name of customer (for logging)
          Returns: true if purchase successful, false if insufficient stock
          Side Effects: Updates product.txt, sales.txt, purchase.txt, and log.txt
        */
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

        /*
          Function: deleteProduct
          Purpose: Deletes a product from the inventory by ID
          Parameters:
            - productID: The ID of the product to delete
          Returns: true if deletion successful, false if product not found
          Side Effects: Updates product.txt file
        */
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
 
        /*
          Function: saveToFile
          Purpose: Saves all products from linked list to product.txt file
          Format: id|name|price|quantity (one product per line)
          Side Effect: Overwrites product.txt with current inventory
        */
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

        /*
          Function: loadFromFile
          Purpose: Loads all products from product.txt into the linked list
          Format Expected: id|name|price|quantity (one product per line)
          Called: At system startup to populate inventory
        */
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

        /*
          Function: updateProductPrice
          Purpose: Updates the price of a product by its ID
          Parameters:
            - id: The product ID to update
          Returns: true if update successful, false otherwise
          Input Validation: Checks for negative prices
          Side Effects: Updates product.txt file
        */
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

            cout << "\n[OK] Price updated successfully!\n"; 
            cout << "Old Price: RM " << oldPrice << " → New Price: RM " << newPrice << endl; 

            return true; 
        } 

        /*
          Function: updateProductQuantity
          Purpose: Updates the stock quantity of a product by its ID
          Parameters:
            - id: The product ID to update
          Returns: true if update successful, false otherwise
          Input Validation: Checks for negative quantities
          Side Effects: Updates product.txt file
        */
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

            cout << "\n[OK] Quantity updated successfully!\n"; 
            cout << "Old Quantity: " << oldQuantity << " → New Quantity: " << newQuantity << endl; 

            return true; 
        } 

        /*
          Function: checkLowStock
          Purpose: Reports all products with stock below 10 units
          Threshold: 10 units (configurable as LOW_STOCK_THRESHOLD)
          Alerts: Critical status for items below 5 units, Out of stock for 0 units
          Usage: For inventory management and reordering
        */
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

        /*
          Function: displayByCategory
          Purpose: Displays products organized by price category
          Categories:
            - Budget: < RM 50
            - Standard: RM 50 - RM 150
            - Premium: > RM 150
          Usage: For categorized product browsing
        */
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

        /*
          Function: countTotalProducts
          Purpose: Provides comprehensive inventory statistics
          Statistics Calculated:
            - Total product types
            - Total units in stock
            - Total inventory value in RM
            - Average price per product
            - Average quantity per product
          Returns: Total number of product types
        */
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
class SalesSummary {
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
            case 0:
                Utils::printStatus("Exiting system...", true);
                break;
            default:
                Utils::printWarning("Invalid choice!");
                Utils::pause();
		} 
	} while(choice != 0); 

	return 0; 
} 
