////////////////////
// StateMachine.h //
////////////////////

#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <deque>
#include <functional>
#include <typeindex>

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
};

class FsmEventSystem
{
	std::vector<std::function<void(const StateEvent&)>> listeners;
public:
	void AddListener(std::function< void(const StateEvent&)> cBack) {
		listeners.push_back(cBack);
	}
	void Dispatch(const StateEvent& event) {
		for (auto& cBack : listeners) {
			cBack(event);
		}
	}
};

class StateMachine
{
	FsmEventSystem events;

public:
	std::vector<State> states;
	State* initialStatePtr = nullptr;
	State* currentStatePtr = nullptr; // memory address of the current state
	std::deque<std::string> stateHistory; // fixed-size historty of state names

	// specify history size in constructor
	StateMachine(size_t historySize = 10) : maxHistory(historySize) {}
	
	std::string GetPreviousStateName();
	void SendEvent(const std::string& eventStr);
	void Initialize();
	void AddListener(std::function<void(const StateEvent&)> cBack) {
		events.AddListener(cBack);
	}

private:
	size_t maxHistory;

	void AddToHistory(const std::string& stateName);
	void NotifyStateEntered(const std::string& stateName) {
		events.Dispatch({ EnumStateEvents::STATE_ENTERED, stateName });
	}
	void NotifyStateExited(const std::string& stateName) {
		events.Dispatch({ EnumStateEvents::STATE_EXITED, stateName });
	}
};

void StateMachine::Initialize()
{
	currentStatePtr = initialStatePtr;
	if (currentStatePtr != nullptr) {
		NotifyStateEntered(currentStatePtr->stateName);
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

					// handle exit
					AddToHistory(currentStatePtr->stateName);
					NotifyStateExited(currentStatePtr->stateName);
					
					// handle enter
					currentStatePtr = &state;
					NotifyStateEntered(currentStatePtr->stateName);
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