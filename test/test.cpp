#include "testcasepairwiseop.hpp"
#include "testcasecovseiso.hpp"

int main(int argc, char** argv) 
{ 
	// Initialize test environment
	::testing::InitGoogleTest(&argc, argv);
		
	// Test
	int ret = RUN_ALL_TESTS(); 

	system("pause");
	return ret;
}