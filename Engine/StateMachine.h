////////////////////
// StateMachine.h //
////////////////////

#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <deque>

class State;
class Transition;

enum EnumStateEvents
{
	STATE_ENTERED,
	STATE_EXITED
};

struct StateEvent
{
	EnumStateEvents eventType;
	std::string stateName;
};

class Transition
{
public:
	std::string transitionName;
	std::string eventString;   // The event that triggers this transition
	std::string toStateName;
	Transition(
		std::string name, std::string event, std::string to
	) : transitionName(std::move(name)), eventString(std::move(event)), toStateName(std::move(to)) { }
};

class State
{
public:
	std::string stateName;
	std::vector<Transition> transitions;

	State(std::string _stateName) : stateName(_stateName) {};

	void OnEnter();
	void OnExit();
};

class StateMachine
{
public:
	std::vector<State> states;
	State* initialStatePtr = nullptr;
	State* currentStatePtr = nullptr; // memory address of the current state
	std::deque<std::string> stateHistory; // fixed-size historty of state names
	

	StateMachine(size_t historySize = 10) : maxHistory(historySize) {}
	void SendEvent(const std::string& eventStr);
	std::string GetPreviousStateName();
	void Initialize();
private:
	size_t maxHistory;
	void AddToHistory(const std::string& stateName);

};
void StateMachine::Initialize()
{
	currentStatePtr = initialStatePtr;
	if (currentStatePtr != nullptr) {
		currentStatePtr->OnEnter();
	}
}
void StateMachine::SendEvent(const std::string& eventStr)
{
	if (currentStatePtr == nullptr) {
		std::cerr << "No current state\n";
		return;
	}
	for (auto& transition : currentStatePtr->transitions)
	{
		if (transition.eventString == eventStr) {
			// look up the new state by name
			for (auto& state : states) {
				if (state.stateName == transition.toStateName) {
					AddToHistory(currentStatePtr->stateName);
					currentStatePtr->OnExit();  
					currentStatePtr = &state;
					currentStatePtr->OnEnter();
					std::cout << "Current state:" << currentStatePtr->stateName << "\n";
					return;
				}
			}
			std::cerr << "Target state: " << transition.toStateName << " not found\n";
			return;
		}
	}
	std::cerr << "No transition from '" << currentStatePtr->stateName << "' on event '" << eventStr << "'.\n";
}
void StateMachine::AddToHistory(const std::string& stateName)
{
	if (stateHistory.size() >= maxHistory) {
		stateHistory.pop_front();
	}
	stateHistory.push_back(stateName);
}
std::string StateMachine::GetPreviousStateName()
{
	if (stateHistory.empty()) return {};
	return stateHistory.back();
}

void State::OnEnter()
{
	StateEvent enterEvent { EnumStateEvents::STATE_ENTERED, stateName };
	std::cout << "Entering state: " << stateName << "\n";
	// pop off an event with the ^^StateEvent payload
}
void State::OnExit()
{
	StateEvent exitEvent { EnumStateEvents::STATE_EXITED, stateName };
	std::cout << "Exiting state: " << stateName << "\n";
	// pop off an event with the ^^StateEvent payload
}