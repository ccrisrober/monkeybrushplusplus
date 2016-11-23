class Timer {
	// Starts tracking time from moment this function is called.
	void start();
	/* Calculates the delta time between this tick and the last tick,
     * or the last reset, depending on which happened more recently.
     * Also recalculates the total time by accruing the calculated delta
     * time into the total time.*/
	void tick();
	// Stops tracking timing information
	void stop();
	/* If timer is currently running, delta time will be calculated between
     * the tick this function is called and the tick that Tick() is called.*/
	void reset();
	// Returns elapsed time (in seconds) between Start() and Stop() calls.
	float elapsedTime();
	// Returns total time between when timer was started and last tick.
	float totalTime();
	// Returns delta time (in seconds) between last two ticks of timer.
	float deltaTime();
}