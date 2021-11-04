/*
 * - This code demonstrate the "Strategy pattern"
 * - In the code below, the travel strategy can be
 *   changed dynamically based on travelling time
 *   or budget.
 * - Code's intention just to show the pattern behavior
 *   the other issues like virtual destructor or
 *   de-allocating memory would not be considered
 */

#include <iostream>

class ITravelStrategy{
public:
  virtual void travel() = 0;
};

class CBikeTravel : public ITravelStrategy {
public:
  virtual void travel() override {
    std::cout << "Travel by BIKE" << '\n';;
  }
};
class CBusTravel : public ITravelStrategy {
public:
  virtual void travel() override {
    std::cout << "Travel by BUS" << '\n';;
  }
};
class CPlanTravel : public ITravelStrategy {
public:
  virtual void travel() override {
    std::cout << "Travel by PLANE" << '\n';;
  }
};

enum class TIME {
  FAST,
  NORMAL,
  SLOW
};
enum class BUDGET {
  HIGH,
  NORMAL,
  LOW
};

class AdaptiveTraveller {
  ITravelStrategy* travel_strategy_;
  
public:
  AdaptiveTraveller(TIME time) {
    if( time == TIME::FAST ) travel_strategy_ = new CPlanTravel();
    if( time == TIME::NORMAL ) travel_strategy_ = new CBusTravel();
    if( time == TIME::SLOW ) travel_strategy_ = new CBikeTravel();
  }
  
  AdaptiveTraveller(BUDGET budget) {
    if( budget == BUDGET::HIGH ) travel_strategy_ = new CPlanTravel();
    if( budget == BUDGET::NORMAL ) travel_strategy_ = new CBusTravel();
    if( budget == BUDGET::LOW ) travel_strategy_ = new CBikeTravel();
  }
  
  void change_strategy(ITravelStrategy* new_strategy) {
    delete travel_strategy_;
    travel_strategy_ = new_strategy;
  }
  
  void travel() {
    travel_strategy_->travel();
  }
};


int main() {
  AdaptiveTraveller traveller {TIME::FAST};
  traveller.change_strategy(new CBusTravel{});
  traveller.travel();
  
  AdaptiveTraveller low_budget_traveller {BUDGET::LOW};
  low_budget_traveller.travel();
  
  return 0;
}
