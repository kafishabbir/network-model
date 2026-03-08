#include "dst/system.h"


dst::System::System(const std::pair<Parameter, State>& pair):
	parameter(pair.first),
	state(pair.second)
{}

void dst::System::print_matrix() const
{
	std::cout << "I printed" << std::endl;
	const std::string filename = "matrix.txt";
	const auto& matrix = sparse_matrix;
	std::ofstream outFile(filename);
	
	if (!outFile.is_open()) {
		std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
		return;
	}
	
	// Convert to dense for printing (since matrix is small)
	Eigen::MatrixXd denseMatrix = Eigen::MatrixXd(matrix);
	
	// Print column headers
	outFile << "\t";  // First cell empty (for row headers)
	for (int j = 0; j < matrix.cols(); ++j) {
		outFile << j;
		if (j < matrix.cols() - 1) outFile << "\t";
	}
	outFile << std::endl;
	
	// Print rows with row headers 
	for (int i = 0; i < matrix.rows(); ++i) {
		outFile << i << "\t";  // Row header
		for (int j = 0; j < matrix.cols(); ++j) {
			outFile << denseMatrix(i, j);
			if (j < matrix.cols() - 1) outFile << "\t";
		}
		outFile << std::endl;
	}
	
	outFile.close();
	std::cout << "Sparse matrix saved to " << filename << std::endl;
}
