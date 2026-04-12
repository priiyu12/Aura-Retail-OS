# Aura-Retail-OS — C++ Prototype

![Language](https://img.shields.io/badge/language-C++-blue)
![Stage](https://img.shields.io/badge/stage-Subtask%202-green)

A modular C++ prototype for an autonomous smart-city retail kiosk platform designed using object-oriented principles and design patterns.

## Project Overview

Zephyrus Retail OS is a smart retail kiosk system designed for multiple deployment environments:
- hospitals dispensing prescription medication
- metro stations selling daily essentials
- university campuses selling electronics
- disaster zones distributing emergency supplies

This project is being developed as part of the **IT620 Object Oriented Programming Project**.

## Project Architecture Overview

The system follows a layered and modular architecture to ensure scalability, maintainability, and clear separation of concerns.

### Layers

- **Interface Layer**
  - `KioskInterface` (Facade Pattern)
  - Provides simplified interaction for users and administrators

- **Core Layer**
  - `KioskCoreSystem`
  - Coordinates all subsystems and manages workflow

- **Subsystems**
  - Inventory System
  - Payment System
  - Hardware Layer
  - Pricing System
  - Event & Monitoring System

All subsystems interact through well-defined interfaces, ensuring low coupling and high cohesion across the system.

## Current Stage

This repository currently represents **Subtask 2: Prototype Implementation**.

At this stage, the project includes:
- partial source code
- selected design pattern implementation
- a basic working simulation
- structure for future expansion in the final submission

Some files are intentionally kept as placeholders and will be fully implemented in **Subtask 3**.

## Implemented Features in Subtask 2

The current prototype supports:

- interactive kiosk selection
- environment-specific product setup for all 4 kiosk types
- inventory display and stock checking
- purchase flow using user input
- payment method handling
- hardware dispensing simulation
- low stock alert generation
- hardware failure alert simulation

## Implemented Design Patterns

### 1. Facade Pattern
Implemented using `KioskInterface` to provide simplified access to kiosk operations such as:
- viewing products
- purchasing items
- running diagnostics

### 2. Strategy Pattern
Implemented using:
- `PricingStrategy`
- `StandardPricing`
- `PricingSystem`

This allows pricing behavior to be modular and extensible.

### 3. Observer Pattern
Implemented using:
- `Event`
- `EventBus`
- `EventListener`
- `CityMonitoringSystem`

This allows event-driven communication for alerts such as:
- low stock detection
- hardware failure

## Current Working Modules

- `Product`
- `InventorySystem`
- `PaymentSystem`
- `HardwareLayer`
- `PricingSystem`
- `KioskCoreSystem`
- `KioskInterface`
- `EventBus`
- `CityMonitoringSystem`

## Placeholder / Planned Modules for Subtask 3

The following components currently exist as placeholders and will be fully implemented in the final submission:

- `CentralRegistry`
- `DiscountPricing`
- `EmergencyPricing`
- `Transaction`
- `Command`
- `PurchaseCommand`
- `RefundCommand`
- `RestockCommand`
- `TransactionManager`
- `TransactionSnapshot`
- `TransactionCaretaker`

## Simulation Flow

The current simulation works through console input:

1. user selects kiosk type
2. system loads products for that environment
3. user views products
4. user enters product ID, quantity, and payment method
5. system checks stock
6. system calculates final price
7. payment is processed
8. hardware attempts dispensing
9. system updates inventory and publishes alerts when needed

## Team Contribution Mapping

### Priya J Shah — 202512100
- Product model
- Inventory system
- stock calculation and inventory operations

### Jay Shah — 202512059
- Kiosk interface
- kiosk core system
- pricing strategy integration

### Priya D Shah — 202512105
- payment system
- planned transaction and command modules

### Jenil Shah — 202512110
- hardware abstraction layer
- event system
- monitoring and alert handling

## Folder Structure

```text
include/   -> header files
src/       -> implementation files
main.cpp   -> interactive simulation entry point
README.md  -> project documentation

## How to Compile and Run

### Prerequisites
- C++ compiler supporting C++17 (g++ / clang++)
- Terminal / Command Prompt

---

## Compile the Project

### On Mac / Linux

```bash
g++ -std=c++17 main.cpp src/*/*.cpp -o kiosk_app

### On Windows

```bash
g++ -std=c++17 main.cpp src/*/*.cpp -o kiosk_app.exe


## Run the Project

### On Mac / Linux

```bash
./kiosk_app

### On Windows

```bash
kiosk_app.exe