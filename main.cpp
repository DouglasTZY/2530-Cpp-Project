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
                    ofstream saleFile("sales.txt", ios::app); 
                    saleFile << cur->data.id << "|" 
                             << cur->data.name << "|" 
                             << quantity << "|" 
                             << cur->data.price * quantity << endl; 
                
                    saleFile.close();  
                    
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
            ofstream outFile("product.txt"); 

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

        void loadFromFile() {
            ifstream inFile("product.txt"); 
            if(!inFile) return; 

            Product p; 
            char line[200]; 

            while(inFile.getline(line, 200)) {
                sscanf(line, "%d|%[^|]|%lf|%d", &p.id, p.name, &p.price, &p.quantity); 
                addProduct(p); 
            } 

            inFile.close(); 
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

class Staff : public User { 
    public: 
        static ProductList plist; // all staff can use 
		Staff() {} 
		~Staff() {} 

		void menu() {
			int choice; 
            Product p; 

			do {
                cout << "\n--- Staff Menu ---\n";
                cout << "1. Add Product\n";
                cout << "2. Display Products\n"; 
                cout << "3. Sort Products by Price\n"; 
                cout << "4. Search Product by ID\n"; 
                cout << "5. Delete Product\n";
                cout << "0. Logout\n";
                cout << "Enter choice: ";
                cin >> choice;

                switch(choice) {
                    case 1:
                        cout << "Enter Product ID: ";
                        cin >> p.id;
                        cin.ignore();

                        cout << "Enter Product Name: ";
                        cin.getline(p.name, 50);

                        cout << "Enter Price: ";
                        cin >> p.price;

                        cout << "Enter Quantity: ";
                        cin >> p.quantity;

                        plist.addProduct(p);
                        plist.saveToFile();  

                        cout << "Product added successfully!\n";
                        break;

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
                    case 0:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid choice!\n";
                }
            } while(choice != 0);
        } 
}; 

class Customer : public User {
	public: 
		Customer() {
			// constructor 
		} 

		~Customer() {
			// destructor 
		} 

		void menu() {
        int choice; 
        int studentID; 

        do {
            cout << "\n--- Customer Menu ---\n";
            cout << "1. View Products\n";
            cout << "2. Search Product by ID\n";
            cout << "3. Sort Products by Price\n"; 
            cout << "4. Purchase Product\n"; 
            cout << "0. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

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
                case 4: 
                    int productID, quantity; 

                    cout << "Enter Product ID: "; 
                    cin >> productID; 
                    cout << "Enter Quantity: "; 
                    cin >> quantity; 

                    Staff::plist.purchaseProduct(productID, quantity); 
                    break; 
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
