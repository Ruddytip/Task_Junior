#include <iostream>
#include "Container.hpp"

int main(){
    try{
        Container<std::string, std::string> cnt;
        cnt.set("test1", "Test1_Out");
        cnt.get("Test_get_error");
    }
    catch(Ex<std::string>& err){
        std::cerr << err.get_key() << std::endl;
    }

    return 0;
}