#include "relaxed_task_graph.h"

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

namespace planopt_heuristics
{
    RelaxedTaskGraph::RelaxedTaskGraph(const TaskProxy &task_proxy)
        : relaxed_task(task_proxy),
          variable_node_ids(relaxed_task.propositions.size())
    {
        /*
          TODO: add your code for exercise 2 (b) here. Afterwards
            - variable_node_ids[i] should contain the node id of the variable node for variable i
            - initial_node_id should contain the node id of the initial node
            - goal_node_id should contain the node id of the goal node
            - the graph should contain precondition and effect nodes for all operators
            - the graph should contain all necessary edges.
        */

        size_t index = 0;
        for (const auto &prop : relaxed_task.propositions)
        {
            NodeID node_id = graph.add_node(NodeType::OR, 0);
            variable_node_ids[index++] = prop.id;
        }

        initial_node_id = graph.add_node(NodeType::AND, 0);
        std::for_each(
            relaxed_task.initial_state.begin(),
            relaxed_task.initial_state.end(),
            [this](PropositionID p_id)
            { graph.add_edge(p_id, initial_node_id); });

        goal_node_id = graph.add_node(NodeType::AND, 0);
        for (const auto &goal_prop : relaxed_task.goal)
        {
            graph.add_edge(goal_node_id, goal_prop);
        }

        for (const auto &op : relaxed_task.operators)
        {
            NodeID effect_node_id = graph.add_node(NodeType::AND, op.cost);

            NodeID formula_node_id = graph.add_node(NodeType::AND, 0);
            std::for_each(
                op.preconditions.begin(),
                op.preconditions.end(),
                [this, &formula_node_id](PropositionID p_id)
                {
                    graph.add_edge(formula_node_id, p_id);
                });

            graph.add_edge(effect_node_id, formula_node_id);

            for (const auto &effect_prop : op.effects)
            {
                graph.add_edge(effect_prop, effect_node_id);
            }
        }
    }

    void RelaxedTaskGraph::change_initial_state(const GlobalState &global_state)
    {
        // Remove all initial edges that where introduced for relaxed_task.initial_state.
        for (PropositionID id : relaxed_task.initial_state)
        {
            graph.remove_edge(variable_node_ids[id], initial_node_id);
        }

        // Switch initial state of relaxed_task
        relaxed_task.initial_state = relaxed_task.translate_state(global_state);

        // Add all initial edges for relaxed_task.initial_state.
        for (PropositionID id : relaxed_task.initial_state)
        {
            graph.add_edge(variable_node_ids[id], initial_node_id);
        }
    }

    bool RelaxedTaskGraph::is_goal_relaxed_reachable()
    {
        // Compute the most conservative valuation of the graph and use it to
        // return true iff the goal is reachable in the relaxed task.

        graph.most_conservative_valuation();
        return graph.get_node(goal_node_id).forced_true;
    }

    int RelaxedTaskGraph::additive_cost_of_goal()
    {
        // Compute the weighted most conservative valuation of the graph and use it
        // to return the h^add value of the goal node.

        // TODO: add your code for exercise 2 (c) here.
        graph.weighted_most_conservative_valuation();

        return graph.get_node(goal_node_id).additive_cost;
    }

    int RelaxedTaskGraph::ff_cost_of_goal()
    {
        // TODO: add your code for exercise 2 (e) here.
        graph.weighted_most_conservative_valuation();

        unordered_set<NodeID> visited_nodes;
        queue<NodeID> processing_queue;
        int total_cost = 0;

        processing_queue.push(goal_node_id);

        while (!processing_queue.empty())
        {
            NodeID current_node_id = processing_queue.front();
            processing_queue.pop();

            if (visited_nodes.count(current_node_id) > 0)
            {
                continue;
            }

            visited_nodes.insert(current_node_id);

            const AndOrGraphNode &current_node = graph.get_node(current_node_id);

            if (current_node.type == NodeType::AND)
            {
                for (NodeID successor_id : current_node.successor_ids)
                {
                    if (visited_nodes.count(successor_id) == 0)
                    {
                        processing_queue.push(successor_id);
                    }
                }
            }
            else if (current_node.type == NodeType::OR)
            {
                if (visited_nodes.count(current_node.achiever) == 0)
                {
                    processing_queue.push(current_node.achiever);
                }
            }
        }

        for (NodeID node_id : visited_nodes)
        {
            total_cost += graph.get_node(node_id).direct_cost;
        }

        return total_cost;
    }
}
