#pragma once
#include <iostream>

#ifdef _DEBUG
#define DEBUG_PRINT1(val) std::cout<<val<<std::endl;
#define DEBUG_PRINT2(val1,val2) std::cout<<val1<<" "<<val2<<std::endl;
#else
#define DEBUG_PRINT1(val) ;
#define DEBUG_PRINT2(val1,val2) ;
#endif


