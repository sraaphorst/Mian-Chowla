/*
 * MianChowla.cpp
 * 
 * By Sebastian Raaphorst, 2018.
 */

#include <algorithm>
#include <exception>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

#include "MianChowla.h"

namespace vorpal::math {
    using namespace std;

    MianChowla::MianChowla() {
    }

    MianChowla::~MianChowla() {
    }

    pair<const unsigned long, const std::set<unsigned long> > MianChowla::nextTerm() {
        auto i = terms.empty() ? 1UL : terms.back() + 1UL;
        set<unsigned long> diffsForI;

        for (;; ++i) {
            // Check all the differences with previous terms and continue
            // if any of them already exist, i.e. i is in the "clear."
            auto clear = true;
            for (auto j : terms) {
                if (differences.find(i - j) != differences.end()) {
                    clear = false;
                    break;
                }
            }

            if (clear) {
                for (auto j : terms) {
                    auto d = i - j;
                    diffsForI.insert(d);
                    differences.insert(d);
                }
                terms.insert(terms.end(), i);
                break;
            } else
                continue;
        }

        return make_pair(i, diffsForI);
    }

    void MianChowla::ensureCalculatedTo(const unsigned int term) {
        for (auto i = terms.size(); i <= term; ++i)
            nextTerm();
    }

    const unsigned long MianChowla::getTerm(const unsigned int term) {
        ensureCalculatedTo(term);
        return terms[term];
    }

    const vector<unsigned long> MianChowla::getTermsTo(const unsigned int term) {
        ensureCalculatedTo(term);
        std::vector<unsigned long> output;
        output.resize(term + 1);

        copy_n(terms.begin(), term + 1, output.begin());
        return output;
    }

    const unsigned long MianChowla::getLastTerm() {
        return terms.back();
    }

    const vector<unsigned long> MianChowla::getTerms() {
        return terms;
    }

    const set<unsigned long> MianChowla::getDifferences() {
        return differences;
    }

    const set<unsigned long> MianChowla::getDifferencesTo(const unsigned int term) {
        set<unsigned long> output;

        for (auto i = 1; i <= term; ++i) {
            auto diffsForI = getDifferencesForTerm(i);
            for (auto e : diffsForI)
                output.insert(e);
        }

        return output;
    }

    const set<unsigned long> MianChowla::getDifferencesForTerm(const unsigned int termNum) {
        ensureCalculatedTo(termNum);

        set<unsigned long> output;
        auto term = terms[termNum];
        for (auto i = 0; i < termNum; ++i)
            output.insert(term - terms[i]);
        return output;
    }

    const unsigned long MianChowla::findDifference(const unsigned long d, const unsigned int maxout) {
        auto numTerms = terms.size();

        // Two cases:
        // Case 1: the difference has already been found.
        if (differences.find(d) != differences.end()) {
            // Now we need to find which difference generated the term.
            for (auto i = 1; i <= numTerms && (i <= maxout || !maxout); ++i) {
                auto term = terms[i];
                auto diffsForTerm = getDifferencesForTerm(i);

                if (diffsForTerm.find(d) != diffsForTerm.end())
                    return term;
            }

            // If we reach this point, we couldn't find the difference.
            // If maxout wasn't reached, this is abnormal behaviour.
            if (!maxout)
                return 0;
            throw logic_error("Difference has been found, but could not locate term generating it.");
        }

        // Case 2: the difference has not been found yet.
        // Keep generating new terms until we find it.
        for (auto i = numTerms; i < maxout || !maxout; ++i) {
            auto result = nextTerm();
            auto term = result.first;
            auto diffs = result.second;

            if (diffs.find(d) != diffs.end())
                return term;
        }

        return 0;
    }
};