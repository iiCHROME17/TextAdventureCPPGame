//methods.h
#pragma once


#include "classes.h"

//THIS HEADER DOES NOT CONTAIN ANY GETTER OR SETTER FUNCTIONS

//-----------------------------------ROOM---------------------------------------------------------
//Helper function
string GetOppositeDirection(const string& direction, string& opposite) {
    if (direction == "north") {
        return  "south";
    }
    else if (direction == "south") {
        return  "north";
    }
    else if (direction == "east") {
        return  "west";
    }
    else if (direction == "west") {
        return  "east";
    }
    return "Invalid direction";
}
//Add Exit to the room
void room::addExit(const string& direction, room* room) {
    if (direction == "north" || direction == "south" || direction == "east" || direction == "west") {
        exits[direction] = room; //Add direction if it is valid
        string opposite = GetOppositeDirection(direction, opposite); //Get the opposite direction
        room->exits[opposite] = this; //Add the opposite direction to the other room

    }
    else {
        throw invalid_argument("Invalid direction");//Throw an error
    }

}

//Add item to the room
void room::addItem(const item& _item) {
    items.push_back(_item);
}
//Remove item from the room
void room::removeItem(const item& _item) {
    for(int i = 0; i < items.size(); i++){
        if(items[i].getName() == _item.getName()){
            items.erase(items.begin() + i);
            break;
        }
    }
}
void room::removeEnemy(enemy &_enemy) {
    for(int i = 0; i < enemies.size(); i++){
        if(enemies[i].getName() == _enemy.getName()){
            enemies.erase(enemies.begin() + i);
            break;
        }
    }
}
void room::removeWeapon(const weapon &_weapon) {
    for(int i = 0; i < weapons.size(); i++){
        if(weapons[i].getName() == _weapon.getName()){
            weapons.erase(weapons.begin() + i);
            break;
        }
    }
}
void room::removeTrader(trader &_trader) {
    for(int i = 0; i < traders.size(); i++){
        if(traders[i].getName() == _trader.getName()){
            traders.erase(traders.begin() + i);
            break;
        }
    }
}
//---------------------------------CHARACTER-----------------------------------------------------
character::character(const string& name, int health) : name(name), health(health) {} // Constructor
//---------------------------------PLAYER--------------------------------------------------------
player::player(const string& name, int health) : character(name, health) {} // Constructor

void player::removeWeapon(const weapon &_weapon) {
    for(int i = 0; i < weapons.size(); i++){
        if(weapons[i].getName() == _weapon.getName()){
            weapons.erase(weapons.begin() + i);
            break;
        }
    }
}
//---------------------------------Enemy---------------------------------------------------------
enemy::enemy(const string& name, int health, int damage, string voiceLine, int money) : character(name, health), damage(damage), voiceLine(voiceLine), money(money) {} // Constructor

//-----------------------------------ITEM---------------------------------------------------------
item::item(const string& name, const string& description, int weight, int value) : name(name), description(description), weight(weight), value(value) {} // Constructor

//-----------------------------------AREA---------------------------------------------------------
room* area::getRoom(const string &name) const {
    auto it = rooms.find(name); // Find the room by name
    //if not found throw an error
    if (it == rooms.end()) {
        throw invalid_argument("Room not found");
    }
    return (it != rooms.end()) ? it->second : nullptr; // Return the room if it exists, otherwise return nullptr

}

void area::addRoom(const std::string& name, room* _room) {
    rooms[name] = _room;
}

void area::loadArea(const std::string &filename, const bool debug) {
    ifstream file(filename); // Open the file
    if (!file.is_open()) { // If the file is not open
        throw invalid_argument("File not found"); // Throw an error
    }
    //Read the file. Structure of the file is as follows:
    //ROOM1,DIRECTION,ROOM2. The delimiter is "|"

    string line;
    while (getline(file, line)) { // Read the file line by line
        stringstream ss(line); // Create a stringstream from the line
        string room1, direction, room2; // Create variables for the room1, direction, and room2
        getline(ss, room1, '|'); // Get the room1
        getline(ss, direction, '|'); // Get the direction
        getline(ss, room2, '|'); // Get the room2
        if (rooms.find(room1) == rooms.end()) { // If the room1 is not in the map
            rooms[room1] = new room(room1); // Create a new room
        }
        if (rooms.find(room2) == rooms.end()) { // If the room2 is not in the map
            rooms[room2] = new room(room2); // Create a new room
        }
        rooms[room1]->addExit(direction, rooms[room2]); // Add the exit from room1 to room2

        //DEBUG
        if (debug) {
            cout << direction << " OF " << room1 << " LEADS TO " << room2 << endl;
        }
    }
}
//---------------------------------INTERPRETER-----------------------------------------------------





