#include"Hugeint.h"
int main()
{
	
	Hugeint h("4564");//
    Hugeint g("17010");//22721551515527296
	Hugeint t('0');
	std::cout << h << std::endl;
	std::cout << g << std::endl;
	t = g * h;
	std::cout << t << std::endl;
	t = g / h;
	std::cout << "g/h = " << t << std::endl;
	/*t = g * h;
	std::cout << t << std::endl;*/
	return 0;
}