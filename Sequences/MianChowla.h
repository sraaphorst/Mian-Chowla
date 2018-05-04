/*
 * MianChowla.h
 * 
 * A basic, index-based implementation of the Mian-Chowla sequence, i.e.
 * the B2 sequence of integers 1, 2, 4, 8, etc. such that every pair of terms
 * has a distinct difference.
 * 
 * By Sebastian Raaphorst, 2018.
 */

#ifndef MIANCHOWLA_H
#define MIANCHOWLA_H

#include <optional>
#include <set>
#include <tuple>
#include <vector>

namespace vorpal::math {

    class MianChowla {
    private:
        std::vector<unsigned long> terms;
        std::set<unsigned long> differences;

        std::pair<const unsigned long, const std::set<unsigned long> > nextTerm();
        void ensureCalculatedTo(const unsigned int);

    public:
        MianChowla();
        virtual ~MianChowla();

        // All of these work on term INDEX and not on actual terms themselves.
        // Thus, getTerm(0) gets the first term, getTerm(1) the second, etc.
        const unsigned long getTerm(const unsigned int);
        const std::vector<unsigned long> getTermsTo(const unsigned int);
        const unsigned long getLastTerm();

        // Returns all the terms calculated so far.
        const std::vector<unsigned long> getTerms();

        // Note that this will return all differences calculated up to the
        // current term.
        const std::set<unsigned long> getDifferences();

        // This will return all differences calculated up to the specified term.
        // Computationally intensive, as it has to recalculate all differences and
        // then insert them into a set. Do not use unless necessary.
        const std::set<unsigned long> getDifferencesTo(const unsigned int);

        // This will return all the differences for the specified term
        // for terms lower in value.
        const std::set<unsigned long> getDifferencesForTerm(const unsigned int);

        // Try to find the term that generates the difference d, i.e. a term t
        // such that t - d is also a term. Since not every term might occur,
        // we provide a "maxout" option, which will stop trying when t reaches
        // maxout. A value of 0 indicates to continue forever.
        // The return value is t, or 0 if maxout was reached and no term was found.
        const unsigned long findDifference(const unsigned long, const unsigned int = 0);
    };
};
#endif /* MIANCHOWLA_H */

