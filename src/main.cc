#include "../include/vrp.h"

int protected_main(int argc, char** argv);
std::string usage();

/**
 * @brief Main function
 *
 * @param argc Number of arguments
 * @param argv Arguments
 * @return int (exit status)
 */
int main(int argc, char** argv) {
  try {
    return protected_main(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}

/**
 * @brief Main function
 *
 * @param argc Number of arguments
 * @param argv Arguments
 * @return 0 if success, 1 otherwise
 */
int protected_main(int argc, char** argv) {
  if(argc != 3) {
    std::cout << usage() << '\n';
    return 1;
  } else {
    std::string filename = argv[1];
    int n = std::stoi(argv[2]);
    VRP vrp(filename,n);
    vrp.Solve();
  }
  return 0;
}

/**
 * Prints the usage of the program.
 */
std::string usage() {
  std::string aux_string = "";
  aux_string += "Usage:\n";
  aux_string += "./build/main <input_file> <option> -> It reads the input";
  aux_string += "file and selects the option to create the graph.\n";
  aux_string += "Options:\n\t0: grasp\n\t1: greedy\n";
  return aux_string;
}
