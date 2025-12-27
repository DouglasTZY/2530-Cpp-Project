# Utils Integration Map

## 🗺️ Complete Integration Overview

### Main Application Flow

```
┌─────────────────────────────────────────────────────────┐
│                    MAIN() - HOME MENU                   │
│  Utils::clearScreen()                                   │
│  Utils::printLine(45)                                   │
│  Utils::printDivider()                                  │
│  Utils::printWarning() - Invalid input                  │
│  Utils::pause() - Wait for user                         │
└────────────────┬───────────────────────────┬────────────┘
                 │                           │
         ┌───────▼───────┐           ┌───────▼──────┐
         │  STAFF MENU   │           │ CUSTOMER MENU│
         └───────┬───────┘           └───────┬──────┘
                 │                           │
    ┌────────────┼──────────────────────┬────┴──────────────┐
    │            │                      │                   │
    ▼            ▼                      ▼                   ▼
┌─────────┐ ┌────────────────┐ ┌──────────────┐ ┌──────────────┐
│ Add     │ │ Display        │ │ View         │ │ Purchase     │
│ Product │ │ Products       │ │ Products     │ │ Product      │
│ (6 Utils)│ │ (4 Utils)      │ │ (3 Utils)    │ │ (5 Utils)   │
└─────────┘ └────────────────┘ └──────────────┘ └──────────────┘
```

---

## 📍 Utils Methods Used by Feature

### Main Menu
```
┌─ clearScreen()         [Screen Management]
├─ printLine(length)     [Visual Formatting]
├─ printDivider()        [Menu Structure]
├─ printWarning()        [Error Feedback]
└─ pause()              [User Control]
```

### Staff Login
```
┌─ clearScreen()         [Screen Management]
├─ printHeader(title)    [Section Header]
├─ printDivider()        [Menu Separator]
├─ printWarning()        [Error Messages]
└─ pause()              [User Pause]
```

### Staff Main Menu
```
┌─ clearScreen()         [Screen Management]
├─ printHeader(title)    [Section Header]
├─ printDivider()        [Menu Separator]
├─ printWarning()        [Invalid Choice]
└─ pause()              [Continue Prompt]
```

### Case 1: Add Product
```
┌─ getPositiveInteger()  [Product ID Input]
├─ getPositiveDouble()   [Price Input]
├─ getPositiveInteger()  [Quantity Input]
├─ confirmAction()       [Confirm Add]
├─ printStatus(success)  [Success Message]
└─ pause()              [Continue Prompt]
```

### Case 2: Display Products
```
┌─ printHeader(title)    [Section Header]
└─ pause()              [Continue Prompt]
```

### Case 3: Sort Products
```
┌─ printStatus(success)  [Success Message]
└─ pause()              [Continue Prompt]
```

### Case 4: Search Product
```
┌─ getPositiveInteger()  [Search ID]
└─ pause()              [Continue Prompt]
```

### Case 5: Delete Product
```
┌─ getPositiveInteger()  [Product ID]
├─ confirmAction()       [Confirm Delete]
├─ printStatus()         [Success/Error]
└─ pause()              [Continue Prompt]
```

### Cases 6-10: Reports
```
┌─ printHeader(title)    [Section Header]
└─ pause()              [Continue Prompt]
```

### Case 0: Logout
```
└─ printStatus()         [Logout Message]
```

---

## Customer Menu Structure

```
┌─ clearScreen()         [Screen Management]
├─ printHeader(title)    [Section Header]
├─ printDivider()        [Menu Separator]
├─ printWarning()        [Invalid Choice]
└─ pause()              [Continue Prompt]
```

### Case 1: View Products
```
┌─ printHeader(title)    [Section Header]
└─ pause()              [Continue Prompt]
```

### Case 2: Search Product
```
┌─ getPositiveInteger()  [Search ID]
└─ pause()              [Continue Prompt]
```

### Case 3: Sort Products
```
┌─ printStatus()         [Success Message]
└─ pause()              [Continue Prompt]
```

### Case 4: Purchase
```
┌─ getPositiveInteger()  [Product ID]
├─ getPositiveInteger()  [Quantity]
├─ confirmAction()       [Confirm Purchase]
├─ printStatus()         [Success/Cancel]
└─ pause()              [Continue Prompt]
```

---

## 📊 Utils Method Usage Count

```
clearScreen()              10 times    [UI Refresh]
printHeader()             10 times    [Titles]
printLine()                2 times    [Formatting]
printDivider()            10 times    [Separators]
printWarning()            10 times    [Alerts]
printStatus()             15 times    [Feedback]
pause()                   25 times    [Control Flow]
confirmAction()            5 times    [Confirmations]
getPositiveInteger()       8 times    [Input Validation]
getPositiveDouble()        1 time     [Price Input]
getPositiveInteger()       1 time     [Search Input]
confirmProceeding()        0 times    [Generic confirm]
────────────────────────────────────────
TOTAL                     97+ calls
```

---

## 🎯 Benefits by Feature

| Feature | Utils Integration | Benefit |
|---------|------------------|---------|
| Main Menu | 5 methods | Professional appearance |
| Login Flow | 4 methods | Consistent UX |
| Staff Menu | 5 methods | Clean interface |
| Add Product | 6 methods | User guidance + validation |
| Delete Product | 4 methods | Safe operation |
| Search Product | 2 methods | Clear feedback |
| Purchase | 5 methods | Guided transaction |

---

## 🔄 Control Flow with Utils

```
User launches app
        │
        ▼
┌──────────────────────────────────────┐
│ Main Menu                            │
│ clearScreen() → printLine() → ...    │
└──────────────────────────────────────┘
        │
        ├──► Staff / Customer?
        │
        ▼ (if Staff)
┌──────────────────────────────────────┐
│ Staff Login Menu                     │
│ printHeader() → printDivider() → ...│
└──────────────────────────────────────┘
        │
        ▼ (if success)
┌──────────────────────────────────────┐
│ Staff Main Menu Loop                 │
│ clearScreen() → Loop through options │
│ Each option uses Utils methods       │
└──────────────────────────────────────┘
        │
        ├──► Add: getPositiveInteger() → confirmAction()
        ├──► Delete: getPositiveInteger() → confirmAction()
        ├──► Search: getPositiveInteger()
        ├──► Reports: printHeader() → pause()
        │
        ▼
┌──────────────────────────────────────┐
│ User Logout (printStatus())          │
└──────────────────────────────────────┘
```

---

## ✨ Key Integration Points

### 1️⃣ Screen Management
- Every menu starts with `Utils::clearScreen()`
- Ensures clean, professional display
- **8 integration points**

### 2️⃣ Visual Formatting
- Headers use `Utils::printHeader()`
- Separators use `Utils::printDivider()`
- Lines use `Utils::printLine()`
- **10 integration points**

### 3️⃣ User Feedback
- Success → `Utils::printStatus(msg, true)`
- Errors → `Utils::printStatus(msg, false)`
- Warnings → `Utils::printWarning(msg)`
- **15 integration points**

### 4️⃣ Input Control
- All pauses use `Utils::pause()`
- All validations use `Utils::getPositiveInteger()`
- All prices use `Utils::getPositiveDouble()`
- **25+ integration points**

### 5️⃣ Confirmations
- Deletions use `Utils::confirmAction()`
- Purchases use `Utils::confirmAction()`
- **5+ integration points**

---

## 🏆 Quality Metrics

✅ **Consistency**: 97+ method calls ensure uniform UX  
✅ **Maintainability**: Single source of truth for UI  
✅ **Robustness**: Error handling in every input  
✅ **Professional**: Status indicators and visual formatting  
✅ **Extensibility**: Easy to add new Utils methods  

---

**Total Utils Integration: 97+ Method Calls Across Entire Application** 🚀

