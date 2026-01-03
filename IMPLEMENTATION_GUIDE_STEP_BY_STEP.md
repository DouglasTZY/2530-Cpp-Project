# STEP-BY-STEP IMPLEMENTATION GUIDE
## Complete Checklist for TDS4223 Project Completion

---

## PHASE 1: IMMEDIATE ACTIONS (Do TODAY - 2-3 hours)

### Step 1: Replace product.txt with 50+ Records
**Time**: 5 minutes
**File**: product.txt
**Action**: 
1. Copy all content from SAMPLE_PRODUCTS.txt
2. Replace entire product.txt with this content
3. Verify file has exactly 50 products

**Verification**:
```
✓ File contains 50 lines
✓ Format: ID|Name|Price|Quantity
✓ IDs are sequential (1-50)
✓ Prices vary (budget, standard, premium)
✓ Quantities differ (low, medium, high stock)
```

**Impact**: +5 marks (meets 50-record requirement)

---

### Step 2: Add Binary Search Algorithm
**Time**: 30-40 minutes
**Location**: Add after ProductList class (after destructor, before SalesSummary class)
**File**: main.cpp (around line 1050)

**What to copy from CODE_SNIPPETS_FOR_INTEGRATION.cpp**:
- Lines with "===== BINARY SEARCH IMPLEMENTATION ====="
- Entire ProductSearcher class

**Where to place**:
```
After: }  // End of ProductList destructor
Before: class SalesSummary {  // Start of SalesSummary class
```

**Integration into menu**:
In Staff menu, replace:
```cpp
case 4: {
    int searchID = Utils::getPositiveInteger("Enter Product ID to search: ");
    plist.searchByID(searchID);
    // ADD THIS:
    ProductSearcher::binarySearch(...);
}
```

**Testing**:
- [ ] Code compiles without errors
- [ ] Search works for existing products
- [ ] Returns -1 for non-existent products
- [ ] Shows comparison count

**Impact**: +8 marks (implements searching algorithm)

---

### Step 3: Add Transaction Queue (DNP Structure)
**Time**: 40-50 minutes
**Location**: Add before Customer class (around line 1400)
**File**: main.cpp

**What to copy**:
- QueueNode struct
- Entire TransactionQueue class

**Where to place**:
```
After: void generateDailySummary(...) { ... }  // End of SalesSummary
Before: class Customer : public User {  // Start of Customer class
```

**Integration into menu**:
Add to main() after the Staff/Customer menu:
```cpp
case 3: {
    user = new InventoryManager();
    user->menu();
    delete user;
    break;
}
```

**Testing**:
- [ ] Code compiles without errors
- [ ] Queue enqueue works
- [ ] Queue dequeue works
- [ ] Display shows all transactions
- [ ] Memory properly freed in destructor

**Impact**: +8 marks (implements DNP data structure)

---

### Step 4: Add Friend Functions
**Time**: 20-30 minutes
**Locations**: 
1. Inside ProductList class declaration
2. After ProductList class definition
**File**: main.cpp

**What to add in ProductList class**:
```cpp
// Add in PRIVATE or PUBLIC section after destructor:
friend bool compareProducts(const Product& a, const Product& b);
friend void logProductOperation(const Product& p, const char* operation);
friend void printProductDetails(const Product& p);
friend double calculateTotalStockValue(ProductList* plist);
```

**What to add after class definition**:
Copy all four friend function implementations

**Testing**:
- [ ] Code compiles without friend errors
- [ ] Each friend function can access Product members
- [ ] compareProducts works for sorting
- [ ] logProductOperation writes to log file
- [ ] printProductDetails displays correctly

**Impact**: +8 marks (implements 4 friend functions)

---

### Step 5: Add Third Derived Class (InventoryManager)
**Time**: 30-40 minutes
**Location**: Before Customer class (around line 1400)
**File**: main.cpp

**What to copy**:
- Entire InventoryManager class from CODE_SNIPPETS_FOR_INTEGRATION.cpp

**Where to place**:
```
After: TransactionQueue declaration and destructor
Before: class Customer : public User {
```

**Integration into main menu**:
Modify main() function - add to the initial menu:
```cpp
cout << "1. Staff Module\n";
cout << "2. Customer Module\n";
cout << "3. Inventory Manager\n";  // ADD THIS
cout << "0. Exit\n";
```

And add case 3:
```cpp
case 3: {
    user = new InventoryManager();
    user->menu();
    delete user;
    break;
}
```

**Create inventory.txt file**:
```
inventorymanager inventory123
```
(Create file if it doesn't exist)

**Testing**:
- [ ] Code compiles without errors
- [ ] InventoryManager appears in main menu
- [ ] Login works correctly
- [ ] All menu options accessible
- [ ] Inherits from User base class correctly
- [ ] Polymorphic menu() override works

**Impact**: +6 marks (3rd derived class requirement)

---

## PHASE 2: ENHANCEMENTS (Do TOMORROW - 2-3 hours)

### Step 6: Add Quick Sort Algorithm
**Time**: 30-40 minutes
**Location**: New method in ProductList class (around line 800)
**File**: main.cpp

**Implementation**:
```cpp
void quickSortByPrice() {
    // Convert linked list to array
    // Call quickSort helper function
    // Convert back to linked list
}

private:
    int partitionByPrice(Product arr[], int low, int high) {
        // Implementation
    }
    
    void quickSortHelper(Product arr[], int low, int high) {
        // Implementation
    }
```

**Add menu option**:
In Staff menu, add:
```cpp
cout << "11. Sort Products by Price (Quick Sort)\n";
case 11: {
    plist.quickSortByPrice();
    // Display results
}
```

**Testing**:
- [ ] Code compiles
- [ ] Quick Sort works on linked list
- [ ] Results are properly sorted
- [ ] Faster than Bubble Sort on large data

**Impact**: +4 marks (multiple sorting algorithms)

---

### Step 7: Add Edit Features
**Time**: 40-50 minutes
**Locations**: Staff menu, Customer menu
**File**: main.cpp

**For Staff - Add to menu()**:
```cpp
cout << "11. Edit Product Name\n";
case 11: {
    int editID = Utils::getPositiveInteger("Enter Product ID: ");
    plist.updateProductName(editID);  // New function
    break;
}
```

**For Customer - Add to menu()**:
```cpp
cout << "5. View Purchase History\n";
cout << "6. Cancel Purchase\n";
case 6: {
    // Implement cancel purchase functionality
    break;
}
```

**New ProductList methods needed**:
```cpp
bool updateProductName(int id) {
    // Similar to updateProductPrice()
}

bool cancelPurchase(int transactionID) {
    // Remove from purchase.txt
    // Update product quantity
}
```

**Testing**:
- [ ] Edit product name works
- [ ] Edit product price works
- [ ] Edit product quantity works
- [ ] All changes persist to files
- [ ] Purchase history display works

**Impact**: +4 marks (edit/update record requirement)

---

## PHASE 3: VERIFICATION & FINAL (Do LAST DAY - 1-2 hours)

### Step 8: Code Cleanup & Comments
**Time**: 30 minutes
**Actions**:
- [ ] Verify each function has proper documentation
- [ ] Check all comments are complete
- [ ] Ensure no unused variables
- [ ] Remove any temporary test code
- [ ] Verify UTF-8 support for Windows is enabled

**Check Completed Functions**:
```cpp
// Verify these have proper doc comments:
void writeLog()
void confirmAction()
void pause()
class ProductList
class Staff
class Customer
class ValidationHelper
// ... etc (all major functions should have comments)
```

---

### Step 9: Verify Line Count
**Time**: 10 minutes
**Action**:
1. Open main.cpp
2. Select all (Ctrl+A)
3. Check status bar for line count
4. Should be 2300+ lines (excluding blank lines and heavy comments)

**If below 2300 lines**:
- Add more descriptive comments
- Add more helper functions
- Expand validation methods

---

### Step 10: Test Complete System
**Time**: 30 minutes
**Testing Checklist**:

#### Compilation
- [ ] main.cpp compiles without errors
- [ ] main.cpp compiles without warnings
- [ ] Executable runs without crashing

#### User Authentication
- [ ] Staff registration works
- [ ] Staff login works
- [ ] Customer registration works
- [ ] Customer login works
- [ ] InventoryManager login works
- [ ] Logout works for all users

#### Product Management
- [ ] Can view 50+ products
- [ ] Add product works
- [ ] Delete product works
- [ ] Update price works
- [ ] Update quantity works
- [ ] Search by ID works
- [ ] Binary search works
- [ ] Bubble sort works
- [ ] Quick sort works

#### Customer Features
- [ ] View products works
- [ ] Search product works
- [ ] Purchase product works
- [ ] View purchase history works
- [ ] Purchase saves to purchase.txt

#### Staff Features
- [ ] Generate sales summary works
- [ ] Highest sales product works
- [ ] Lowest sales product works
- [ ] Average sales works
- [ ] Daily summary works

#### Data Files
- [ ] product.txt has 50+ records
- [ ] sales.txt created and updated
- [ ] purchase.txt created and updated
- [ ] summary.txt created
- [ ] log.txt created and updated

#### Queue Testing
- [ ] Enqueue transaction works
- [ ] Dequeue transaction works
- [ ] Display queue works
- [ ] Empty queue handled correctly

#### Friend Functions
- [ ] compareProducts works
- [ ] logProductOperation works
- [ ] printProductDetails works

---

### Step 11: Final Code Review Checklist

**Requirements Check**:
- [ ] 2300+ lines of code ✓
- [ ] 50+ records loaded ✓
- [ ] 10+ user-defined functions ✓
- [ ] 4 overloaded/overridden functions ✓
- [ ] 2+ constructors ✓
- [ ] 2+ destructors ✓
- [ ] 2 struct types (Product, Node) ✓
- [ ] 2 base classes (User, ?) - Check if need another
- [ ] 3 derived classes (Staff, Customer, InventoryManager) ✓
- [ ] 4 friend functions ✓
- [ ] 2+ dynamic memory ops (new/delete) ✓
- [ ] 5+ .txt files ✓
- [ ] Try-catch blocks (multiple) ✓
- [ ] DNP Data Structure (Linked List + Queue) ✓
- [ ] Sorting Algorithm (Bubble Sort + Quick Sort) ✓
- [ ] Searching Algorithm (Binary Search) ✓

**Code Quality**:
- [ ] No memory leaks
- [ ] Proper error handling
- [ ] Clear variable names
- [ ] Consistent indentation
- [ ] Proper comments
- [ ] Follows project guidelines

---

## PROBLEM-SOLVING TROUBLESHOOTING

### If Code Won't Compile

**Check these common issues**:

1. **Syntax errors in new code**
   - Verify all { } are matched
   - Verify all ; at end of statements
   - Check for typos in function names

2. **Friend function issues**
   - Make sure friend declarations are inside class
   - Function implementations are outside class
   - Check spelling matches exactly

3. **Inheritance issues**
   - InventoryManager must have `: public User`
   - Must implement virtual menu() function
   - Destructors must be virtual if using polymorphism

4. **Template/STL errors** (if you used any)
   - Remember: NO #include <algorithm>
   - NO #include <vector>
   - NO std::sort(), std::find()
   - Use manual implementations only

### If Certain Features Don't Work

1. **Binary search not finding products**
   - Check that product IDs are sorted
   - Verify you're searching correct array
   - Test with known product IDs

2. **Queue operations failing**
   - Verify memory allocation (new) succeeded
   - Check enqueue before dequeue
   - Test with simple integer values first

3. **Friend functions can't access data**
   - Verify friend declaration inside class
   - Check that friend is declaring correct class/function
   - Ensure it's not in private section

4. **Files not saving**
   - Check file permissions
   - Verify correct file path (use relative paths)
   - Check for file I/O exceptions

---

## ESTIMATED TIMELINE

**Phase 1 (Today)**: 2-3 hours
- Add 50+ records: 5 min
- Binary search: 40 min
- Transaction queue: 50 min
- Friend functions: 30 min
- 3rd derived class: 40 min

**Phase 2 (Tomorrow)**: 2-3 hours
- Quick sort: 40 min
- Edit features: 50 min
- Code cleanup: 30 min
- Initial testing: 20 min

**Phase 3 (Final day)**: 1-2 hours
- Line count verification: 10 min
- Comprehensive testing: 30 min
- Final code review: 20 min
- Documentation update: 30 min

**Total Effort**: 5-8 hours spread over 3 days

**Expected Score**: 70+ out of 80 marks

---

## SUCCESS CRITERIA

You'll know you're done when:

✅ All 50+ products load into system
✅ Binary search finds products correctly
✅ Queue enqueue/dequeue works
✅ All friend functions accessible
✅ Inventory manager menu appears
✅ Staff, Customer, Inventory login works
✅ Purchase history displays correctly
✅ Sales reports generate correctly
✅ No compilation errors
✅ No memory leaks
✅ All 5 text files created
✅ Audit log tracks all actions
✅ Code is 2300+ lines

---

## FINAL SUBMISSION PREPARATION

### Before submitting, ensure:

1. **Code Quality**
   - [ ] No compilation errors
   - [ ] No runtime errors
   - [ ] Proper documentation
   - [ ] Clean code structure

2. **Documentation**
   - [ ] README.md exists and is clear
   - [ ] CODE_ANALYSIS_REPORT.md created
   - [ ] Comments in code are comprehensive
   - [ ] All algorithms documented

3. **Files**
   - [ ] main.cpp complete and tested
   - [ ] All 5+ .txt files exist
   - [ ] product.txt has 50+ records
   - [ ] GitHub repository set up
   - [ ] Lecturer added as collaborator

4. **Testing**
   - [ ] All features tested manually
   - [ ] Edge cases handled
   - [ ] Error messages display correctly
   - [ ] Files save and load properly

---

**Good luck with your project!**
**Target: 70+ marks out of 80**
