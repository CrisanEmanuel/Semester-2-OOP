#pragma once
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
private:
    /*Non owning pointers to observer instances*/
    std::vector<Observer*> observers;
public:
    void addObserver(Observer *obs) {
        observers.push_back(obs);
    }
    void removeObserver(Observer *obs) {
        observers.erase(std::remove(observers.begin(), observers.end(),obs), observers.end());
    }
protected:
    void notify() {
        for (auto obs : observers) {
            obs->update();
        }
    }
};
