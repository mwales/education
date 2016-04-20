#pragma once

#include <string>
#include <fstream>

union SDL_Event;

typedef int (*WaitEventFuncType)(SDL_Event*,int);

/**
 * Records and plays back SDL events.
 *
 * Want main game event reader to get a function pointer from us for getting events from SDL:
 *  * Use regular SDL event poll
 *  * Use custom getEvent to call SDL event poll, and then record event to file before returning
 *  * Read event from file and return as if sent from SDL directly
 */
class EventRecorder
{
public:

   static EventRecorder* GetInstance();

   static void DestroyInstance();

   static EventRecorder* CreateInstance();

   void ParseArguments(int argc, char** argv);

   void SeedRandomNumberGenerator();

   void AdvanceFrame();

   void StoreEvent(SDL_Event* ev);

   WaitEventFuncType GetWaitEventFunction();

   static int WaitEventTimeoutRecordEvent(SDL_Event* event, int timeout);

   static int WaitEventTimeoutReplayEvent(SDL_Event* event, int timeout);

protected:

   enum class RecorderState
   {
      IDLE,
      RECORDING,
      PLAYBACK
   };

   EventRecorder();

   ~EventRecorder();

   static EventRecorder* theInstance;

   RecorderState theState;

   std::string theFilename;

   bool theSpeedupFlag;

   std::fstream theDataFile;
};

