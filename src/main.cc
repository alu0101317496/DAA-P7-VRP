#include "../include/graph.h"

int protected_main(int argc, char** argv);
void usage();

int main(int argc, char** argv) {
  try {
    return protected_main(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}

int protected_main(int argc, char** argv) {
  if(argc != 1) {
    std::cout << usage() << '\n';
    return 1;
  }
  return 0;
}


void usage() {
  std::string aux_string = "";
  aux_string += "Usage: ";
  aux_string += "./build/main <input_file>";
}
