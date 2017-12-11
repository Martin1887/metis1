#ifndef STRUCTURAL_SYMMETRIES_PERMUTATION_H
#define STRUCTURAL_SYMMETRIES_PERMUTATION_H

#include <vector>
#include <memory>

#include "group.h"

class GlobalState;

class Permutation{
public:
    Permutation(const Group* group);
    explicit Permutation(const Group* group, const unsigned int *full_perm);
    Permutation(const Permutation &perm, bool invert=false);
    Permutation(const Permutation &perm1, const Permutation &perm2);
    ~Permutation();

    bool identity() const;
    void print_cycle_notation() const;
    void print_affected_variables_by_cycles() const;
    int get_value(int ind) const {
        return value[ind];
    }
    void dump_var_vals() const;
    void dump() const;
    void dump_fdr() const;

    int get_order() const {
        return order;
    }

    std::pair<int, int> get_new_var_val_by_old_var_val(const int var, const int val) const;

    bool replace_if_less(int*) const;
    const std::vector<int>& get_affected_vars() const { 
        return vars_affected; 
    }
private:
    const Group* group;
    int* value;
    std::vector<int> vars_affected;
    std::vector<bool> affected;

    // Need to keep the connection between affected vars, ie which var goes into which.
    std::vector<int> from_vars;
    // Affected vars by cycles
    std::vector<std::vector<int> > affected_vars_cycles;
    int order;

    void set_value(int ind, int val);
    void set_affected(int ind, int val);

    void finalize();
    void _allocate();
    void _deallocate();
    void _copy_value_from_permutation(const Permutation &perm);
    void _inverse_value_from_permutation(const Permutation &perm);
};

#endif
