#include <memory>
#include <pybind11/pybind11.h>


#include "algorithms/mcts.h"
#include "bindings/python_alg.h"
#include "bindings/python_node.h"

using namespace mctslib;
namespace py = pybind11;

PYBIND11_MODULE(_mctslib_mcts, m)
{
    m.doc() = "pybind11 example plugin"; // optional module docstring

    //@NOTE:    Must specify template args to move that correspond to the settings of the algorithm.
    //          No way to infer this because the Settings default constructor cannot be deleted,
    //          and because of this the compiler will always choose to decide that the parameter
    //          pack is empty.
    //


    // Used to traverse
    //
    py::class_<MCTSStats>(m, "MCTSStats")
        .def_readonly("evaluation", &MCTSStats::evaluation)
        .def_readonly("action_id", &MCTSStats::action_id)
        .def_readonly("backprop_reward", &MCTSStats::backprop_reward)
        .def_readonly("visits", &MCTSStats::visits)
        .def("average_reward", &MCTSStats::average_reward);

    py::class_<PythonNode<MCTSStats>, std::shared_ptr<PythonNode<MCTSStats>>>(m, "MCTSNode")
        .def("children", &PythonNode<MCTSStats>::children, "")
        .def_readonly("state", &PythonNode<MCTSStats>::state)
        .def_readonly("stats", &PythonNode<MCTSStats>::stats);

    using PyCPU_Tree_NoRNG_NoCAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, false, false, false, false>>;
    py::class_<PyCPU_Tree_NoRNG_NoCAS_MCTS>(m, PyCPU_Tree_NoRNG_NoCAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyCPU_Tree_NoRNG_NoCAS_MCTS::move<int, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_Tree_NoRNG_NoCAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, true, false, false, false>>;
    py::class_<PyIters_Tree_NoRNG_NoCAS_MCTS>(m, PyIters_Tree_NoRNG_NoCAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyIters_Tree_NoRNG_NoCAS_MCTS::move<int, int, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_DAG_NoRNG_NoCAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, false, true, false, false>>;
    py::class_<PyCPU_DAG_NoRNG_NoCAS_MCTS>(m, PyCPU_DAG_NoRNG_NoCAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyCPU_DAG_NoRNG_NoCAS_MCTS::move<int, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_DAG_NoRNG_NoCAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, true, true, false, false>>;
    py::class_<PyIters_DAG_NoRNG_NoCAS_MCTS>(m, PyIters_DAG_NoRNG_NoCAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyIters_DAG_NoRNG_NoCAS_MCTS::move<int, int, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_Tree_RNG_NoCAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, false, false, true, false>>;
    py::class_<PyCPU_Tree_RNG_NoCAS_MCTS>(m, PyCPU_Tree_RNG_NoCAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyCPU_Tree_RNG_NoCAS_MCTS::move<int, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_Tree_RNG_NoCAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, true, false, true, false>>;
    py::class_<PyIters_Tree_RNG_NoCAS_MCTS>(m, PyIters_Tree_RNG_NoCAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyIters_Tree_RNG_NoCAS_MCTS::move<int, int, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_DAG_RNG_NoCAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, false, true, true, false>>;
    py::class_<PyCPU_DAG_RNG_NoCAS_MCTS>(m, PyCPU_DAG_RNG_NoCAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyCPU_DAG_RNG_NoCAS_MCTS::move<int, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_DAG_RNG_NoCAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, true, true, true, false>>;
    py::class_<PyIters_DAG_RNG_NoCAS_MCTS>(m, PyIters_DAG_RNG_NoCAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyIters_DAG_RNG_NoCAS_MCTS::move<int, int, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_Tree_NoRNG_CAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, false, false, false, true>>;
    py::class_<PyCPU_Tree_NoRNG_CAS_MCTS>(m, PyCPU_Tree_NoRNG_CAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyCPU_Tree_NoRNG_CAS_MCTS::move<int, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_Tree_NoRNG_CAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, true, false, false, true>>;
    py::class_<PyIters_Tree_NoRNG_CAS_MCTS>(m, PyIters_Tree_NoRNG_CAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyIters_Tree_NoRNG_CAS_MCTS::move<int, int, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_DAG_NoRNG_CAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, false, true, false, true>>;
    py::class_<PyCPU_DAG_NoRNG_CAS_MCTS>(m, PyCPU_DAG_NoRNG_CAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyCPU_DAG_NoRNG_CAS_MCTS::move<int, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_DAG_NoRNG_CAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, true, true, false, true>>;
    py::class_<PyIters_DAG_NoRNG_CAS_MCTS>(m, PyIters_DAG_NoRNG_CAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyIters_DAG_NoRNG_CAS_MCTS::move<int, int, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_Tree_RNG_CAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, false, false, true, true>>;
    py::class_<PyCPU_Tree_RNG_CAS_MCTS>(m, PyCPU_Tree_RNG_CAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyCPU_Tree_RNG_CAS_MCTS::move<int, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_Tree_RNG_CAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, true, false, true, true>>;
    py::class_<PyIters_Tree_RNG_CAS_MCTS>(m, PyIters_Tree_RNG_CAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyIters_Tree_RNG_CAS_MCTS::move<int, int, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_DAG_RNG_CAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, false, true, true, true>>;
    py::class_<PyCPU_DAG_RNG_CAS_MCTS>(m, PyCPU_DAG_RNG_CAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyCPU_DAG_RNG_CAS_MCTS::move<int, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_DAG_RNG_CAS_MCTS = PyAlg<MCTS<PythonNode<MCTSStats>, true, true, true, true>>;
    py::class_<PyIters_DAG_RNG_CAS_MCTS>(m, PyIters_DAG_RNG_CAS_MCTS::str_id())
        .def(py::init<double, int, py::object>())
        .def("move", &PyIters_DAG_RNG_CAS_MCTS::move<int, int, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));
}
