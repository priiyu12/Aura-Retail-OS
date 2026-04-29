# Zephyrus Retail OS

![Language](https://img.shields.io/badge/language-C++-blue)
![Frontend](https://img.shields.io/badge/frontend-React%20%2B%20Tailwind-4f46e5)
![Stage](https://img.shields.io/badge/stage-Final%20Project-success)
![OOP](https://img.shields.io/badge/focus-OOP%20%26%20Design%20Patterns-1d4ed8)

A modular smart-city retail kiosk platform built in **C++** using **Object-Oriented Programming principles** and multiple **design patterns**. The system supports multiple deployment environments, adaptive pricing, admin and user workflows, bundle purchases, event-driven monitoring, failure recovery, and persistence.

---

## Project Overview

**Zephyrus Retail OS** is designed as an autonomous and extensible kiosk platform for different smart-city environments:

- **Hospitals** dispensing prescription medication and hygiene essentials
- **Metro stations** selling daily-use and travel products
- **University campuses** selling electronics and stationery
- **Disaster relief zones** distributing essential emergency supplies

Although these kiosk environments share a common platform, they differ in:
- product categories
- pricing behavior
- purchase restrictions
- operational priorities
- emergency handling rules

This project was developed as part of the **IT620 Object Oriented Programming Project**.

---

## Final System Highlights

The final system supports:

- **User Mode** and **Admin Mode**
- environment-specific kiosk setup
- product and bundle purchase
- dynamic pricing strategies
- policy-based validation
- hardware failure simulation
- recovery chain handling
- event-driven alerts
- transaction history
- system mode switching
- kiosk environment switching without rerun
- persistence of inventory, transaction, and config data
- minimal clean frontend for presentation support

---

## Supported Kiosk Environments

### 1. Hospital
- medical essentials and hygiene products
- restricted handling for prescription items
- quantity limits for sensitive products

### 2. Metro
- fast daily-use and travel products
- quick-service flow
- lightweight purchase limits

### 3. University
- electronics and stationery
- student-friendly discount pricing
- study bundle support

### 4. Disaster Relief
- essential items only
- emergency pricing
- strict emergency purchase limits

---

## Project Architecture Overview

The system follows a layered modular architecture for scalability, maintainability, and low coupling.

### 1. Presentation Layer
- `KioskInterface`
- Console Simulation
- Minimal Frontend

### 2. Core Coordination Layer
- `KioskCoreSystem`
- `CentralRegistry`
- `DecisionMediator`

### 3. Behavior Layer
- Factory Module
- State Module
- Pricing Module

### 4. Business Layer
- Inventory Module
- Transaction Module
- Payment Module

### 5. System Services Layer
- Hardware & Recovery Module
- Event & Monitoring Module
- Persistence Module

---

## OOP Concepts Used

The project strongly reflects the following OOP concepts:

- **Encapsulation**  
  Product, transaction, inventory, and state-related data are kept inside dedicated classes and exposed through controlled methods.

- **Abstraction**  
  Interfaces and base classes such as `PricingStrategy`, `KioskState`, `KioskFactory`, `Command`, and `EventListener` hide implementation complexity.

- **Inheritance**  
  Multiple specialized classes extend shared abstractions, such as pricing strategies, kiosk states, factories, and events.

- **Polymorphism**  
  Different pricing, state, and factory implementations are used dynamically through base-type references.

- **Low Coupling**  
  Subsystems communicate through interfaces, mediator-based decisions, command execution, and an event bus instead of direct dependencies.

- **Modularity**  
  Each subsystem is implemented separately so the system remains extendable and easier to maintain.

---

## Implemented Design Patterns

### 1. Facade Pattern
**Where implemented:** `KioskInterface`  
**How it works:**  
Provides a single entry point for operations such as purchasing items, purchasing bundles, restocking inventory, diagnostics, and viewing transaction history.

### 2. Strategy Pattern
**Where implemented:** `PricingStrategy`, `StandardPricing`, `DiscountPricing`, `EmergencyPricing`, `PricingSystem`  
**How it works:**  
Allows different pricing behaviors to be selected depending on kiosk environment and operating conditions.

### 3. Observer Pattern
**Where implemented:** `EventBus`, `Event`, `EventListener`, `CityMonitoringSystem`, event classes  
**How it works:**  
System events such as low stock, policy violation, and hardware failure are published and sent to subscribed listeners automatically.

### 4. Command Pattern
**Where implemented:** `Command`, `PurchaseCommand`, `RefundCommand`, `RestockCommand`  
**How it works:**  
Encapsulates operational actions as command objects for modular execution.

### 5. State Pattern
**Where implemented:** `KioskState`, `ActiveState`, `PowerSavingState`, `MaintenanceState`, `EmergencyLockdownState`  
**How it works:**  
The kiosk behaves differently depending on the current operational mode.

### 6. Abstract Factory Pattern
**Where implemented:** `KioskFactory`, `HospitalKioskFactory`, `MetroKioskFactory`, `UniversityKioskFactory`, `DisasterReliefKioskFactory`  
**How it works:**  
Creates environment-specific inventory setup and pricing strategy without modifying the core logic.

### 7. Chain of Responsibility Pattern
**Where implemented:** `FailureHandler`, `RetryHandler`, `RecalibrationHandler`, `TechnicianAlertHandler`  
**How it works:**  
Passes hardware failure through a sequence of handlers until the issue is handled or escalated.

### 8. Memento Pattern
**Where implemented:** `TransactionSnapshot`, `TransactionCaretaker`  
**How it works:**  
Stores important state information before risky operations to support safe recovery logic.

### 9. Singleton Pattern
**Where implemented:** `CentralRegistry`  
**How it works:**  
Maintains one shared global source of truth for current kiosk type and system mode.

### 10. Mediator Pattern
**Where implemented:** `DecisionMediator`  
**How it works:**  
Coordinates state-based operational decisions without tightly coupling all subsystems together.

---

## Major Functional Modules

### Inventory Module
- `Product`
- `Bundle`
- `InventorySystem`
- `InventoryPolicy`

Handles:
- stock tracking
- reserved stock
- bundle definitions
- environment-specific rules
- low-stock detection

### Pricing Module
- `PricingStrategy`
- `StandardPricing`
- `DiscountPricing`
- `EmergencyPricing`
- `PricingSystem`

Handles:
- dynamic pricing strategy selection
- pricing explanation
- environment-sensitive price behavior

### Transaction Module
- `Transaction`
- `TransactionManager`
- `PurchaseCommand`
- `RefundCommand`
- `RestockCommand`
- `TransactionSnapshot`
- `TransactionCaretaker`

Handles:
- command execution
- transaction history
- status updates
- pre-operation snapshot support

### Hardware & Recovery Module
- `HardwareLayer`
- `FailureHandler`
- `RetryHandler`
- `RecalibrationHandler`
- `TechnicianAlertHandler`

Handles:
- hardware simulation
- diagnostics
- failure recovery flow
- escalation for unresolved issues

### Event & Monitoring Module
- `EventBus`
- `LowStockEvent`
- `HardwareFailureEvent`
- `PolicyViolationEvent`
- `EmergencyModeActivated`
- `CityMonitoringSystem`

Handles:
- publishing alerts
- monitoring updates
- event-driven notifications

### Persistence Module
- `InventoryStorage`
- `TransactionStorage`
- `ConfigStorage`

Handles:
- inventory export
- transaction history export
- config export

---

## Simulation Flow

The project includes an interactive **console-based simulation**.

### User Mode
The user can:
- view products
- view bundles
- purchase products
- purchase bundles
- simulate hardware failure on next dispense

### Admin Mode
The admin can:
- login using password `1234`
- view inventory
- restock products
- run diagnostics
- view transaction history
- change system mode
- switch kiosk environment without rerunning the application
- save persistence files

---

## Example Demo Scenarios

### Scenario 1: University Purchase with Discount Pricing
1. Select **University** environment
2. View products
3. Purchase `Earphones`
4. System shows:
   - pricing strategy used
   - base total
   - discount applied
   - final price
5. Transaction is recorded

### Scenario 2: Hardware Failure and Recovery
1. Enter **User Mode**
2. Simulate hardware failure
3. Attempt a purchase
4. System triggers:
   - hardware failure handling
   - recovery chain
   - event notification
   - monitoring alert

### Scenario 3: Admin Operations
1. Enter **Admin Mode**
2. Login with password `1234`
3. Restock item
4. Change system mode
5. Switch kiosk environment
6. Save inventory / transactions / config

---

## Folder Structure

```text
include/          -> header files
src/              -> implementation files
frontend/         -> minimal React frontend
data/             -> generated persistence files
demo/             -> screenshots / demo media
main.cpp          -> console simulation entry point
README.md         -> project documentation
```

## Compile and Run

### Prerequisites

* C++ compiler supporting **C++17**

### Compile the C++ Project

```bash
g++ -std=c++17 main.cpp \
src/models/Product.cpp \
src/models/Transaction.cpp \
src/inventory/InventorySystem.cpp \
src/inventory/InventoryPolicy.cpp \
src/inventory/Bundle.cpp \
src/payment/PaymentSystem.cpp \
src/pricing/PricingSystem.cpp \
src/pricing/StandardPricing.cpp \
src/pricing/DiscountPricing.cpp \
src/pricing/EmergencyPricing.cpp \
src/hardware/HardwareLayer.cpp \
src/hardware/FailureHandler.cpp \
src/events/EventBus.cpp \
src/monitoring/CityMonitoringSystem.cpp \
src/core/KioskCoreSystem.cpp \
src/core/DecisionMediator.cpp \
src/core/CentralRegistry.cpp \
src/interface/KioskInterface.cpp \
src/commands/PurchaseCommand.cpp \
src/commands/RestockCommand.cpp \
src/commands/RefundCommand.cpp \
src/transaction/TransactionManager.cpp \
src/transaction/TransactionSnapshot.cpp \
src/transaction/TransactionCaretaker.cpp \
src/state/ActiveState.cpp \
src/state/PowerSavingState.cpp \
src/state/MaintenanceState.cpp \
src/state/EmergencyLockdownState.cpp \
src/factory/HospitalKioskFactory.cpp \
src/factory/MetroKioskFactory.cpp \
src/factory/UniversityKioskFactory.cpp \
src/factory/DisasterReliefKioskFactory.cpp \
src/persistence/InventoryStorage.cpp \
src/persistence/TransactionStorage.cpp \
src/persistence/ConfigStorage.cpp \
-Iinclude -o kiosk_app
```

### Run the C++ Project

Create the persistence output folder first:

```bash
mkdir -p data
```

#### macOS / Linux

```bash
./kiosk_app
```

#### Windows

```bash
kiosk_app.exe
```
