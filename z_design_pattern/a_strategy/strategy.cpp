/*
    When to use: When a object could perform an action in various ways.
    Real-world example: 
  1. A math exercise could have more than 1 solution.
  Every solution is interchanable each other, and can be changed at runtime.
  2. A game character can use many kinds of weapon, weapons are interchangable,
  it means that the character could use any kind of weapon and perform the attack
  action.
    Key words:
    - Context: Manages a reference to a concrete stategy, and interact with the strategy
    with a public interface, provided by the Strategy.
    - Strategy: Interface that provides a public interfaces to perform athe action.
    How to implement;


*/
#include <iostream>

struct Weapon{
  virtual int hit() const = 0;
};

struct Hand : public Weapon{
  virtual int hit() const override { return 1; }
};

struct RustySword : public Weapon{
  virtual int hit() const override { return 2; }
};

struct SharpSword : public Weapon{
  virtual int hit() const override { return 4; }
};

struct Character{
  Character(Weapon* w) : weapon(w){}
  Weapon* weapon;
  void setWeapon(Weapon* w){
    weapon = w;
  }

  void attack(int& HP){
    HP -= weapon->hit();
  }
};

int main(){
  int HP = 100;
  Character c{new Hand()};
  c.attack(HP);
  std::cout << "HP: " << HP << '\n';
  c.setWeapon(new RustySword());
  c.attack(HP);
  std::cout << "HP: " << HP << '\n';
  c.setWeapon(new SharpSword());
  c.attack(HP);
  std::cout << "HP: " << HP << '\n';
}