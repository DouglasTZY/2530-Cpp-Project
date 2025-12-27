# Audit Log System - Implementation Documentation

## Overview
This project includes a complete audit log system that records all critical operations. Each operation is logged to the `log.txt` file, including timestamps, usernames, and operation details.

## 📋 Logged Critical Operations

### Authentication Operations
- ✅ **STAFF LOGIN** - Successful staff login
- ✅ **STAFF LOGIN FAILED** - Failed staff login
- ✅ **STAFF REGISTERED** - Staff registration
- ✅ **CUSTOMER LOGIN** - Successful customer login
- ✅ **CUSTOMER LOGIN FAILED** - Failed customer login
- ✅ **CUSTOMER REGISTERED** - Customer registration

### Product Management Operations
- ✅ **ADD PRODUCT** - Add new product (includes: product name, price, quantity)
- ✅ **DELETE PRODUCT** - Delete product (includes: product ID)
- ✅ **SEARCH PRODUCT** - Search product (includes: product ID)
- ✅ **DISPLAY PRODUCTS** - Display all products
- ✅ **SORT PRODUCTS BY PRICE** - Sort products by price

### Sales Operations
- ✅ **PURCHASE** - Complete purchase (includes: customer name, product name, quantity, total price)
- ✅ **GENERATE SALES SUMMARY** - Generate sales report

## 📝 Log Format

```
[YYYY-MM-DD HH:MM:SS] [Username] Action Details
```

### Example Log Entries

```
[2025-12-27 14:30:45] [john] STAFF LOGIN
[2025-12-27 14:31:12] [john] ADD PRODUCT - Product: Notebook (Price: RM5.99, Qty: 100)
[2025-12-27 14:35:28] [john] DELETE PRODUCT (ID: 5)
[2025-12-27 14:40:15] [jane] CUSTOMER LOGIN
[2025-12-27 14:41:00] [jane] VIEW PRODUCTS
[2025-12-27 14:41:45] [jane] SEARCH PRODUCT (ID: 3)
[2025-12-27 14:42:30] [jane] PURCHASE - Customer: jane | Product: Pen | Qty: 10 | Total: RM9.90
[2025-12-27 14:43:10] [john] GENERATE SALES SUMMARY
```

## 🔧 Implementation Details

### Logging Functions

#### 1. `writeLog(action, username)`
- **Purpose**: Log basic operations
- **Parameters**:
  - `action`: Operation description
  - `username`: User performing the operation (default: "unknown")
- **Example**: `writeLog("STAFF LOGIN", userName);`

#### 2. `writeLogWithID(action, id, username)`
- **Purpose**: Log operations involving product ID
- **Parameters**:
  - `action`: Operation description
  - `id`: Product ID
  - `username`: User performing the operation
- **Example**: `writeLogWithID("DELETE PRODUCT", deleteID, username);`

#### 3. `writeLogWithProduct(action, productName, price, qty, username)`
- **Purpose**: Log operations with complete product information
- **Parameters**:
  - `action`: Operation description
  - `productName`: Product name
  - `price`: Product price
  - `qty`: Product quantity
  - `username`: User performing the operation
- **Example**: `writeLogWithProduct("ADD PRODUCT", p.name, p.price, p.quantity, username);`

#### 4. `writeLogPurchase(customerName, productName, qty, totalPrice, username)`
- **Purpose**: Log purchase transactions
- **Parameters**:
  - `customerName`: Customer name
  - `productName`: Product name
  - `qty`: Purchase quantity
  - `totalPrice`: Total price
  - `username`: User performing the operation
- **Example**: `writeLogPurchase(customerName, productName, qty, total, username);`

## 📂 File Structure

```
Tri 2530 C++ Project/
├── main.cpp           # Main program file (audit log integrated)
├── log.txt            # Audit log file
├── product.txt        # Product data
├── staff.txt          # Staff accounts
├── customer.txt       # Customer accounts
├── purchase.txt       # Purchase history
├── sales.txt          # Sales records
├── summary.txt        # Sales summary
└── README.md          # Project documentation
```

## 🚀 Usage

### Compilation and Execution
```bash
# Compile
g++ main.cpp -o stationery_shop

# Run
./stationery_shop
```

### View Logs
Log file is automatically created and appended. You can view it with any text editor or command line:

```bash
# Windows
type log.txt

# Linux/Mac
cat log.txt
```

## 💡 Features

✨ **Real-time Recording** - Every operation is logged immediately

✨ **Timestamps** - Accurate to the second using system time

✨ **User Tracking** - Records which user performed each operation

✨ **Detailed Information** - Includes important parameters for each operation

✨ **Error Recording** - Logs failed login attempts and other errors

✨ **Audit Transparency** - Complete operation history for system management

## 📊 Audit Log Uses

1. **Security Audit** - Track who did what
2. **Troubleshooting** - Find when and why problems occurred
3. **Compliance** - Meet system operation record requirements
4. **Performance Analysis** - Understand system usage patterns
5. **Inventory Control** - Track product additions and deletions

## 🔐 Security Considerations

- Log files contain usernames and operation details
- Recommend regular backup of log files
- Consider restricting access permissions to log files in production
- May consider adding log encryption or signing for enhanced security

## ✅ Test Coverage

Following operations have integrated audit logging:

| Operation Category | Number of Operations | Status |
|-------------------|---------------------|--------|
| Authentication    | 6                   | ✅     |
| Product Management| 5                   | ✅     |
| Sales Operations  | 2                   | ✅     |
| **Total**        | **13+**             | ✅     |

## 📈 Code Statistics

- Logging system code: ~90 lines
- Logging call integration: ~110 lines
- **Total new code**: ~200 lines

## 🎯 Project Goals Achieved

✅ Added complete audit log system
✅ All critical operations are logged
✅ Timestamps and user information are complete
✅ Log format is clear and readable
✅ Code compiles without errors
✅ System has realistic feel and full traceability

---

**Version**: 1.0
**Last Updated**: 2025-12-27
**Author**: AI Copilot Assistant
