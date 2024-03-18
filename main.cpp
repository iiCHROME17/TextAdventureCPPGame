//main.cpp
#include "interpreter.h"
#include "methods.h"


int main() {

    area gameWorld;
    gameWorld.loadArea("area.txt", false);


    //Create player and interpreter
    player player1("The Returned", 100);
    player1.addMoney(100); //Start with 100 gold
    interpreter commandline(&player1);

    //Create Items
    weapon TST("The Soul Tether","A Powerful Artifact That Ends The Curse Of Treachery.", 5, 12, 35);
    weapon TTJ("Treacherous Trolls Jokery", "A Poor Excuse For A Weapon.", 1, 10, -100);
    weapon TCB("The Cross Bane","A powerful, yet heavy, sword capable of heavy strikes.", 40,150,30);
    weapon HKLG("The Holy Knight's Last Gift","A Sword only the truly capable can wield.", 70,200,41);
    weapon TTPR("The Treacherous Peasant's Rapier","A powerful, yet light, sword capable of swift strikes.", 20,220,51);
    weapon TBOZ("The Blade of Zion","A powerful, yet light, sword capable of swift strikes.", 20,100,22);




    //Room metadata
    room* startRoom = gameWorld.getRoom("The Entrance");
    gameWorld.getRoom("The Entrance")->setDescription("The sky bleeds crimson. The Moon shines white. Ahead lies the Treacherous King's Domain. A blade sticks out the soil.");
    gameWorld.getRoom("Hallway")->setDescription("The corridor is dark and damp. The floor is decorated with skeletons of Kingdom Men."
                                                 "Some Still Stand.");
    gameWorld.getRoom("World's Edge")->setDescription("The back of the castle is a cliff. The wind is strong and the view is breathtaking. Darkness enshrouds the land."
                                                      "Be wary, for in the dark corner, The Treacherous King awaits.");
    gameWorld.getRoom("Abyss")->setDescription("Its dark, faint screams and cries can be heard. Is this hell?");

    //Add enemies to rooms
    enemy treacherousKing("The Treacherous King, Modius VII", 225, 45,"This is My Kingdom! You Shall not take it from me!",230);
    enemy treacherousWomb("An Amalgamation of Treacherous Peasants", 65, 37, "Help, Please..... Stop, Save us....", 70);
    enemy treacherousGuard("The Treacherous Guard", 50, 30, "For the Glory!", 55);

    //Give enemies souls
    soul tGS("The Treacherous Guard's Soul", "A soul of a treacherous guard. It's filled with treachery.", 25);
    soul* tGSptr = &tGS;
    soul tWS("The Treacherous Womb's Soul", "A soul of a treacherous womb. It overflows with treachery.", 0);
    soul* tWSptr = &tWS;
    soul tKS("The Treacherous King's Soul", "A soul of a treacherous king. It's filled with treachery.", 150 );
    soul* tKSptr = &tKS;





    //Extra enemies to add to the room
    enemy tg1 = treacherousGuard;
    enemy tg2 = treacherousGuard;
    enemy tg3 = treacherousGuard;

    tg1.setSoul(tGSptr);
    tg2.setSoul(tGSptr);
    tg3.setSoul(tGSptr);
    treacherousWomb.setSoul(tWSptr);
    treacherousKing.setSoul(tKSptr);

    gameWorld.getRoom("Abyss")->addEnemy(treacherousWomb);
    gameWorld.getRoom("Hallway")->addEnemy(tg1);
    gameWorld.getRoom("Hallway")->addEnemy(tg2);
    gameWorld.getRoom("Hallway")->addEnemy(tg3);
    gameWorld.getRoom("World's Edge")->addEnemy(treacherousKing);

    //Add Trader to room
    trader merchant1("The Gateseller", 300);
    merchant1.addWeapon(TCB);
    merchant1.addWeapon(TST);
    trader secretMerchant("The Dark Marketeer", 300);
    secretMerchant.addWeapon(HKLG);
    secretMerchant.addWeapon(TTPR);
    trader troll("The Treacherous Troll", 300);
    troll.addWeapon(TTJ);
    gameWorld.getRoom("Hallway")->addTrader(troll);
    gameWorld.getRoom("Abyss")->addTrader(secretMerchant);
    gameWorld.getRoom("The Entrance")->addTrader(merchant1);

    //Add items to rooms
    gameWorld.getRoom("The Entrance")->addWeapon(TBOZ);


    //Set the player's location to the start room
    player1.setLocation(startRoom);


    commandline.listCommands();

    cout <<"Welcome back to the realm of the living,The Returned.\nYou have been brought back to investigate the treacherous king's domain.\nTo Save your daughter's soul, you must defeat The Soul of the Treachorous.\n" << endl;
    //Game loop
    room *finalBossRoom = gameWorld.getRoom("World's Edge");
    //cout << finalBossRoom->getEnemies().size() << endl;
    while(finalBossRoom->getEnemies().size() > 0){
        if(player1.getLocation() != nullptr)
        {
            cout << "You are in " << player1.getLocation()->getID() << endl;
            cout << player1.getLocation()->getDescription() << endl;
            cout << "\n" << endl;

            string command;

            cout << "What would you like to do?" << endl;
            getline(cin, command);
            commandline.readCommand(command);
        }



    }
    cout << "You have defeated the treacherous king. You have saved your daughter's soul." << endl;
    cout << "The curse of treachery has been lifted." << endl;
    cout << "You have won the game." << endl;
    return 0;

}
