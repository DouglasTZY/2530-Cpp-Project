# Audit Log System - Quick Reference Guide

## 📚 File Navigation

| File | Purpose | Recommended Reading Order |
|------|---------|-----------|
| **main.cpp** | Main program (log integrated) | 3 |
| **log.txt** | Real-time log recording | 4 |
| **AUDIT_LOG_README.md** | Complete documentation ⭐ | **1** |
| **AUDIT_LOG_EXAMPLES.md** | Usage examples | 2 |
| **AUDIT_LOG_SUMMARY.md** | Project summary | 5 |

## 🔑 Core Log Functions

### Basic Log
```cpp
writeLog(action, username)
// Example: writeLog("STAFF LOGIN", "john");
```

### Log with ID
```cpp
writeLogWithID(action, id, username)
// Example: writeLogWithID("DELETE PRODUCT", 5, "john");
```

### Log with Product Information
```cpp
writeLogWithProduct(action, productName, price, qty, username)
// Example: writeLogWithProduct("ADD PRODUCT", "Pen", 2.50, 100, "john");
```

### Purchase Log
```cpp
writeLogPurchase(customerName, productName, qty, totalPrice, username)
// Example: writeLogPurchase("jane", "Pen", 10, 25.00, "jane");
```

## 📝 Log Format

```
[YYYY-MM-DD HH:MM:SS] [Username] Action Details
```

### Examples
```
[2025-12-27 14:30:45] [john] STAFF LOGIN
[2025-12-27 14:31:12] [john] ADD PRODUCT - Product: Notebook (Price: RM5.99, Qty: 100)
[2025-12-27 14:42:30] [jane] PURCHASE - Customer: jane | Product: Pen | Qty: 10 | Total: RM9.90
```

## ✅ Logged Operations (13+)

| Category | Operation | Log Function |
|----------|-----------|--------------|
| **Authentication** | Staff login success | writeLog() |
| | Staff login failure | writeLog() |
| | Staff registration | writeLog() |
| | Customer login success | writeLog() |
| | Customer login failure | writeLog() |
| | Customer registration | writeLog() |
| **Products** | Add product | writeLogWithProduct() |
| | Delete product | writeLogWithID() |
| | Search product | writeLogWithID() |
| | Display products | writeLog() |
| | Sort products | writeLog() |
| **Sales** | Purchase product | writeLogPurchase() |
| | Generate report | writeLog() |

## 🚀 Usage Scenarios

### Scenario 1: Staff Adding New Product
```cpp
// Code location: Staff::menu() - case 1
plist.addProduct(p);
plist.saveToFile();
writeLogWithProduct("ADD PRODUCT", p.name, p.price, p.quantity, username);
// Log result: [2025-12-27 14:31:12] [john] ADD PRODUCT - Product: Pen (Price: RM2.50, Qty: 200)
```

### Scenario 2: Customer Purchasing Product
```cpp
// Code location: ProductList::purchaseProduct()
writeLogPurchase(customerName, cur->data.name, quantity, cur->data.price * quantity, customerName);
// Log result: [2025-12-27 14:42:30] [jane] PURCHASE - Customer: jane | Product: Pen | Qty: 10 | Total: RM25.00
```

### Scenario 3: Login Failure
```cpp
// Code location: Staff::login() or Customer::login()
writeLog("STAFF LOGIN FAILED", userName);
// Log result: [2025-12-27 15:10:00] [tom] STAFF LOGIN FAILED
```

## 💻 View Log Commands

### Windows (PowerShell)
```powershell
# View all logs
Get-Content log.txt

# View last 10 entries
Get-Content log.txt -Tail 10

# Search for specific user
Select-String "jane" log.txt

# Search for specific operation
Select-String "PURCHASE" log.txt

# Count operations
(Select-String "PURCHASE" log.txt).Count
```

### Linux/Mac
```bash
# View all logs
cat log.txt

# View last 10 entries
tail -10 log.txt

# Search for specific user
grep "jane" log.txt

# Search for specific operation
grep "PURCHASE" log.txt

# Count operations
grep -c "PURCHASE" log.txt
```

## 🔍 Log Analysis Tips

### 1. Count Operations by User
```bash
grep "\[jane\]" log.txt | wc -l    # Count jane's operations
```

### 2. View Operations at Specific Time
```bash
grep "2025-12-27 14:" log.txt      # View operations at 14:00
```

### 3. View Login Failures
```bash
grep "LOGIN FAILED" log.txt
```

### 4. View All Purchases
```bash
grep "PURCHASE" log.txt
```

### 5. View Data Modification Operations
```bash
grep -E "ADD|DELETE|PURCHASE" log.txt
```

## ⚙️ Configuration Guide

### Timestamp Format
**Current**: `%Y-%m-%d %H:%M:%S` (precision to seconds)

Location to modify:
```cpp
// main.cpp line 16
strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
```

### Log File Location
**Current**: `log.txt` (program running directory)

How to modify:
```cpp
ofstream log("log.txt", ios::app);  // Change to desired path
```

### Default Username
**Current**: "unknown"

How to modify:
```cpp
void writeLog(const char* action, const char* username = "unknown")
//                                                           ^^^^^^^^^ Change here
```

## 🐛 Common Questions

### Q: Why don't I see logs?
**A**: 
1. Check if log.txt is in the program running directory
2. Ensure write operations are being executed
3. Wait for program to finish running before checking

### Q: Why is the username "unknown"?
**A**: 
1. Check if username parameter is being passed correctly
2. Username should be assigned after login

### Q: Log information is incomplete?
**A**:
1. Different operation types use different log functions
2. Some operations may not have logging implemented
3. Check log function calls in main.cpp

### Q: Can I add more logs?
**A**: Yes, you can call corresponding log functions before or after any operation

## 📊 Log Statistics Example

```
Total operations: 16
├─ Authentication operations: 6 (login/registration)
├─ Product operations: 5 (add/delete/view/sort)
└─ Sales operations: 3 (purchase+report)

User operation distribution:
├─ john: 5 operations (staff)
├─ jane: 6 operations (customer)
└─ tom: 3 operations (staff)

Operation type distribution:
├─ LOGIN: 4 times
├─ REGISTERED: 2 times
├─ ADD PRODUCT: 1 time
├─ PURCHASE: 2 times
└─ Others: 7 times
```

## 🔐 Security Recommendations

1. **Regularly backup logs**
   ```bash
   cp log.txt log.txt.backup-$(date +%Y%m%d)
   ```

2. **Regularly clean or archive**
   ```bash
   # Save old logs then clear
   mv log.txt log.$(date +%Y%m%d).txt
   ```

3. **Protect log file permissions** (Linux)
   ```bash
   chmod 600 log.txt
   ```

4. **Regularly review logs**
   - Search for unusual logins
   - Check large transactions
   - Monitor administrator operations

## 📈 Performance Monitoring

### Calculate Average Response Time
```bash
# Extract time difference between two log entries
```

### Check Peak Hours
```bash
# Count operations per hour
grep "14:" log.txt | wc -l  # Count 14:00 operations
```

### User Activity Analysis
```bash
# Count operations per user
grep -o "\[[^]]*\]" log.txt | sort | uniq -c
```

## 🎯 Best Practices

✅ **Log all critical operations** - Enables tracking and auditing

✅ **Include timestamps** - Enables time series analysis

✅ **Record user information** - Enables accountability tracking

✅ **Record operation details** - Enables troubleshooting

✅ **Regularly backup logs** - Prevents data loss

✅ **Regularly review logs** - Identifies anomalies and improvements

## 📞 More Resources

- Complete documentation: See **AUDIT_LOG_README.md**
- Detailed examples: See **AUDIT_LOG_EXAMPLES.md**
- Project summary: See **AUDIT_LOG_SUMMARY.md**
- Source code: See **main.cpp** (lines 8-88 for log functions)

---

**Quick Links**:
- 🔍 View function source: main.cpp (L8-L88)
- 📝 View log calls: main.cpp (grep "writeLog")
- 📊 Analyze log data: log.txt
- 📚 Full documentation: AUDIT_LOG_README.md

