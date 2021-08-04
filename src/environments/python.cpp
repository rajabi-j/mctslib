#include <iostream>
#include <limits>
#include <stdexcept>
#include <memory>
#include <set>
#include <pybind11/stl.h>
#include "util/nodestats.cpp"
#include "algorithm/mcts.cpp"

namespace py = pybind11;

class PyNode {
public:
	py::object object;
	NodeStats stats;

	std::vector<PyNode*> children;
	bool been_expanded = false;

	PyNode(py::object _object) : object(_object), stats(object.attr("evaluation").cast<double>()) {}

	PyNode random_child() const {
		return PyNode(object.attr("random_child")());
	}

	void create_children() {
		py::list list = object.attr("find_children")();
		size_t length = py::len(list);

		children.reserve(length);

		for (py::handle child : list) {
			children.push_back(new PyNode(py::reinterpret_borrow<py::object>(child)));
		}

		return;
	}

	friend bool operator< (const PyNode lhs, const PyNode rhs) {
		return lhs.object < rhs.object;
	}

};



class PyMCTS {
public:
	MCTS<PyNode> mcts;

	PyMCTS (py::object root) : mcts(new PyNode(root)) {}

	py::object pyMove(double exploration_weight, int rollout_depth, int iters, 
			double cpu_time, bool invert_reward) {

		if (!cpu_time && !iters) {
			throw std::invalid_argument("Must supply either cpu_time or iters");
		}

		MCTSSettings settings {exploration_weight, rollout_depth, iters, cpu_time, invert_reward};
		
		return mcts.move(settings).object;
	}
};
