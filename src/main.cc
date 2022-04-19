#include "../include/vrp.h"

int protected_main(int argc, char** argv);
std::string usage();

int main(int argc, char** argv) {
  try {
    return protected_main(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}

int protected_main(int argc, char** argv) {
  if(argc != 2) {
    std::cout << usage() << '\n';
    return 1;
  } else {
    std::string filename = argv[1];
    VRP vrp(filename);
    vrp.Solve();
  }
  return 0;
}


std::string usage() {
  std::string aux_string = "";
  aux_string += "Usage: ";
  aux_string += "./build/main <input_file> -> It reads the input file and ";
  aux_string += "creates the graph.\n";
  return aux_string;
}
