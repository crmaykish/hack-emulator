#ifndef VM_CODE_GENERATOR_HPP
#define VM_CODE_GENERATOR_HPP

#include <string>

class VMCodeGenerator {
public:
    VMCodeGenerator();
    
    std::string Generate(std::string vmCode);

    std::string Arithmetic(std::string command);
    std::string PushPop(std::string command);

private:

};

#endif