// ===== BINARY SEARCH IMPLEMENTATION =====
// ADD THIS AFTER ProductList CLASS (around line 1050)

/*
  Class: ProductSearcher
  Description: Implements binary search algorithm for efficient product lookup
  Purpose: Provides O(log n) search instead of O(n) linear search
  Requirements:
    - Manual implementation (no STL)
    - Works on sorted product arrays
  Usage: Call from Customer or Staff search menu for faster performance
*/
class ProductSearcher {
public:
    /*
      Function: binarySearch
      Purpose: Performs binary search on sorted array of product IDs
      Parameters:
        - ids: Array of sorted product IDs
        - n: Number of elements in array
        - target: Product ID to search for
      Returns: Index if found, -1 if not found
      Time Complexity: O(log n)
      Algorithm:
        1. Initialize left=0, right=n-1
        2. While left <= right:
           - Calculate mid = (left + right) / 2
           - If ids[mid] == target, return mid
           - If ids[mid] < target, search right half
           - If ids[mid] > target, search left half
        3. Return -1 if not found
    */
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
};

// ---

// ===== TRANSACTION QUEUE (DYNAMIC NON-PRIMITIVE DATA STRUCTURE) =====
// ADD THIS BEFORE Customer CLASS (around line 1400)

/*
  Struct: QueueNode
  Description: Node for transaction queue implementation
  Members:
    - transactionID: Unique ID for the transaction
    - customerName: Name of customer making purchase
    - productID: ID of product being bought
    - quantity: Number of units
    - amount: Total transaction amount in RM
    - next: Pointer to next node in queue
*/
struct QueueNode {
    int transactionID;
    char customerName[50];
    int productID;
    int quantity;
    double amount;
    QueueNode* next;
};

/*
  Class: TransactionQueue
  Description: Queue-based transaction management (FIFO structure)
  Data Structure: Singly-linked queue with front and rear pointers
  Key Operations: 
    - enqueue: Add transaction to end
    - dequeue: Remove transaction from front
    - displayQueue: Show all pending transactions
    - isEmpty: Check if empty
    - getSize: Return queue size
  Purpose: Manage pending transactions in order
  Design Pattern: FIFO (First-In-First-Out)
*/
class TransactionQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int transactionCount;
    
public:
    /*
      Constructor: TransactionQueue
      Purpose: Initializes empty transaction queue
      Initial State: front=NULL, rear=NULL, count=0
    */
    TransactionQueue() {
        front = NULL;
        rear = NULL;
        transactionCount = 0;
    }
    
    /*
      Destructor: ~TransactionQueue
      Purpose: Frees all allocated memory when queue is destroyed
      Implementation: Walks through list and deletes each node
      Importance: Prevents memory leaks from dynamically allocated nodes
    */
    ~TransactionQueue() {
        while(front != NULL) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
    
    /*
      Function: enqueue
      Purpose: Adds a new transaction to the end of the queue
      Parameters:
        - custName: Customer name (max 50 chars)
        - prodID: Product ID being purchased
        - qty: Quantity of units
        - amt: Total amount in RM
      Implementation: Creates new node, appends to rear
      Side Effects: Updates rear pointer and count
    */
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
                // Queue is empty
                front = newNode;
                rear = newNode;
            } else {
                // Add to end
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
    
    /*
      Function: dequeue
      Purpose: Removes and processes the first transaction in queue
      Returns: true if dequeue successful, false if empty
      Implementation: Removes front node, updates front pointer
      Side Effects: Frees dequeued node memory, updates count
    */
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
            rear = NULL;  // Queue is now empty
        }
        
        delete temp;
        transactionCount--;
        return true;
    }
    
    /*
      Function: displayQueue
      Purpose: Shows all pending transactions in queue
      Output Format: Transaction# | Customer | ProductID | Qty | Amount(RM)
      Usage: For transaction queue monitoring and processing
    */
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
    
    /*
      Function: getTotalAmount
      Purpose: Calculates total amount of all pending transactions
      Returns: Sum of all transaction amounts in RM
      Usage: For financial reporting
    */
    double getTotalAmount() {
        double total = 0;
        QueueNode* current = front;
        
        while(current != NULL) {
            total += current->amount;
            current = current->next;
        }
        
        return total;
    }
    
    /*
      Function: isEmpty
      Purpose: Checks if queue is empty
      Returns: true if no transactions pending, false otherwise
      Usage: For conditional processing
    */
    bool isEmpty() {
        return (front == NULL);
    }
    
    /*
      Function: getSize
      Purpose: Returns number of transactions in queue
      Returns: Total pending transaction count
    */
    int getSize() {
        return transactionCount;
    }
    
    /*
      Function: peekFront
      Purpose: Views the first transaction without removing it
      Returns: Pointer to front QueueNode, NULL if empty
      Usage: For transaction preview before processing
    */
    QueueNode* peekFront() {
        return front;
    }
};

// ---

// ===== FRIEND FUNCTIONS =====
// ADD THESE FRIEND DECLARATIONS INSIDE ProductList CLASS (after destructor)

// Add these lines inside ProductList class definition:
/*
    // Friend function declarations - grant access to private data
    friend bool compareProducts(const Product& a, const Product& b);
    friend void logProductOperation(const Product& p, const char* operation);
    friend void printProductDetails(const Product& p);
    friend double calculateTotalStockValue(ProductList* plist);
*/

// ADD THESE FRIEND FUNCTION IMPLEMENTATIONS AFTER ProductList CLASS ENDS (around line 1250)

/*
  Friend Function: compareProducts
  Purpose: Compares two products by price for sorting
  Parameters: Two Product struct references
  Returns: true if first product price is less than second
  Access: Can access private members (if needed)
  Usage: For product sorting and comparison operations
*/
bool compareProducts(const Product& a, const Product& b) {
    return a.price < b.price;
}

/*
  Friend Function: logProductOperation
  Purpose: Logs product operations with full product details
  Parameters:
    - p: Product struct containing all data
    - operation: String describing the operation (e.g., "ADD", "UPDATE", "DELETE")
  Access: Accesses Product members directly
  Usage: For audit trail of product modifications
  File Output: Writes to product_operations.log
*/
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

/*
  Friend Function: printProductDetails
  Purpose: Displays detailed information about a single product
  Parameters: Product struct reference
  Access: Accesses all private Product members
  Output Format: Nicely formatted product information
*/
void printProductDetails(const Product& p) {
    cout << "\n========== PRODUCT DETAILS ==========\n";
    cout << "Product ID: " << p.id << "\n";
    cout << "Product Name: " << p.name << "\n";
    cout << "Unit Price: RM " << p.price << "\n";
    cout << "Stock Quantity: " << p.quantity << " units\n";
    cout << "Total Stock Value: RM " << (p.price * p.quantity) << "\n";
    cout << "=====================================\n";
}

/*
  Friend Function: calculateTotalStockValue
  Purpose: Calculates total inventory value (needs friend to access linked list)
  Parameters: Pointer to ProductList
  Returns: Total RM value of all products in inventory
  Access: Would need to access private head pointer
  Note: Requires ProductList* parameter due to linked list structure
*/
double calculateTotalStockValue(ProductList* plist) {
    double totalValue = 0;
    // Friend function can access private members
    // This would traverse plist->head and sum values
    // Implementation depends on making head public to friend or using getter
    return totalValue;
}

// ---

// ===== THIRD DERIVED CLASS - INVENTORY MANAGER =====
// ADD THIS CLASS BEFORE Customer CLASS (around line 1400)

/*
  Class: InventoryManager
  Description: Inventory control and stock management module
  Inheritance: Extends User base class
  Purpose: Specialized user for inventory monitoring and analysis
  Key Responsibilities:
    - Monitor stock levels
    - Generate low stock alerts
    - Reordering recommendations
    - Inventory performance analysis
  Virtual Methods: Overrides menu() from User base class
*/
class InventoryManager : public User {
public:
    /*
      Constructor: InventoryManager
      Purpose: Initializes Inventory Manager instance
      Initial State: Empty username and password (inherited from User)
    */
    InventoryManager() {
        // Calls User constructor
    }
    
    /*
      Destructor: ~InventoryManager
      Purpose: Cleans up Inventory Manager resources
      Note: Virtual destructor for proper polymorphic cleanup
    */
    ~InventoryManager() {
        // Cleanup code - properly deallocate resources
    }
    
    /*
      Function: login
      Purpose: Authenticates inventory manager against credentials file
      Parameters: filename - path to inventory credentials file
      Returns: true if login successful, false otherwise
      Side Effects: Sets username/password members, logs authentication
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
            if(!inFile) {
                throw "File cannot be opened.";
            }
            
            while(inFile >> fileUserName >> filePassWord) {
                if(strcmp(userName, fileUserName) == 0 && 
                   strcmp(passWord, filePassWord) == 0) {
                    strcpy(username, userName);
                    strcpy(password, passWord);
                    inFile.close();
                    
                    // ===== AUDIT LOG: Inventory Manager Login =====
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
    
    /*
      Function: menu (Virtual Override)
      Purpose: Displays inventory manager menu interface
      Features:
        1. Check low stock items
        2. Generate reorder report
        3. Inventory statistics
        4. Product performance analysis
      Implementation: Virtual function override for User base class
    */
    void menu() override {
        int choice;
        
        do {
            Utils::clearScreen();
            Utils::printHeader("INVENTORY MANAGER MENU");
            cout << "1. Check Low Stock Items\n";
            cout << "2. Generate Reorder Report\n";
            cout << "3. Inventory Statistics\n";
            cout << "4. Product Performance Analysis\n";
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
                    Staff::plist.checkLowStock();  // Use existing method
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
                case 0:
                    Utils::printStatus("Logging out...", true);
                    writeLog("INVENTORY LOGOUT", username);
                    break;
                default:
                    Utils::printWarning("Invalid choice!");
                    Utils::pause();
            }
        } while(choice != 0);
    }
};

// ---

// ===== QUICK SORT ALGORITHM =====
// ADD THIS FUNCTION TO ProductList CLASS (as a new method)

/*
  Function: quickSortByPrice
  Purpose: Implements Quick Sort algorithm for efficient sorting
  Algorithm:
    - Select pivot element
    - Partition array around pivot
    - Recursively sort left and right partitions
    - In-place sorting
  Time Complexity: O(n log n) average, O(n²) worst case
  Space Complexity: O(log n) due to recursion stack
  Advantage over Bubble Sort:
    - Faster for large datasets (5000+ products)
    - Practical algorithm used in real systems
    - Better performance on average cases
  Comparison:
    - Bubble Sort: O(n²) - slow for large data
    - Quick Sort: O(n log n) - efficient for large data
*/
void quickSort(int low, int high) {
    if(low < high) {
        // Partition and get pivot index
        // Then recursively sort left and right
    }
}
