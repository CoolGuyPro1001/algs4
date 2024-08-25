#include "StdRandom.h"

/***************************************************************************
* Private Variables and Functions
***************************************************************************/

// pseudo-random number generator seed
static long seed = std::chrono::system_clock::now().time_since_epoch().count();

// pseudo-random number generator
static std::mt19937 rng = std::mt19937(seed);

// throw an exception unless 0 <= lo <= hi <= length
void validateSubarrayIndices(int lo, int hi, int length);

void validateSubarrayIndices(int lo, int hi, int length)
{
    if (lo < 0 || hi > length || lo > hi)
    {
        //TODO
        //error("subarray indices out of bounds: [" + lo + ", " + hi + ")");
    }
}


/***************************************************************************
* Public Functions
***************************************************************************/

void StdRandom::set_seed(long s)
{
    seed = s;
    rng = std::mt19937(seed);
}

long StdRandom::get_seed()
{
    return seed;
}

double StdRandom::uniform_double()
{
    std::uniform_real_distribution<double> dis(0, 1);
    return dis(rng);
}

int StdRandom::uniform_int(int n)
{
    //if (n <= 0) error("argument must be positive: " + n);
    std::uniform_int_distribution<int> dis(0, n - 1);
    return dis(rng);
}

long StdRandom::uniform_long(long n)
{
    //if (n <= 0L) error("argument must be positive: " + n);

    std::uniform_int_distribution<long> dis(0, n - 1);
    long r = dis(rng);
    long m = n - 1;

    // power of two
    if ((n & m) == 0L)
    {
        return r & m;
    }

    // reject over-represented candidates
    unsigned long u = r >> 1;
    while (u + m - (r = u % n) < 0L)
    {
        u = dis(rng) >> 1;
    }
    return r;
}

///////////////////////////////////////////////////////////////////////////
//  METHODS BELOW RELY ON STD::RANDOM ONLY INDIRECTL
//   HE METHODS ABOVE.
///////////////////////////////////////////////////////////////////////////

int StdRandom::uniform_int(int a, int b)
{
    if ((b <= a) || ((long) b - a >= INT_MAX))
    {
        //TODO
        //error("invalid range: [" + a + ", " + b + ")");
    }
    return a + uniform_int(b - a);
}

double StdRandom::uniform_double(double a, double b)
{
    if (!(a < b))
    {
        //TODO
        //error("invalid range: [" + a + ", " + b + ")");
    }
    return a + uniform_double() * (b-a);
}

bool StdRandom::bernoulli(double p)
{
    //if (!(p >= 0.0 && p <= 1.0))
        //TODO error("probability p must be between 0.0 and 1.0: " + p);
    return uniform_double() < p;
}

bool StdRandom::bernoulli()
{
    return bernoulli(0.5);
}

double StdRandom::gaussian()
{
    // use the polar form of the Box-Muller transform
    double r, x, y;
    do
    {
        x = uniform_double(-1.0, 1.0);
        y = uniform_double(-1.0, 1.0);
        r = x*x + y*y;
    } while (r >= 1 || r == 0);
    return x * std::sqrt(-2 * std::log(r) / r);

    // Remark:  y * std::sqrt(-2 * std::log(r) / r)
    // is an independent random gaussian
}

double StdRandom::gaussian(double mu, double sigma)
{
    return mu + sigma * gaussian();
}

int StdRandom::geometric(double p)
{
    if (!(p >= 0))
    {
        // TODO error("probability p must be greater than 0: " + p);
    }
    if (!(p <= 1.0))
    {
        // TODO error("probability p must not be larger than 1: " + p);
    }
    // using algorithm given by Knuth
    return (int) std::ceil(std::log(uniform_double()) / std::log(1.0 - p));
}

int StdRandom::poisson(double lambda)
{
    //if (!(lambda > 0.0))
        //TODO error("lambda must be positive: " + lambda);
    //if (lambda == infinity)
        //TODO error("lambda must not be infinite: " + lambda);
    // using algorithm given by Knuth
    // see http://en.wikipedia.org/wiki/Poisson_distribution
    int k = 0;
    double p = 1.0;
    double expLambda = std::exp(-lambda);
    do
    {
        k++;
        p *= uniform_double();
    } while (p >= expLambda);
    return k-1;
}

double StdRandom::pareto(double alpha)
{
    //TODO
    //if (!(alpha > 0.0))
    //    error("alpha must be positive: " + alpha);
    return std::pow(1 - uniform_double(), -1.0 / alpha) - 1.0;
}

double StdRandom::pareto()
{
    return pareto(1.0);
}

double StdRandom::cauchy()
{
    return std::tan(pi() * (uniform_double() - 0.5));
}

int StdRandom::discrete(std::vector<double>& probabilities)
{
    double EPSILON = 1.0E-14;
    double sum = 0.0;
    for (int i = 0; i < probabilities.size(); i++)
    {
        //TODO
        //if (!(probabilities[i] >= 0.0))
        //    error("array entry " + i + " must be non-negative: " + probabilities[i]);
        sum += probabilities[i];
    }

    //TODO
    //if (sum > 1.0 + EPSILON || sum < 1.0 - EPSILON)
    //   error("sum of array entries does not approximately equal 1.0: " + sum);

    // the for loop may not return a value when both r is (nearly) 1.0 and when the
    // cumulative sum is less than 1.0 (as a result of floating-point roundoff error)
    while (true)
    {
        double r = uniform_double();
        sum = 0.0;
        for (int i = 0; i < size(probabilities); i++)
        {
            sum = sum + probabilities[i];
            if (sum > r) return i;
        }
    }
}

int StdRandom::discrete(std::vector<int>& frequencies)
{   
    long sum = 0;
    for (int i = 0; i < frequencies.size(); i++)
    {
        //TODO
        //if (frequencies[i] < 0)
        //    error("array entry " + i + " must be non-negative: " + frequencies[i]);
        sum += frequencies[i];
    }
    if (sum == 0)
        error("at least one array entry must be positive");
    if (sum >= INT_MAX)
        error("sum of frequencies overflows an int");

    // pick index i with probability proportional to frequency
    double r = uniform_int((int) sum);
    sum = 0;
    for (int i = 0; i < size(frequencies); i++)
    {
        sum += frequencies[i];
        if (sum > r) return i;
    }

    // can't reach here
    assert(false);
    return -1;
}

double StdRandom::exponential(double lambda)
{
    //TODO
    //if (!(lambda > 0.0))
    //    error("lambda must be positive: " + lambda);
    return -std::log(1 - uniform_double()) / lambda;
}

std::vector<int> StdRandom::permutation(int n)
{
    //if (n < 0) error("n must be non-negative: " + n);
    std::vector<int> perm = std::vector<int>(n);
    for (int i = 0; i < n; i++)
        perm[i] = i;
    shuffle(perm);
    return perm;
}

std::vector<int> StdRandom::permutation(int n, int k)
{
    //if (n < 0) error("n must be non-negative: " + n);
    //if (k < 0 || k > n) error("k must be between 0 and n: " + k);
    std::vector<int> perm = std::vector<int>(k);
    for (int i = 0; i < k; i++)
    {
        int r = uniform_int(i+1);    // between 0 and i
        perm[i] = perm[r];
        perm[r] = i;
    }
    for (int i = k; i < n; i++)
    {
        int r = uniform_int(i+1);    // between 0 and i
        if (r < k) perm[r] = i;
    }
    return perm;
}