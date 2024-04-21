#ifndef STDRANDOM_H
#define STDRANDOM_H

/******************************************************************************
 *  Compilation:  javac StdRandom.java
 *  Execution:    java StdRandom
 *  Dependencies: StdOut.java
 *
 *  A library of methods to generate pseudo-random numbers from
 *  different distributions (bernoulli, uniform, gaussian, discrete,
 *  and exponential). Also includes a method for shuffling an array.
 *
 *
 *  %  java StdRandom 5
 *  seed = 1316600602069
 *  59 16.81826  true 8.83954  0
 *  32 91.32098  true 9.11026  0
 *  35 10.11874  true 8.95396  3
 *  92 32.88401  true 8.87089  0
 *  72 92.55791  true 9.46241  0
 *
 *  % java StdRandom 5
 *  seed = 1316600616575
 *  96 60.17070  true 8.72821  0
 *  79 32.01607  true 8.58159  0
 *  81 59.49065  true 9.10423  1
 *  96 51.65818  true 9.02102  0
 *  99 17.55771  true 8.99762  0
 *
 *  % java StdRandom 5 1316600616575
 *  seed = 1316600616575
 *  96 60.17070  true 8.72821  0
 *  79 32.01607  true 8.58159  0
 *  81 59.49065  true 9.10423  1
 *  96 51.65818  true 9.02102  0
 *  99 17.55771  true 8.99762  0
 *
 *
 *  Remark
 *  ------
 *    - Relies on randomness of nextDouble() method in java.util.Random
 *      to generate pseudo-random numbers in [0, 1).
 *
 *    - This library allows you to set and get the pseudo-random number seed.
 *
 *    - See http://www.honeylocust.com/RngPack/ for an industrial
 *      strength random number generator in Java.
 *
 ******************************************************************************/

/**
 *  The {@code StdRandom} class provides methods for generating
 *  random number from various discrete and continuous distributions,
 *  including uniform, Bernoulli, geometric, Gaussian, exponential, Pareto,
 *  Poisson, and Cauchy. It also provides method for shuffling an
 *  array or subarray and generating random permutations.
 *
 *  <p><b>Conventions.</b>
 *  By convention, all intervals are half open. For example,
 *  <code>uniformDouble(-1.0, 1.0)</code> returns a random number between
 *  <code>-1.0</code> (inclusive) and <code>1.0</code> (exclusive).
 *  Similarly, <code>shuffle(a, lo, hi)</code> shuffles the <code>hi - lo</code>
 *  elements in the array <code>a[]</code>, starting at index <code>lo</code>
 *  (inclusive) and ending at index <code>hi</code> (exclusive).
 *
 *  <p><b>Performance.</b>
 *  The methods all take constant expected time, except those that involve arrays.
 *  The <em>shuffle</em> method takes time linear in the subarray to be shuffled;
 *  the <em>discrete</em> methods take time linear in the length of the argument
 *  array.
 *
 *  <p><b>Additional information.</b>
 *  For additional documentation,
 *  see <a href="https://introcs.cs.princeton.edu/22library">Section 2.2</a> of
 *  <i>Computer Science: An Interdisciplinary Approach</i>
 *  by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
namespace StdRandom
{
    /**
     * Sets the seed of the pseudo-random number generator.
     * This method enables you to produce the same sequence of "random"
     * number for each execution of the program.
     * Ordinarily, you should call this method at most once per program.
     *
     * @param s the seed
     */
    void setSeed(long s);

    /**
     * Returns the seed of the pseudo-random number generator.
     *
     * @return the seed
     */
    long getSeed();

    /**
     * Returns a random real number uniformly in [0, 1).
     *
     * @return a random real number uniformly in [0, 1)
     */
    double uniformDouble();
    /**
     * Returns a random integer uniformly in [0, n).
     *
     * @param n number of possible integers
     * @return a random integer uniformly between 0 (inclusive) and {@code n} (exclusive)
     * @throws IllegalArgumentException if {@code n <= 0}
     */
    int uniformInt(int n);

    /**
     * Returns a random long integer uniformly in [0, n).
     *
     * @param n number of possible {@code long} integers
     * @return a random long integer uniformly between 0 (inclusive) and {@code n} (exclusive)
     * @throws IllegalArgumentException if {@code n <= 0}
     */
    long uniformLong(long n);

    ///////////////////////////////////////////////////////////////////////////
    //  METHODS BELOW RELY ON JAVA.UTIL.RANDOM ONLY INDIRECTLY VIA
    //  THE METHODS ABOVE.
    ///////////////////////////////////////////////////////////////////////////

    /**
     * Returns a random integer uniformly in [a, b).
     *
     * @param  a the left endpoint
     * @param  b the right endpoint
     * @return a random integer uniformly in [a, b)
     * @throws IllegalArgumentException if {@code b <= a}
     * @throws IllegalArgumentException if {@code b - a >= Integer.MAX_VALUE}
     */
    int uniformInt(int a, int b);

    /**
     * Returns a random real number uniformly in [a, b).
     *
     * @param  a the left endpoint
     * @param  b the right endpoint
     * @return a random real number uniformly in [a, b)
     * @throws IllegalArgumentException unless {@code a < b}
     */
    double uniformDouble(double a, double b);

    /**
     * Returns a random bool from a Bernoulli distribution with success
     * probability <em>p</em>.
     *
     * @param  p the probability of returning {@code true}
     * @return {@code true} with probability {@code p} and
     *         {@code false} with probability {@code 1 - p}
     * @throws IllegalArgumentException unless {@code 0} &le; {@code p} &le; {@code 1.0}
     */
    bool bernoulli(double p);

    /**
     * Returns a random bool from a Bernoulli distribution with success
     * probability 1/2.
     *
     * @return {@code true} with probability 1/2 and
     *         {@code false} with probability 1/2
     */
    bool bernoulli();

    /**
     * Returns a random real number from a standard Gaussian distribution.
     *
     * @return a random real number from a standard Gaussian distribution
     *         (mean 0 and standard deviation 1).
     */
    double gaussian();
    /**
     * Returns a random real number from a Gaussian distribution with mean &mu;
     * and standard deviation &sigma;.
     *
     * @param  mu the mean
     * @param  sigma the standard deviation
     * @return a real number distributed according to the Gaussian distribution
     *         with mean {@code mu} and standard deviation {@code sigma}
     */
    double gaussian(double mu, double sigma);

    /**
     * Returns a random integer from a geometric distribution with success
     * probability <em>p</em>.
     * The integer represents the number of independent trials
     * before the first success.
     *
     * @param  p the parameter of the geometric distribution
     * @return a random integer from a geometric distribution with success
     *         probability {@code p}; or {@code Integer.MAX_VALUE} if
     *         {@code p} is (nearly) equal to {@code 1.0}.
     * @throws IllegalArgumentException unless {@code p >= 0.0} and {@code p <= 1.0}
     */
    int geometric(double p);

    /**
     * Returns a random integer from a Poisson distribution with mean &lambda;.
     *
     * @param  lambda the mean of the Poisson distribution
     * @return a random integer from a Poisson distribution with mean {@code lambda}
     * @throws IllegalArgumentException unless {@code lambda > 0.0} and not infinite
     */
    int poisson(double lambda);

    /**
     * Returns a random real number from the standard Pareto distribution.
     *
     * @return a random real number from the standard Pareto distribution
     */
    double pareto();

    /**
     * Returns a random real number from a Pareto distribution with
     * shape parameter &alpha;.
     *
     * @param  alpha shape parameter
     * @return a random real number from a Pareto distribution with shape
     *         parameter {@code alpha}
     * @throws IllegalArgumentException unless {@code alpha > 0.0}
     */
    double pareto(double alpha);

    /**
     * Returns a random real number from the Cauchy distribution.
     *
     * @return a random real number from the Cauchy distribution.
     */
    double cauchy();

    /**
     * Returns a random integer from the specified discrete distribution.
     *
     * @param  probabilities the probability of occurrence of each integer
     * @return a random integer from a discrete distribution:
     *         {@code i} with probability {@code probabilities[i]}
     * @throws IllegalArgumentException if {@code probabilities} is {@code null}
     * @throws IllegalArgumentException if sum of array entries is not (very nearly) equal to {@code 1.0}
     * @throws IllegalArgumentException unless {@code probabilities[i] >= 0.0} for each index {@code i}
     */
    int discrete(std::vector<double>& probabilities);

    /**
     * Returns a random integer from the specified discrete distribution.
     *
     * @param  frequencies the frequency of occurrence of each integer
     * @return a random integer from a discrete distribution:
     *         {@code i} with probability proportional to {@code frequencies[i]}
     * @throws IllegalArgumentException if {@code frequencies} is {@code null}
     * @throws IllegalArgumentException if all array entries are {@code 0}
     * @throws IllegalArgumentException if {@code frequencies[i]} is negative for any index {@code i}
     * @throws IllegalArgumentException if sum of frequencies exceeds {@code Integer.MAX_VALUE} (2<sup>31</sup> - 1)
     */
    int discrete(std::vector<int>& frequencies);

    /**
     * Returns a random real number from an exponential distribution
     * with rate &lambda;.
     *
     * @param  lambda the rate of the exponential distribution
     * @return a random real number from an exponential distribution with
     *         rate {@code lambda}
     * @throws IllegalArgumentException unless {@code lambda > 0.0}
     */
    double exponential(double lambda);

    /**
     * Rearranges the elements of the specified array in uniformly random order.
     *
     * @param  a the array to shuffle
     * @throws IllegalArgumentException if {@code a} is {@code null}
     */
    template <typename T>
    void shuffle(std::vector<T>& a)
    {
        int n = a.size();
        for (int i = 0; i < n; i++)
        {
            int r = i + uniformInt(n-i);     // between i and n-1
            T temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
    }

    /**
     * Rearranges the elements of the specified subarray in uniformly random order.
     *
     * @param  a the array to shuffle
     * @param  lo the left endpoint (inclusive)
     * @param  hi the right endpoint (exclusive)
     * @throws IllegalArgumentException if {@code a} is {@code null}
     * @throws IllegalArgumentException unless {@code (0 <= lo) && (lo < hi) && (hi <= a.length)}
     *
     */
    template <typename T>
    void shuffle(std::vector<T>& a, int lo, int hi)
    {
        validateSubarrayIndices(lo, hi, a.size());

        for (int i = lo; i < hi; i++)
        {
            int r = i + uniformInt(hi-i);     // between i and hi-1
            T temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
    }

    /**
     * Returns a uniformly random permutation of <em>n</em> elements.
     *
     * @param  n number of elements
     * @throws IllegalArgumentException if {@code n} is negative
     * @return an array of length {@code n} that is a uniformly random permutation
     *         of {@code 0}, {@code 1}, ..., {@code n-1}
     */
    std::vector<int> permutation(int n);

    /**
     * Returns a uniformly random permutation of <em>k</em> of <em>n</em> elements.
     *
     * @param  n number of elements
     * @param  k number of elements to select
     * @throws IllegalArgumentException if {@code n} is negative
     * @throws IllegalArgumentException unless {@code 0 <= k <= n}
     * @return an array of length {@code k} that is a uniformly random permutation
     *         of {@code k} of the elements from {@code 0}, {@code 1}, ..., {@code n-1}
     */
    std::vector<int> permutation(int n, int k);
}

/******************************************************************************
 *  Copyright 2002-2022, Robert Sedgewick and Kevin Wayne.
 *
 *  This file is part of algs4.jar, which accompanies the textbook
 *
 *      Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne,
 *      Addison-Wesley Professional, 2011, ISBN 0-321-57351-X.
 *      http://algs4.cs.princeton.edu
 *
 *
 *  algs4.jar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  algs4.jar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with algs4.jar.  If not, see http://www.gnu.org/licenses.
 ******************************************************************************/

#endif