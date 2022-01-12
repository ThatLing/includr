
#include "includr_extern.h"

includr::IncludrFile test({
	0x68,0x65,0x6c,0x6c,0x6f
});

void aaa()
{
	auto yes = test.ToString();
	printf("got it: %s\n", yes.c_str());
}
// DEBUG FILE
#ifdef nah
int main()
{
	aaa();

	return 0;
}
#endif