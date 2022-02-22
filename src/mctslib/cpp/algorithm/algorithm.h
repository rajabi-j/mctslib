
#pragma once

namespace mctslib {
template <
    class _Body,
    class Move,
    class Rollout,
    class Select,
    class UCT,
    class Expand,
    class Simulate,
    class Backpropagate>
class Algorithm {
public:
    using Body = _Body;
    using Node = typename Body::Node;
    using NodeStats = typename Body::NodeStats;
    using Settings = typename Body::Settings;

    Body body;
    Move move;
    Rollout rollout;
    Select select;
    UCT uct;
    Expand expand;
    Simulate simulate;
    Backpropagate backpropagate;

    template <typename... Args>
    Algorithm(Node* root, Args... args)
        : body(root, args...)
    {
    }
};
}