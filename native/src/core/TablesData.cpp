#include "original.hpp"
namespace TablesData {
int32_t AMOD_A(int32_t reg){
return M68k::setw(reg,(reg & TablesData::SINTAB_MASK_ADR));
}

int32_t AMOD_I(int32_t reg){
return M68k::setw(reg,(reg & TablesData::SINTAB_MASK_IDX));
}

}