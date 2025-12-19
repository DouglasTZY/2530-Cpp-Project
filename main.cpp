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
    private: 
        static ProductList plist; // all staff can use 

	public: 
		Staff() {} 
		~Staff() {} 

		void menu() {
			int choice; 
            Product p; 

			do {
                cout << "\n--- Staff Menu ---\n";
                cout << "1. Add Product\n";
                cout << "2. Display Products\n";
                cout << "0. Logout\n";
                cout << "Enter choice: ";
                cin >> choice;

                switch(choice) {
                    case 1:
                        cout << "Add Product (coming soon)\n";
                        break;
                    case 2:
                        cout << "Display Products (coming soon)\n";
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

        do {
            cout << "\n--- Customer Menu ---\n";
            cout << "1. View Products\n";
            cout << "2. Search Product\n";
            cout << "0. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    cout << "View Products (coming soon)\n";
                    break;
                case 2:
                    cout << "Search Product (coming soon)\n";
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

int main() { 
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
