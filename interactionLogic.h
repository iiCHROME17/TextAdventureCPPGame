
#pragma once
#include <cmath>


void fightInteraction(player* player, enemy* enemy) {
    // Check if the player has weapons
    if (player->getWeapons().empty()) {
        cout << "You have no weapons. You die treacherously." << endl;
        exit(0);
    }

    // Initialize playerWeapon to point to the first weapon in the player's inventory
    weapon* playerWeapon = &player->getWeapons()[0];
    int playerDamage = playerWeapon->getDamage(); // Base damage from the weapon

    cout << enemy->getName() << " approaches." << endl;
    cout << enemy->getName() << ": " << enemy->getVoiceLine() << endl;

    //Give player choice of weapon
    cout << "Select a weapon to use:" << endl; //
    for (int i = 0; i < player->getWeapons().size(); ++i) {
        cout << i + 1 << ". " << player->getWeapons()[i].getName() << endl;
    }
    int weaponChoice;
    cout << "Enter the number of the weapon: ";
    cin >> weaponChoice;
    if (weaponChoice >= 1 && weaponChoice <= player->getWeapons().size()) {
        playerWeapon = &player->getWeapons()[weaponChoice - 1];
        playerDamage = playerWeapon->getDamage();
    } else {
        cout << "Invalid weapon choice." << endl;
    }



    while (player->getHealth() > 0 && enemy->getHealth() > 0) {
        cout << "You have " << player->getHealth() << " health" << endl;
        cout << "The enemy has " << enemy->getHealth() << " health" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Change Weapon" << endl;
        cout << "3. Run" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) { // Attack
            int critChance = rand() % 100; // Random number from 0 to 99
            if (critChance < 10) { // 10% chance of critical hit
                playerDamage *= 2; // Double the damage
                cout << "Determination fills your heart. You strike with double the force!" << endl;
            }
            else if (critChance > 90) { // 10% chance of missing
                playerDamage = 0; // No damage
                cout << "You missed your attack." << endl;
            }
            else{
                cout << "You attack the enemy." << endl;
            }
            cout << "You deal " << playerDamage << " damage." << endl;

            enemy->takeDamage(playerDamage);
            playerDamage = playerWeapon->getDamage(); // Reset the damage to the base damage

        } else if (choice == 2) { // Change Weapon
            cout << "Select a weapon to use:" << endl;
            for (int i = 0; i < player->getWeapons().size(); ++i) {
                cout << i + 1 << ". " << player->getWeapons()[i].getName() << endl;
            }
            int weaponChoice;
            cout << "Enter the number of the weapon: ";
            cin >> weaponChoice;
            if (weaponChoice >= 1 && weaponChoice <= player->getWeapons().size()) {
                playerWeapon = &player->getWeapons()[weaponChoice - 1];
                playerDamage = playerWeapon->getDamage();
                cout << "You've switched to " << playerWeapon->getName() << endl;
            } else {
                cout << "Invalid weapon choice." << endl;
            }
        } else if (choice == 3) { // Run
            cout << "You ran away." << endl;
            return;
        } else { // Invalid choice
            cout << "Invalid choice. Please try again." << endl;
        }

        // Enemy's turn
        int enemyDamage = enemy->getDamage(); // Get enemy's damage
        player->takeDamage(enemyDamage); // Apply damage to the player

        cout << "The enemy attacks! You take " << enemyDamage << " damage." << endl;

        // Check if player or enemy has no health left
        if (player->getHealth() <= 0) {
            cout << "You were defeated." << endl;
            cout << "So, the story ends here." << endl;
            cout << player->getName() << " has died, eternally resting in " << player->getLocation()->getID() << "." << endl;
            cout << "Never to recue his daughter's soul, always to roam the treacherous king's domain." << endl;
            cout << "Day will come where he rises again, but as a mindless, treacherous soul." << endl;
            exit(0); // End the game (exit the program)
            return;
        } else if (enemy->getHealth() <= 0) {
            cout << "You defeated the enemy." << endl;
            player->addMoney(enemy->getMoney());
            player->setMaxHealth(player->getMaxHealth() + 25);
            cout << "You currently have " << player->getMoney() << " gold attained." << endl;
            player->getLocation()->removeEnemy(*enemy);
            return;
        }
    }

}

