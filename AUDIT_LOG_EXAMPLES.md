# Audit Log System - Usage Examples

## Example Scenario: Daily Operation Logs

The following is a complete usage scenario and expected log output:

### Scenario: Daily transactions of staff and customers

```
=== Time: 2025-12-27 09:00:00 ===

[Action] Staff John logs in to system
[Expected Log]
[2025-12-27 09:00:15] [john] STAFF LOGIN

[Action] John adds new product: Pencil, price RM2.50, quantity 200
[Expected Log]
[2025-12-27 09:05:30] [john] ADD PRODUCT - Product: Pencil (Price: RM2.50, Qty: 200)

[Action] John searches for product with ID 5
[Expected Log]
[2025-12-27 09:10:45] [john] SEARCH PRODUCT (ID: 5)

[Action] John sorts products by price
[Expected Log]
[2025-12-27 09:15:20] [john] SORT PRODUCTS BY PRICE

[Action] John displays all products
[Expected Log]
[2025-12-27 09:20:10] [john] DISPLAY PRODUCTS

=== Time: 2025-12-27 10:00:00 ===

[Action] Customer Jane registers account
[Expected Log]
[2025-12-27 10:00:30] [jane] CUSTOMER REGISTERED

[Action] Jane logs in to system
[Expected Log]
[2025-12-27 10:01:00] [jane] CUSTOMER LOGIN

[Action] Jane views product list
[Expected Log]
[2025-12-27 10:02:15] [jane] VIEW PRODUCTS

[Action] Jane searches for product with ID 2
[Expected Log]
[2025-12-27 10:03:45] [jane] SEARCH PRODUCT (ID: 2)

[Action] Jane purchases product ID 2 (Pen), quantity 10, total RM15.00
[Expected Log]
[2025-12-27 10:05:00] [jane] PURCHASE - Customer: jane | Product: Pen | Qty: 10 | Total: RM15.00

[Action] Jane sorts products by price
[Expected Log]
[2025-12-27 10:06:30] [jane] SORT PRODUCTS BY PRICE

[Action] Jane purchases product ID 3 (Notebook), quantity 5, total RM24.95
[Expected Log]
[2025-12-27 10:07:45] [jane] PURCHASE - Customer: jane | Product: Notebook | Qty: 5 | Total: RM24.95

=== Time: 2025-12-27 11:00:00 ===

[Action] Staff Tom attempts to log in but password is incorrect
[Expected Log]
[2025-12-27 11:00:15] [tom] STAFF LOGIN FAILED

[Action] Staff Tom successfully logs in
[Expected Log]
[2025-12-27 11:01:00] [tom] STAFF LOGIN

[Action] Tom deletes product with ID 10
[Expected Log]
[2025-12-27 11:05:45] [tom] DELETE PRODUCT (ID: 10)

[Action] Tom generates sales report
[Expected Log]
[2025-12-27 11:10:30] [tom] GENERATE SALES SUMMARY
```

## Complete Log File Example

```
[2025-12-27 09:00:15] [john] STAFF LOGIN
[2025-12-27 09:05:30] [john] ADD PRODUCT - Product: Pencil (Price: RM2.50, Qty: 200)
[2025-12-27 09:10:45] [john] SEARCH PRODUCT (ID: 5)
[2025-12-27 09:15:20] [john] SORT PRODUCTS BY PRICE
[2025-12-27 09:20:10] [john] DISPLAY PRODUCTS
[2025-12-27 10:00:30] [jane] CUSTOMER REGISTERED
[2025-12-27 10:01:00] [jane] CUSTOMER LOGIN
[2025-12-27 10:02:15] [jane] VIEW PRODUCTS
[2025-12-27 10:03:45] [jane] SEARCH PRODUCT (ID: 2)
[2025-12-27 10:05:00] [jane] PURCHASE - Customer: jane | Product: Pen | Qty: 10 | Total: RM15.00
[2025-12-27 10:06:30] [jane] SORT PRODUCTS BY PRICE
[2025-12-27 10:07:45] [jane] PURCHASE - Customer: jane | Product: Notebook | Qty: 5 | Total: RM24.95
[2025-12-27 11:00:15] [tom] STAFF LOGIN FAILED
[2025-12-27 11:01:00] [tom] STAFF LOGIN
[2025-12-27 11:05:45] [tom] DELETE PRODUCT (ID: 10)
[2025-12-27 11:10:30] [tom] GENERATE SALES SUMMARY
```

## Log Analysis Examples

### 1. User Activity Tracking
```
User jane's activities:
- Registration time: 2025-12-27 10:00:30
- First login: 2025-12-27 10:01:00
- View count: 2 times (VIEW PRODUCTS, SEARCH)
- Purchase count: 2 times (15.00 + 24.95 = RM40.00)
- Last activity: 2025-12-27 10:07:45
```

### 2. Product Operation Audit
```
Product management audit:
- Add product: 1 time (pencil)
- Delete product: 1 time (ID: 10)
- Search operations: 2 times (ID: 5, ID: 2)
- Sort operations: 2 times
```

### 3. Login Failure Alert
```
Failed login attempts:
- User: tom
- Time: 2025-12-27 11:00:15
- Status: FAILED
- Follow-up: User eventually logs in successfully at 11:01:00
```

### 4. Sales Analysis
```
Sales statistics:
- Purchase time range: 2025-12-27 10:05:00 to 10:07:45
- Purchasing customer: jane
- Number of transactions: 2
- Total sales: RM40.00
- Sales products: Pen (10 units), Notebook (5 units)
```

## Real-time Log Query Commands

### Windows PowerShell
```powershell
# View last 10 logs
Get-Content log.txt -Tail 10

# Search for specific user's activity
Select-String "jane" log.txt

# Search for specific operation type
Select-String "PURCHASE" log.txt

# Search for login failures
Select-String "LOGIN FAILED" log.txt
```

### Linux/Mac
```bash
# View last 10 logs
tail -10 log.txt

# Search for specific user's activity
grep "jane" log.txt

# Search for specific operation type
grep "PURCHASE" log.txt

# Search for login failures
grep "LOGIN FAILED" log.txt

# Count operations by specific user
grep "john" log.txt | wc -l
```

## Log Statistics Examples

### Operations count per user
```
john: 5 operation records
  - 1 login
  - 1 add product
  - 2 search and sort
  - 1 display products

jane: 5 operation records
  - 1 registration
  - 1 login
  - 2 view/search
  - 2 purchases

tom: 3 operation records
  - 1 login failed
  - 1 login succeeded
  - 1 delete product
  - 1 generate report
```

### Operation type distribution
```
Authentication operations: 6 (2 FAILED, 2 LOGIN, 2 REGISTERED)
Product operations: 6 (1 ADD, 1 DELETE, 2 SEARCH, 2 SORT)
Sales operations: 2 (2 PURCHASE)
Administration operations: 2 (1 DISPLAY, 1 GENERATE)
Total: 16 operation records
```

## Security Applications

### 1. Detect Abnormal Activity
```
Abnormal check points:
- Multiple login failures in short time → Possible brute force attack
- Admin operations outside working hours → Review necessity
- Large number of delete operations by single user → Data integrity risk
```

### 2. Audit Trail
```
Tracking chain:
User action → Log recording → Audit check → Compliance verification
```

### 3. Failure Recovery
```
Log-based recovery steps:
1. View the timestamp of the last successful operation
2. Identify all transactions before failure
3. Verify data consistency
4. Recover to the last consistent state
```

## Performance Monitoring

### Response Time Analysis
```
Using log timestamps, you can calculate:
- Average interval time between user operations
- System busy time periods
- User concurrency during peak hours
```

### Usage Pattern Analysis
```
Statistical data:
- Most frequent operation type
- Most active user
- Most accessed product
- Best time to purchase
```

---

**Note**: This is a complete audit log system example. Actual log content will be generated based on real user operations.
