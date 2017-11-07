#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

const int numberOfColumns = 37;
const int numberOfRows = 15;

using namespace std;

class Monster;

class Character{
private:
    string name;
    int healthPoint;
    int attackValue;
    int defenseValue;
    char level;
    int posX;
    int posY;
public:
    string getName() {return name;}
    int getHealthPoint() {return healthPoint;}
    int getAttackValue() {return attackValue;}
    int getDefenseValue() {return defenseValue;}
    char getLevel() {return level;}
    int getPosX() {return posX;}
    int getPosY() {return posY;}

    void setName(string name) {this->name = name;}
    void setHealtPoint(int hp) {healthPoint = hp;}
    void setAttackValue(int av) {attackValue = av;}
    void setDefenseValue(int dv) {defenseValue = dv;}
    void setLevel(char lvl) {level = lvl;}
    void setPosX(int x) {posX = x;}
    void setPosY(int y) {posY = y;}
    void changeX(int x){
        if (posX + x < numberOfColumns && posX + x >= 0)
            posX += x;
    }
    void changeY(int y){
        if (posY + y < numberOfRows && posY + y >= 0)
            posY += y;
    }
};


class Hero : public Character{
public:
    Hero(string name, int hp, int atk, int def, char lvl){
        setName(name);
        setHealtPoint(hp);
        setAttackValue(atk);
        setDefenseValue(def);
        setLevel(lvl);
        setPosX(0);
        setPosY(0);
    }

    void step(char command){
        switch (command){
        case 'w': changeY(-1); break;
        case 'a': changeX(-1); break;
        case 's': changeY(1); break;
        case 'd': changeX(1); break;
        }
    }

    void printDetails(){
        cout << "\n\n\n" <<
        " " << getName() << ":\n" <<
        " \t" << "Level: " << getLevel() << '\n' <<
        " \t" << "Health: " << getHealthPoint() << '\n' <<
        " \t" << "Attack: " << getAttackValue() << '\n' <<
        " \t" << "Defense: " << getDefenseValue();
    }
};


class Monster : public Character{
    void moveUp(int distance) {changeY(-distance);}
    void moveDown(int distance) {changeY(distance);}
    void moveLeft(int distance) {changeX(-distance);}
    void moveRight(int distance) {changeX(distance);}
public:
    Monster(int hp, int atk, int def, char lvl){
        setHealtPoint(hp);
        setAttackValue(atk);
        setDefenseValue(def);
        setLevel(lvl);
        setPosX(rand() % numberOfColumns);
        setPosY(rand() % numberOfRows);
    }
    void moving(){
        int direction = rand() % 4;
        int distance = rand() % 3 + 1;
        switch (direction){
        case 0: moveUp(distance); break;
        case 1: moveDown(distance); break;
        case 2: moveLeft(distance); break;
        case 3: moveRight(distance); break;
        }
    }
};


class Game{
    int sizeX;
    int sizeY;
    int numberOfMonsters = 5;
    vector<Monster> monsters;
    vector<char> line;
    vector<vector<char>> field;

    bool areTheyClose(Hero &hero, Monster &monster){
        if (abs(hero.getPosX() - monster.getPosX()) <= 2){
                if (abs(hero.getPosY() - monster.getPosY() <= 2)){
                    return true;
                }
        }
        return false;
    }

    void fight(Hero &hero, Monster &monster){
        //insert fight mechanism here
    }
public:
    Game(int sizeY, int sizeX){
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        for(int i = 0; i < sizeY; ++i){
            for(int j = 0; j < sizeX; ++j){
                line.push_back('_');
            }
            field.push_back(line);
        }
        monsters = {{10, 3, 3, '1'},
                    {15, 4, 4, '2'},
                    {20, 5, 5, '3'},
                    {25, 6, 6, '4'},
                    {30, 7, 7, '5'}};
    }

    void putMonstersOnMap(){
        for (int i = 0; i < sizeY; ++i){
            for(int j = 0; j < sizeX; ++j){
                field[i][j] = '_';
            }
        }
        for (int i = 0; i < numberOfMonsters; ++i){
            int x = monsters[i].getPosX();
            int y = monsters[i].getPosY();
            field[y][x] = monsters[i].getLevel();
        }
    }

    void monsterMovement(){
        for (int i = 0; i < numberOfMonsters; ++i){
            monsters[i].moving();
        }
    }

    void putHeroOnMap(Hero &hero){
        int x = hero.getPosX();
        int y = hero.getPosY();
        field[y][x] = 'X';
    }

    void gameDrawer(){
        for (int i = 0; i < sizeY; ++i){
            for (int j = 0; j < sizeX; ++j){
                cout << field[i][j];
            }
            cout << endl;
        }
    }

    void possibleFights(Hero &hero){
         for (int i = 0; i < numberOfMonsters; ++i){
            if (areTheyClose(hero, monsters[i]))
                fight(hero, monsters[i]);
         }
    }
};


int main()
{
    srand(time(NULL));
    Hero hero("Sanyi", 13, 4, 4, '1');
    Game game(numberOfRows, numberOfColumns);

    char command = '0';
    while (command != 'e'){
        game.monsterMovement();
        game.putMonstersOnMap();
        game.putHeroOnMap(hero);
        system("cls");
        game.gameDrawer();
        hero.printDetails();
        command = getch();
        hero.step(command);
    }
    return 0;
}
// next thing: fight mechanism and monster vector decrease when a monster dies
