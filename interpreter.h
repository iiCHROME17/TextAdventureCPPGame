//interpreter.h - CONTAINS THE INTERPRETER  METHODS
#pragma once
#include "classes.h"
#include "interactionLogic.h"

void interpreter::readCommand(const string& command) {
    istringstream iss(command); // Create an input string stream
    vector<string> words; // Create a vector to store each word in the command
    string word; // Create a string to store each word in the command

    while (iss >> word) { // While there are words to read
        words.push_back(word); // Add the word to the vector
    }

    if (words[0] == "go") { // If the first word is "go"
        if (words.size() != 2) { // If the command is not in the format "go <direction>"
            cout << "Invalid command. Please state the desired direction." << endl; // Print an error message
            return; // Return
        }
        string direction = words[1]; // Get the direction
        room* currentRoom = player_->getLocation(); // Get the current room of the player
        auto exits = currentRoom->getExits(); // Get the exits of the current room

        if (exits.find(direction) == exits.end()) { // If the direction is not in the exits of the current room
            cout << "There is no exit in that direction" << endl; // Print an error message
            return; // Return
        }

        player_->setLocation(exits[direction]); // Set the location of the player to the room in the direction
    }
    else if(words[0] == "loot"){
        room* currentRoom = player_->getLocation(); // Get the current room of the player
        vector<weapon> weapons = currentRoom->getWeapons(); // Get the weps in the current room
        if(weapons.size() == 0) { // If there are no items in the room
            cout << "There are no items in this room" << endl; 
            return; // Return
        }

        while (true){
            cout << "Enter the number of the weapon you want to loot" << endl; 
            for (int i = 0; i < weapons.size(); i++) {
                cout << i+1 << ". " << weapons[i].getName() << endl; // Print the name of the item
            }
            int choice; // Create a variable to store the choice
            cin >> choice; // Get the choice from the user
            if(choice < 1 || choice > weapons.size()) { // If the choice is not valid
                cout << "Invalid choice" << endl; // Print an error message
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                cout << "You looted " << weapons[choice-1].getName() << endl;
                player_->addWeapon(weapons[choice-1]); // Add the weapon to the player's inventory
                currentRoom->removeWeapon(weapons[choice-1]); // Remove the weapon from the room
                return; // Return
            }

        }
    }
    else if (words[0] == "rest") { // If the first word is "rest"
        player_->setHealth(player_->getMaxHealth()); // Set the health of the player to 100
        cout << "You are fully rested" << endl; 
        cout << "You have " << player_->getHealth() << " health" << endl; // Print the health of the player
    }
    else if(words[0] == "confront"){
        room* currentRoom = player_->getLocation(); // Get the current room of the player
        vector<enemy> enemies = currentRoom->getEnemies(); // Get the enemies in the current room
        if(enemies.size() == 0) { // If there are no enemies in the room
            cout << "There are no enemies in this room" << endl; 
            return; // Return
        }

        while (true) { // Continue prompting until a valid choice is entered
            cout << "Enter the number of the enemy you want to confront" << endl; 
            for (int i = 0; i < enemies.size(); i++) {
                cout << i+1 << ". " << enemies[i].getName() << endl; // Print the name of the enemy
            }
            int choice; // Create a variable to store the choice
            cin >> choice; // Get the choice from the user
            if(choice < 1 || choice > enemies.size()) { // If the choice is not valid
                cout << "Invalid choice" << endl; // Print an error message
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                cout << "You confront " << enemies[choice-1].getName() << endl;
                fightInteraction(player_, &enemies[choice-1]); // Fight the enemy
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                return; // Return
            }
        }
    }
    else if (words[0] == "talk"){
        room* currentRoom = player_->getLocation(); // Get the current room of the player
        vector<trader> traders = currentRoom->getTraders(); // Get the traders in the current room
        if(traders.size() == 0) { // If there are no traders in the room
            cout << "There are no traders in this room" << endl; 
            return; // Return
        }

        while (true) { // Continue prompting until a valid choice is entered
            cout << "Enter the number of the trader you want to talk to" << endl; 
            for (int i = 0; i < traders.size(); i++) {
                cout << i+1 << ". " << traders[i].getName() << endl; // Print the name of the trader
            }
            int choice; // Create a variable to store the choice
            cin >> choice; // Get the choice from the user
            if(choice < 1 || choice > traders.size()) { // If the choice is not valid
                cout << "Invalid choice" << endl; // Print an error message
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                cout << "You talk to " << traders[choice-1].getName() << endl;
                traders[choice-1].interact(player_); // Interact with the trader
                return; // Return
            }
        }
    }
    else if(words[0] == "inventory") { // If the first word is "inventory"
        cout << "You have: "<< player_->getMoney() << " gold coins." << endl; // Print the amount of money the player has
        if(player_->getInventory().size() == 0) { // If the inventory is empty
            cout << "You have no items in your inventory" << endl;
            return; // Return
        }
        cout << "In your inventory, you own:" << endl;
        for(int i = 0; i < player_->getInventory().size(); i++) { // For each item in the inventory
            cout << i+1 << ":" << player_->getInventory()[i]->getName() << ": " << player_->getInventory()[i]->getDescription() << endl; // Print the name and description of the item
        }
        int choice; // Create a variable to store the choice
        cout << "Enter the number of the item you want to inspect: ";
        cin >> choice; // Get the choice from the user
        if(choice < 1 || choice > player_->getInventory().size()) { // If the choice is not valid
            cout << "Invalid choice" << endl; // Print an error message
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "You inspect " << player_->getInventory()[choice-1]->getName() << endl;
            player_->getInventory()[choice-1]->interact(player_); // Inspect the item
            player_->removeItem(*player_->getInventory()[choice-1]); // Remove the item from the inventory
            return; // Return
        }
        
    }
    else if(words[0] == "weapons"){
        vector<weapon> weapons = player_->getWeapons(); // Get the weapons of the player
        if(weapons.size() == 0) { // If the inventory is empty
            cout << "You have no weapons" << endl; 
            return; // Return
        }
        cout << "Your weapons are:" << endl; 
        for(int i = 0; i < weapons.size(); i++) { // For each item in the inventory
            cout << i+1 << ". " << weapons[i].getName() << ": " << weapons[i].getDescription() << endl; // Print the name and description of the item
        }
        int choice; // Create a variable to store the choice
        cout << "Enter the number of the weapon you want to inspect: "; 
        cin >> choice; // Get the choice from the user

        if(choice < 1 || choice > weapons.size()) { // If the choice is not valid
            cout << "Invalid choice" << endl; // Print an error message
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "You inspect " << weapons[choice-1].getName() << endl;
            weapons[choice-1].interact(player_); // Inspect the item
            return; // Return
        }
    }
    else if(words[0] == "help") { // If the first word is "help"
        listCommands(); // List the available commands
    }
    else if(words[0] == "quit") { // If the first word is "quit"
        exit(0); // Exit the program
    }
    else if(words[0] == "sec_dev::" && words[1] == "money" ) { // Developer command to add money
        //if we can turn the next word into an int
        if (words.size() == 3 && isdigit(words[2][0])) {
            player_->addMoney(stoi(words[2])); // Add the money to the player's inventory
            cout << "You now have " << player_->getMoney() << " gold coins." << endl; // Print the amount of money the player has
            //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        }
        else {
            cout << "Invalid command. Please state the amount of money you want to add." << endl; // Print an error message
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        }
    }
    else { // If the command is not recognized
        cout << "Unrecognized command. " << endl; // Print an error message
        listCommands(); // List the available commands
    }

}
void interpreter::listCommands() const {
    cout << "The following commands are available:\n" << endl;
    cout << "go <direction> - Move in the specified direction." << endl;
    cout << "rest - Replenish health." << endl;
    cout << "confront - Confront an enemy in the current room." << endl;
    cout << "talk - Talk to a trader in the current room." << endl;
    cout << "loot - Loot a weapon from the current room." << endl;
    cout << "inventory - View the gold in your inventory." << endl;
    cout << "weapons - View the weapons in your inventory." << endl;
    cout << "help - Display the list of available commands." << endl;
    cout << "quit - Exit the game.\n" << endl;
}