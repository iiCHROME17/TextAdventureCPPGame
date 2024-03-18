//classes.h - MOSTLY CONTAINS THE DECLARATION OF THE CLASSES. TRADER CLASS AND METHODS IN HERE
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <limits>


using namespace std;

//-----------------------------------FORWARD-DECLARATION------------------------------------------
class trader;
class enemy;
class weapon;
class soul;
class player;

//-----------------------------------ITEM---------------------------------------------------------
class item {
    private:
    string name; // Name of the item
    string description; // Description of the item
    int weight; // Weight of the item
    int value; // Value of the item
    public:
    item(const string& name, const string& description, int weight, int value); // Constructor
    string getName() const { return name; } // Get the name of the item
    string getDescription() const { return description; } // Get the description of the item
    int getWeight() const { return weight; } // Get the weight of the item
    int getValue() const { return value; } // Get the value of the item
    virtual void interact(player* player) const  = 0; // Interact with the item
};
//-----------------------------------ROOM---------------------------------------------------------
class room {
private:
    string name; // ID of the room
    string description; // description of the room
    map<string, room*> exits; //Directions to other rooms
    vector<item*> items; //Items in the room
    vector<weapon> weapons; //Weapons in the room
    vector<enemy> enemies;//Items in the room
    vector<trader> traders; //Traders in the room


public:
    room(const string& name) : name(name){}  // Constructr
    string getID() const { return name; } // Get the ID (name) of the room
    string getDescription() const { return description; } // Get the description of the room
    map<string, room*> getExits() const { return exits; } // Get the exits of the room
    vector<item*> getItems() const { return items; } // Get the items in the room
    vector<weapon> getWeapons() const { return weapons; } // Get the weapons in the room

    void setDescription(const string& description) { this->description = description; } // Set the description of the room
    void setName(const string& ID) { this->name = name; } // Set the ID of the room

    void addItem(item* _item); // Add an item to the room
    void addWeapon(const weapon& _weapon) { weapons.push_back(_weapon); } // Add a weapon to the room
    void removeItem(const item& _item); // Remove an item from the room
    void removeWeapon(const weapon& _weapon) ;// Remove a weapon from the room
    void addExit(const string& direction, room* room); // Add an exit to the room

    void addEnemy(const enemy& _enemy) { enemies.push_back(_enemy); } // Add an enemy to the room
    void removeEnemy(enemy& _enemy) ; // Remove an enemy from the room
    vector<enemy> getEnemies() const { return enemies; } // Get the enemies in the room

    void addTrader(const trader& _trader) { traders.push_back(_trader); } // Add a trader to the room
    vector<trader> getTraders() const { return traders; } // Get the traders in the room
    void removeTrader(trader& _trader); // Remove a trader from the room


};
//---------------------------------CHARACTER-----------------------------------------------------
class character{
private:
    string name; // Name of the character
    int health = 100; // Health of the character
    vector<item*> inventory; // Inventory of the character
    int maxWeight = 150; // Maximum weight the character can carry

    public:
    character(const string& name, int health); // Constructor
    int getHealth() const { return health; } // Get the health of the character
    void setHealth(int health) { this->health = health; } // Set the health of the character
    string getName() const { return name; } // Get the name of the character
    vector<item*> getInventory() const { return inventory; } // Get the inventory of the character
    int getMaxWeight() const { return maxWeight; } // Get the maximum weight the character can carry
    void addItem(item* _item) { inventory.push_back(_item); } // Add an item to the inventory
    void removeItem(const item& _item); // Remove an item from the inventory
    void takeDamage(int damage) { health -= damage; } // Take damage


};

//---------------------------------Enemy-----------------------------------------------------
class enemy : public character {
    //This class is seperate from NPCs because they are only capable of fighting
private:
    int damage; // Damage the enemy can deal
    string voiceLine; // Voice line of the enemy
    int money; // Money the enemy has
    soul* soul; // Soul the enemy has

    public:
    enemy(const string& name, int health, int damage, string voiceLine, int money); // Constructor
    int getDamage() const { return damage; } // Get the damage the enemy can deal
    class soul* getSoul() const { return soul; } // Get the soul the enemy has
    void setSoul(class soul* soul) { this->soul = soul; } // Set the soul the enemy has
    void dropSoul(player* player) const; // Drop the soul of the enemy
    int getMoney() const { return money; } // Get the money the enemy has
    string getVoiceLine() const { return voiceLine; } // Get the voice line of the enemy
    void setVoiceLine(string voiceline); // Set the voice line of the enemy

};
//---------------------------------PLAYER--------------------------------------------------------
class player : public character {
private:

    room* currentRoom; // Current room of the player
    vector<weapon> weapons; // Weapons the player has
    int money = 0; // Money the player has
    int maxHealth = 100; // Maximum health the player can have
    int vigor = 0; // Vigor the player has (damage boost)

    public:
    player(const string& name, int health); // Constructor
    room* getLocation() const { return currentRoom; } // Get the current room of the player
    void setLocation(room* room) { currentRoom = room; } // Set the current room of the player
    void addWeapon(const weapon& _weapon) { weapons.push_back(_weapon); } // Add a weapon to the player
    vector<weapon> getWeapons() const { return weapons; } // Get the weapons the player has
    void removeWeapon(const weapon& _weapon); // Remove a weapon from the player
    int getMoney() const { return money; } // Get the money the player has
    void addMoney(int amount) { money += amount; } // Add money to the player
    void removeMoney(int amount) { money -= amount; } // Remove money from the player
    int getMaxHealth() const { return maxHealth; } // Get the maximum health the player can have
    void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; } // Set the maximum health the player can have
    int getVigor() const { return vigor; } // Get the vigor the player has
    void setVigor(int vigor) { this->vigor = vigor; } // Set the vigor the player has

};
//-----------------------------------AREA---------------------------------------------------------
class area {
private:
    map<string, room*> rooms; //Rooms in the area
public:
    area() {} // Constructor
    void addRoom(const string& name, room* room); // Add a room to the area
    map <string, room*> getRooms() const { return rooms; } // Get the rooms in the area
    void printAllRooms() const; // Print all rooms in the area
    room* getRoom(const string& name) const; // Get a room from the area
    void connectRooms(const string& room1, const string& room2, const string& direction); // Connect two rooms
    void loadArea(const string& filename, const bool debug); // Load an area from a file

};
//---------------------------------INTERPRETER-----------------------------------------------------
class interpreter{
    private:
    player* player_;
public:
    interpreter(player* player) : player_(player) {} // Constructor
    void readCommand(const string& command); // Read a command from the user
    void listCommands() const; // List all available commands
};
//---------------------------------WEAPON---------------------------------------------------------
class weapon : public item {
private:
    int damage; // Damage the weapon can deal


public:
    weapon(const string& name, const string& description, int weight, int value, int damage)
            : item(name, description, weight, value), damage(damage){} // Constructor
    int getDamage() const { return damage; } // Get the damage the weapon can deal
    void interact(player* player) const override; // Interact with the weapon
};
//---------------------------------SOUL--------------------------------------------------------
class soul : public item {
private:
    int health; // Health the soul can give
public:
    soul(const string& name, const string& description, int health)
            : item(name, description, 0, 0), health(health) {} // Constructor
    int getHealth() const { return health; } // Get the health the soul can give
    void interact(player* player) const override; // Interact with the soul
};
//---------------------------------ADVANCED:TRADER------------------------------------------------
class trader {
private:
    enum State { FEAR, TRADE };
    string name;
    int health;
    int money;
    vector<weapon> weaponsForSale;
    State currentState;

public:
    trader(const string& name  , int money) : name(name), money(money) {}

    State getState() const { return currentState; } // Get the state of the trader
    void setState(State state) { currentState = state; } // Set the state of the trader
    string getName() const { return name; } // Get the name of the trader
    int getMoney() const { return money; }
    vector<weapon> getWeapons() const { return weaponsForSale; }
    void removeWeapon(const weapon& _weapon) {
        for(int i = 0; i < weaponsForSale.size(); i++){
            if(weaponsForSale[i].getName() == _weapon.getName()){
                weaponsForSale.erase(weaponsForSale.begin() + i);
                break;
            }
        }
    }
    void addWeapon(const weapon& _weapon) { weaponsForSale.push_back(_weapon); }

    void determineState(player* player) {
        if (player->getLocation()->getEnemies().size() > 0) { // If there are enemies in the room
            currentState = FEAR;
        } else {
            currentState = TRADE;
        }
    }

    void interact(player* player) {
        cout << "A trader stands before you." << endl;
        determineState(player);

        switch (currentState) {
            case FEAR:
                cout << "The trader is too scared to talk to you." << endl;
                cout << getName() << ": Please, get rid of these treacherously-afflicted being first." << endl;
                break;
            case TRADE:
                trade(player);
                break;
            default:
                break;
        }
    }

    void trade(player* player) {
        cout << trader::getName() << ": Hello, Returned Solider." << endl;
        cout << trader::getName() << ": I have the following weapons for sale:" << endl;
        for (int i = 0; i < weaponsForSale.size(); i++) {
            cout << i + 1 << ". " << weaponsForSale[i].getName() << " - " << weaponsForSale[i].getValue() << " gold" << endl;
        }
        cout << "You have " << player->getMoney() << " gold." << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Buy" << endl;
        cout << "2. Sell" << endl;
        cout << "3. Leave" << endl;

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid choice. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        switch (choice) {
            case 1:
                buy(player);
                break;
            case 2:
                sell(player);
                break;
            case 3:
                cout << "You leave the trader alone." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                break;
            default:
                cout << "Invalid choice" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }
    void buy(player* player) {

        cout << "Enter the number of the weapon you want to buy" << endl;
        for (int i = 0; i < weaponsForSale.size(); i++) {
            cout << i + 1 << ". " << weaponsForSale[i].getName() <<  "- " << weaponsForSale[i].getValue() << " gold" << endl;
        }

        int choice;
        // Get the choice from the user
        if (!(cin >> choice)) {
            cout << "Invalid choice. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        // Check if the choice is valid
        if (choice < 1 || choice > weaponsForSale.size()) {
            cout << "Invalid choice" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return;
        }

        // Get the index of the weapon
        int weaponIndex = choice - 1;
        int weaponValue = weaponsForSale[weaponIndex].getValue();

        // Check if the player has enough money to buy the weapon
        if (player->getMoney() < weaponValue) {
            cout << "You don't have enough gold to buy this weapon" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return;
        }

        // Add the weapon to the player's inventory

        weapon boughtWeapon = weaponsForSale[weaponIndex];
        player->addWeapon(boughtWeapon);

        // Remove the weapon from the trader's inventory
        player->removeMoney(weaponValue);
        weaponsForSale.erase(weaponsForSale.begin() + weaponIndex);
        cout << "You bought " << boughtWeapon.getName() << " for " << weaponValue << " gold" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }
    // Sell a weapon to the trader
    void sell(player* player) {
        if(player->getWeapons().size() == 0){
            cout << "You have no weapons to sell." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return;
        }
        cout << "Enter the number of the weapon you want to sell" << endl;
        vector<weapon> playerWeapons = player->getWeapons();
        for (int i = 0; i < playerWeapons.size(); i++) {
            cout << i + 1 << ". " << playerWeapons[i].getName() << " - " << playerWeapons[i].getValue() << " gold" << endl;
        }

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid choice. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (choice < 1 || choice > playerWeapons.size()) {
            cout << "Invalid choice" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return;
        }

        int weaponIndex = choice - 1;
        int weaponValue = playerWeapons[weaponIndex].getValue();

        player->removeWeapon(playerWeapons[weaponIndex]); // Remove the weapon from the player's inventory
        player->addMoney(weaponValue); // Add the weapon value to the player's money
        cout << "You sold " << playerWeapons[weaponIndex].getName() << " for " << weaponValue << " gold" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }
};