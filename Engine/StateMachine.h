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
};

class State
{
public:
	std::string stateName;
	std::vector<Transition> transitions;
	void OnEnter();
	void OnExit();
};

class StateMachine
{
public:
	std::vector<State> states;
	//std::vector<Transition> transitions;
	State* currentStatePtr = nullptr; // memory address of the current state
	std::deque<std::string> stateHistory; // fixed-size historty of state names
	State* initialState = nullptr;

	StateMachine(size_t historySize = 10) : maxHistory(historySize) {}

	void OnEventStringReceived(const std::string& eventStr);
	std::string GetPreviousStateName();
private:
	size_t maxHistory;
	void AddToHistory(const std::string& stateName);

};
void StateMachine::OnEventStringReceived(const std::string& eventStr)
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

					//out with the old
					AddToHistory(currentStatePtr->stateName);
					currentStatePtr->OnExit();  
					// moved ^^this to inside the if block
					// it seemed more appropriate to exercise
					// the enter/exit machinery once all the
					// conditions are satisfied.

					// in with the new
					currentStatePtr = &state;
					currentStatePtr->OnEnter();
					return;
				}
			}
			std::cerr << "Target state: " << transition.toStateName << " not found\n";
			return;
		}
	}
	// transition not allowed from this state.
	// (I'm not sure if this will always be an error condition.
	// for example if the current state is "airborne", and a 
	// "walk" input is received, that's not an error, it's just a 
	// disallowed transition.)
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
	// pop off an event with the ^^StateEvent payload
	// how do C++ events work?
}
void State::OnExit()
{
	StateEvent exitEvent { EnumStateEvents::STATE_EXITED, stateName };
	// pop off an event with the ^^StateEvent payload
}

