#include "relaxed_task_graph.h"

#include <iostream>
#include <vector>
#include "../task_utils/task_properties.h"


using namespace std;

namespace planopt_heuristics {
RelaxedTaskGraph::RelaxedTaskGraph(const TaskProxy &task_proxy)
    : relaxed_task(task_proxy),
      variable_node_ids(relaxed_task.propositions.size()) {
    /*
      TODO: add your code for exercise 2 (b) here. Afterwards
        - variable_node_ids[i] should contain the node id of the variable node for variable i
        - initial_node_id should contain the node id of the initial node
        - goal_node_id should contain the node id of the goal node
        - the graph should contain precondition and effect nodes for all operators
        - the graph should contain all necessary edges.
    */
    task_properties::verify_no_axioms(task_proxy);
    task_properties::verify_no_conditional_effects(task_proxy);

    // Set variables
    int id = 0;
    for(auto prop : relaxed_task.propositions)
    {
        NodeID node_id = graph.add_node(NodeType::OR, 0);
        variable_node_ids[id] = prop.id;
    }

    // Set inital node id and point init variables to it
    initial_node_id = graph.add_node(NodeType::AND);
    for(auto prop_id : relaxed_task.initial_state)
    {
        graph.add_edge(prop_id, initial_node_id);
    }

    // Set goal node id and point it to goal propositions
    goal_node_id = graph.add_node(NodeType::AND);
    for(auto prop_id : relaxed_task.goal)
    {
        graph.add_edge(goal_node_id, prop_id);
    }

    // Get operators and build the rest of the graph
    for(auto op : relaxed_task.operators)
    {
        NodeID op_effect_id = graph.add_node(NodeType::AND, op.cost);
        NodeID op_formula_id = graph.add_node(NodeType::AND, 0);
        auto preconditions = op.preconditions;
        for(int p = 0; p < preconditions.size(); p++)
        {
            auto precond_id = preconditions[p];
            graph.add_edge(op_formula_id, precond_id);
        }
        graph.add_edge(op_effect_id, op_formula_id);
        auto effects = op.effects;
        for(int e = 0; e < effects.size(); e++)
        {
            auto effect_id = effects[e];
            graph.add_edge(effect_id, op_effect_id);
        }
    }
}

void RelaxedTaskGraph::change_initial_state(const GlobalState &global_state) {
    // Remove all initial edges that where introduced for relaxed_task.initial_state.
    for (PropositionID id : relaxed_task.initial_state) {
        graph.remove_edge(variable_node_ids[id], initial_node_id);
    }

    // Switch initial state of relaxed_task
    relaxed_task.initial_state = relaxed_task.translate_state(global_state);

    // Add all initial edges for relaxed_task.initial_state.
    for (PropositionID id : relaxed_task.initial_state) {
        graph.add_edge(variable_node_ids[id], initial_node_id);
    }
}

bool RelaxedTaskGraph::is_goal_relaxed_reachable() {
    // Compute the most conservative valuation of the graph and use it to
    // return true iff the goal is reachable in the relaxed task.

    graph.most_conservative_valuation();
    return graph.get_node(goal_node_id).forced_true;
}

int RelaxedTaskGraph::additive_cost_of_goal() {
    // Compute the weighted most conservative valuation of the graph and use it
    // to return the h^add value of the goal node.

    // TODO: add your code for exercise 2 (c) here.
    return -1;
}

int RelaxedTaskGraph::ff_cost_of_goal() {
    // TODO: add your code for exercise 2 (e) here.
    return -1;
}

}
