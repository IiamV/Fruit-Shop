# Fruit Ordering System

A console-based fruit ordering application written in C that allows customers to browse and order fruits while providing administrators with management capabilities.

## Features

### 🍎 Customer Features
- **User Registration & Login**: Create new accounts and securely log in
- **Fruit Browsing**: View available fruits with prices and regions
- **Regional Filtering**: Browse fruits by specific regions
- **Shopping Cart**: Add/remove items from cart
- **Order Management**: View current order and calculate total price
- **Order Confirmation**: Confirm and place orders

### 👨‍💼 Admin Features
- **Fruit Inventory Management**: View, add, and remove fruits from the system
- **Order Monitoring**: View all customer orders
- **Administrative Controls**: Full system management access

## Default Credentials

**Admin Account:**
- Username: `admin`
- Password: `123`

## Installation & Setup

1. **Clone or download** the source code
2. **Compile** the program:
   ```bash
   gcc -o fruit_ordering startover.c
   ```
3. **Run** the executable:
   ```bash
   ./fruit_ordering
   ```

## System Requirements

- C compiler (GCC recommended)
- Terminal/Console with ANSI color support
- Write permissions for creating user and order files

## File Structure

The program creates and manages the following files:
- `users.txt` - Stores customer account information
- `orders.txt` - Stores all customer orders

## Usage Guide

### Getting Started
1. Run the program
2. Choose from the main menu:
   - **Login** - Access existing account
   - **Signup** - Create new customer account
   - **Exit** - Close the program

### Customer Workflow
1. **Register/Login** to your account
2. **Browse Fruits** - View available inventory
3. **Add Items** to your cart
4. **Review Order** - Check your current selection
5. **Place Order** - Confirm and submit your order

### Admin Workflow
1. **Login** with admin credentials
2. **Manage Inventory**:
   - View current fruit list
   - Add new fruits
   - Remove existing fruits
3. **Monitor Orders** - View all customer orders
4. **System Management** - Access administrative functions

## Available Fruits (Default)

| Fruit | Region | Price |
|-------|--------|-------|
| Apple | North America | $1.15 |
| Pineapple | Africa | $5.40 |
| Cabbage | Europe | $1.25 |
| Mango | Asia | $7.00 |

## Technical Details

### Data Structures
- **User**: Stores username and password
- **Fruit**: Contains name, region, and price information
- **Cart**: Array-based shopping cart implementation

### Key Functions
- `Signin()` - User authentication
- `Signup()` - User registration
- `displayFruits()` - Show available fruits
- `addToCart()` - Add items to shopping cart
- `removeFromCart()` - Remove items from cart
- `displayCart()` - Show current cart contents

### Security Features
- Username uniqueness validation
- Admin account protection
- Input validation and error handling

## Color Coding

The application uses ANSI color codes for better user experience:
- 🟢 **Green**: Success messages, confirmations
- 🔴 **Red**: Error messages, warnings
- 🟡 **Yellow**: Headers, decorative elements

## Known Limitations

- Console-based interface only
- Simple file-based storage (no database)
- Basic security implementation
- No data encryption

## Future Enhancements (W.I.P)

- Range-based selection (e.g., 1-3, 5-8)
- Admin order deletion capabilities
- Enhanced password/username restrictions
- Improved data validation

## Troubleshooting

### Common Issues
1. **File Permission Errors**: Ensure write permissions in the program directory
2. **Invalid Input**: The program includes input validation - follow prompts carefully
3. **Username Already Taken**: Choose a different username during registration

### Error Messages
- "Username is already taken" - Choose a different username
- "Login failed" - Check credentials
- "File Error" - Check file permissions
