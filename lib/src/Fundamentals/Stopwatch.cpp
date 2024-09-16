#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
    m_start = std::chrono::high_resolution_clock::now();
}

double Stopwatch::elapsed_time() const
{
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(now - m_start);
    return time_span.count();
}