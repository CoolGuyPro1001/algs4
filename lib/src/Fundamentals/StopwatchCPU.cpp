#include "StopwatchCPU.h"

/**
 * Initializes a new stopwatch.
 */
StopwatchCPU::StopwatchCPU()
{
   m_start = std::clock(); 
}

/**
 * Returns the elapsed CPU time (in seconds) since the stopwatch was created.
 *
 * @return elapsed CPU time (in seconds) since the stopwatch was created
 */
double StopwatchCPU::elapsed_time() const
{
    std::clock_t now = std::clock();
    return (double) (now - m_start) / CLOCKS_PER_SEC;
}