#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "../includes/TextAnalyzer.hpp"

namespace py = pybind11;

PYBIND11_MODULE(WordFreqAnalyzer, m) {
	m.doc() = "Word frequency analyzer module";

	m.def("analyze_freq", WordFreq, 
		"Calculate word frequencies from text",
		py::arg("lines"));
	
	m.def("save_to_csv", SaveFreqToCsv,
		"Save frequency map to CSV file",
		py::arg("freq"),
		py::arg("filename"));
}