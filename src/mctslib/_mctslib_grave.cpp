#include <pybind11/pybind11.h>

#include "algorithms/grave.h"
#include "bindings/python_alg.h"
#include "bindings/python_node.h"

using namespace mctslib;
namespace py = pybind11;

PYBIND11_MODULE(_mctslib_grave, m)
{
    m.doc() = "pybind11 example plugin"; // optional module docstring

    //@NOTE:    Must specify template args to move that correspond to the settings of the algorithm.
    //          No way to infer this because the Settings default constructor cannot be deleted,
    //          and because of this the compiler will always choose to decide that the parameter
    //          pack is empty.
    //
    //
    using PyCPU_Tree_NoRNGTies_GRAVE = PyAlg<GRAVE<PythonNode<RAVEStats>, false, false, false>>;
    py::class_<PyCPU_Tree_NoRNGTies_GRAVE>(m, PyCPU_Tree_NoRNGTies_GRAVE::str_id())
        .def(py::init<uint, uint, uint, py::object>())
        .def("move", &PyCPU_Tree_NoRNGTies_GRAVE::move<uint, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_Tree_NoRNGTies_GRAVE = PyAlg<GRAVE<PythonNode<RAVEStats>, true, false, false>>;
    py::class_<PyIters_Tree_NoRNGTies_GRAVE>(m, PyIters_Tree_NoRNGTies_GRAVE::str_id())
        .def(py::init<uint, uint, uint, py::object>())
        .def("move", &PyIters_Tree_NoRNGTies_GRAVE::move<uint, uint, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_DAG_NoRNGTies_GRAVE = PyAlg<GRAVE<PythonNode<RAVEStats>, false, true, false>>;
    py::class_<PyCPU_DAG_NoRNGTies_GRAVE>(m, PyCPU_DAG_NoRNGTies_GRAVE::str_id())
        .def(py::init<uint, uint, uint, py::object>())
        .def("move", &PyCPU_DAG_NoRNGTies_GRAVE::move<uint, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_DAG_NoRNGTies_GRAVE = PyAlg<GRAVE<PythonNode<RAVEStats>, true, true, false>>;
    py::class_<PyIters_DAG_NoRNGTies_GRAVE>(m, PyIters_DAG_NoRNGTies_GRAVE::str_id())
        .def(py::init<uint, uint, uint, py::object>())
        .def("move", &PyIters_DAG_NoRNGTies_GRAVE::move<uint, uint, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_Tree_RNGTies_GRAVE = PyAlg<GRAVE<PythonNode<RAVEStats>, false, false, true>>;
    py::class_<PyCPU_Tree_RNGTies_GRAVE>(m, PyCPU_Tree_RNGTies_GRAVE::str_id())
        .def(py::init<uint, uint, uint, py::object>())
        .def("move", &PyCPU_Tree_RNGTies_GRAVE::move<uint, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_Tree_RNGTies_GRAVE = PyAlg<GRAVE<PythonNode<RAVEStats>, true, false, true>>;
    py::class_<PyIters_Tree_RNGTies_GRAVE>(m, PyIters_Tree_RNGTies_GRAVE::str_id())
        .def(py::init<uint, uint, uint, py::object>())
        .def("move", &PyIters_Tree_RNGTies_GRAVE::move<uint, uint, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));

    using PyCPU_DAG_RNGTies_GRAVE = PyAlg<GRAVE<PythonNode<RAVEStats>, false, true, true>>;
    py::class_<PyCPU_DAG_RNGTies_GRAVE>(m, PyCPU_DAG_RNGTies_GRAVE::str_id())
        .def(py::init<uint, uint, uint, py::object>())
        .def("move", &PyCPU_DAG_RNGTies_GRAVE::move<uint, double, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("cpu_time"), py::arg("exploration_weight"));

    using PyIters_DAG_RNGTies_GRAVE = PyAlg<GRAVE<PythonNode<RAVEStats>, true, true, true>>;
    py::class_<PyIters_DAG_RNGTies_GRAVE>(m, PyIters_DAG_RNGTies_GRAVE::str_id())
        .def(py::init<uint, uint, uint, py::object>())
        .def("move", &PyIters_DAG_RNGTies_GRAVE::move<uint, uint, double>, "", py::kw_only(),
            py::arg("rollout_depth"), py::arg("iters"), py::arg("exploration_weight"));
}