#include <iostream> 
#include <fstream> 
#include <cstring> 
using namespace std; 

int main() {
	int choice; 

	do {
		cout << "\n===== Stationery Shop Management System =====\n"; 
		cout << "1. Staff Module\n"; 
		cout << "2. Customer Module\n"; 
		cout << "0. Exit\n"; 
		cout << "Enter choice: "; 
		cin >> choice; 

		switch(choice) {
			case 1:
                cout << "Staff Module (coming soon)\n";
                break;
            case 2:
                cout << "Customer Module (coming soon)\n";
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
