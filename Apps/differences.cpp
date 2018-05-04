/*
 * differences.cpp
 * 
 * Look for the terms that generate the differences in the Mian-Chowla sequence.
 * 
 * By Sebastian Raaphorst, 2018.
 */

#include <iostream>
#include "MianChowla.h"
using namespace std;
using namespace vorpal::math;

/**
 * Questions of interest and tasks:
 * 1. What if we allow 2-coverage of differences? n-coverage?
 * 2. Generalize the idea of a B_2 sequence to a superclass as best as possible.
 * 3. Implement prohibited differences and prohibited terms.
 *    We already know prohibiting all [1,x] terms shifts the sequence
 *    by x exclusively.
 * 4. How does the percentage of differences not found for some upper bound U(x)
 *    vary with x, the number of terms generated? What is a good U(x)?
 *    We could use U(x) = maximum term - 1, since that difference is the largest
 *    guaranteed to appear.
 */
int main(int argc, char* argv[]) {
    // Try to find all the differences. Stop after a certain number of
    // simultaneous fails, assuming that that means that we have gone
    // beyond what maxout allows.
    MianChowla mc;
    auto maxout = 1000U;
    auto numfails = 0;
    auto maxfails = 1000;
    
    for (auto d = 1UL;; ++d) {
        auto term = mc.findDifference(d, maxout);
        if (!term) {
            cout << "Could not find difference " << d
                << " within sequence to " << mc.getLastTerm() << endl;
            ++numfails;
        }
        else {
            cout << d << " = " << term << " - " << (term - d) << endl;
            numfails = 0;
        }
        
        if (numfails >= maxfails)
            break;
    }
    return 0;
}
