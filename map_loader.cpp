#include "map_loader.h"

void map_loader::init(std::string file_path){

    file_handler.open(file_path.c_str());
}
std::vector<std::vector<int>> map_loader::generate_map_list(){
    std::istringstream row;
    std::vector<int> row_int;
    std::vector<std::vector<int>> map;
    unsigned int col_size;
    unsigned int row_size;
    std::string element;
    
    if(file_handler.is_open()) {
        for(std::string file_data ;std::getline(file_handler,file_data);){
            row.str(file_data);
            for( std::string element ; std::getline(row,element,',');){
                row_int.push_back(std::stoi(element));
            }
            map.push_back(row_int);
            row_int.clear();
            row.clear();
        }
    }
    this->num_row = map.size();
    this->num_col = map[0].size();
    return map;
}

std::vector<int> map_loader::get_map_dimensions(){
    return std::vector<int>(this->num_row,this->num_col);
}
