#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
class map_loader{

private:
    std::ifstream file_handler;
    unsigned int num_row;
    unsigned int num_col;
public:
    map_loader(std::string file_path);
    std::vector<std::vector<int>> generate_map_list();
    std::vector<int> get_map_dimensions();
};
