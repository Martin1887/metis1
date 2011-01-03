#ifndef MAX_HEURISTIC_H
#define MAX_HEURISTIC_H

#include "priority_queue.h"
#include "relaxation_heuristic.h"
#include <cassert>

class HSPMaxHeuristic : public RelaxationHeuristic {
    AdaptiveQueue<Proposition *> queue;

    void setup_exploration_queue();
    void setup_exploration_queue_state(const State &state);
    void relaxed_exploration();

    void enqueue_if_necessary(Proposition *prop, int cost) {
        assert(cost >= 0);
        if (prop->h_max_cost == -1 || prop->h_max_cost > cost) {
            prop->h_max_cost = cost;
            queue.push(cost, prop);
        }
        assert(prop->h_max_cost != -1 && prop->h_max_cost <= cost);
    }
protected:
    virtual void initialize();
    virtual int compute_heuristic(const State &state);
public:
    HSPMaxHeuristic(const HeuristicOptions &options);
    ~HSPMaxHeuristic();

    static ScalarEvaluator *create(const std::vector<std::string> &config,
                                   int start, int &end, bool dry_run);
};

#endif
