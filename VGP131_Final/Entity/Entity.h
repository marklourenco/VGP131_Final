#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"

#include <iostream>
#include <vector>

using namespace std;

class Entity
{
private:
	vector<shared_ptr<Component>> components;
	int id;
	string name;
public:
	explicit Entity(string name) : name(move(name)) {
		static int next_id = 0;
		id = next_id++;
	}
	int getID() const {
		return id;
	}
	template <typename T>
	void addComponent(shared_ptr<T> component) {
		components.push_back(component);
	}
	void removeComponent(int comID) {
		for (int i = 0; i < components.size(); i++) {
			if (components[i]->getID() == comID) {
				components.erase(components.begin() + i);
				break;
			}
		}
	}
	template <typename T>
	std::shared_ptr<T> GetComponent() {
		for (auto& component : components) {
			if (auto casted = std::dynamic_pointer_cast<T>(component))
				return casted;
		}
		std::cout << "Entity '" << name << "' does not have a component of type '" << typeid(T).name() << "'" << std::endl;
		return nullptr;
	}
	void PrintEntity() {
		std::cout << "~ Entity: " << name << std::endl;
		for (auto& component : components)
			component->PrintComponent();
	}
	std::string getName() const {
		return name;
	}
};

#endif

