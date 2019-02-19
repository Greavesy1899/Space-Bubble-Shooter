#ifndef TIMER_H
#define TIMER_H
// written by oszymanezyk@lincoln.ac.uk
// part of games programming module
// CG: improved slightly.
namespace EngineOpenGL
{
	class SZ_Timer
	{
	private:
		int startTicks; // SDL time when the timer started
		bool isRunning;
	public:
		SZ_Timer();
		//SDL timer stuff
		void resetTicksTimer(); // resets timer to zero
		int getTicks() const; // returns how much time has passed since timer has been reset
		bool IsRunning() const;
		void StopTimer();
	};
}
#endif