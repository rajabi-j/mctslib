#include <limits>
#include <type_traits>
#include "util/empty.h"

#pragma once
namespace mctslib {

struct MCTSStats {
    double evaluation;
    double backprop_value;
    uint visits;
    [[no_unique_address]] Empty action;

    MCTSStats() = default;

    MCTSStats(double eval)
        : visits(0)
        , evaluation(eval)
        , backprop_value(0)
    {
    }

    double avg_value() const
    {

        return visits ? backprop_value / visits : std::numeric_limits<double>::min();
    }
};

}
