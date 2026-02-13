// TestLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vec3.h"
#include "Vec3OpsTest.h"
#include "StateMachine.h"




int main()
{
    Transition toSleeping { "TO_SLEEPING", "TO_SLEEPING_EVENT", "SLEEPING" };
    Transition toShowering { "TO_SHOWERING", "TO_SHOWERING_EVENT", "SHOWERING" };
    Transition toWorking { "TO_SHOWERING", "TO_WORKING_EVENT", "WORKING" };
    Transition toPlayingVideogames { "TO_PLAYING_VIDEO_GAMES", "TO_PLAYING_VIDEO_GAMES_EVENT", "PLAYING_VIDEO_GAMES" };
    Transition toRunningErrands{ "TO_RUNNING_ERRANDS", "TO_RUNNING_ERRANDS_EVENT", "RUNNING_ERRANDS" };

    State sleeping{ "SLEEPING" };
    sleeping.transitions.push_back(toShowering);

    State showering{ "SHOWERING" };
    showering.transitions.push_back(toWorking);
    showering.transitions.push_back(toPlayingVideogames);

    State working{ "WORKING" };
    working.transitions.push_back(toPlayingVideogames);
    working.transitions.push_back(toRunningErrands);
    working.transitions.push_back(toSleeping);

    State playingVideogames{ "PLAYING_VIDEO_GAMES" };
    playingVideogames.transitions.push_back(toWorking);
    playingVideogames.transitions.push_back(toRunningErrands);
    playingVideogames.transitions.push_back(toSleeping);

    State runningErrands{ "RUNNING_ERRANDS" };
    runningErrands.transitions.push_back(toWorking);
    runningErrands.transitions.push_back(toPlayingVideogames);

    StateMachine bradsDaySM = StateMachine(3);
    bradsDaySM.states.push_back(sleeping);
    bradsDaySM.states.push_back(showering);
    bradsDaySM.states.push_back(working);
    bradsDaySM.states.push_back(playingVideogames);
    bradsDaySM.states.push_back(runningErrands);
    bradsDaySM.initialStatePtr = &bradsDaySM.states[0];
    bradsDaySM.Initialize();

    bradsDaySM.SendEvent(toShowering.eventString);
    bradsDaySM.SendEvent(toWorking.eventString);
    bradsDaySM.SendEvent(toRunningErrands.eventString);
    bradsDaySM.SendEvent(toWorking.eventString);
    bradsDaySM.SendEvent(toPlayingVideogames.eventString);
    bradsDaySM.SendEvent(toSleeping.eventString);

}