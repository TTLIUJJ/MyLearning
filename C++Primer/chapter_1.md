#C++ Primer
##第1章
###1.3
~~~c
#include <iostream>

int main()
{
	std::cout << "Hello, World." << std::endl;
}
~~~
###1.4
~~~c
#include <iostream>

int main()
{
	int v1 = 3;
	int v2 = 5;
	std::cout << "The multiply of " << v1 << "and " << v2 << "is " << v1*v2 << std::endl;
}
~~~
###1.5
~~~c
#include <iostream>

int main()
{
	int v1 = 5;
	int v2 = 3;
	std::cout << "The multiple of ";
	std::cout << v1;
	std::cout << " and ";
	std::cout << v2;
	std::cout << " is ";
	std::cout << v1*v2;
	std::cout << std::endl;
}
~~~
###1.9
~~~c
#include <iostream>

int main()
{
	int i = 50;
	int sum = 0;
	while (i < 101) {
		sum += i;
		++i;
	}
	std::cout << sum << std::endl;
}
~~~
###1.10
~~~c
#include <iostream>

int main()
{
	for (int i = 10; i > -1; --i)
		std::cout << i << " ";

	return 0;
}
~~~
###1.11
~~~c
#include <iostream>

int main()
{
	int v1;
	int v2;
	std::cout << "Please enter two integers: " << std::endl;
	std::cin >> v1 >> v2;
	if (v1 > v2) {
		int temp = v1;
		v1 = v2;
		v2 = temp;
	}
	while (v1 <= v2) {
		std::cout << v1 << " ";
		++v1;
	}
	std::cout << std::endl;
}
~~~
###1.16
~~~c
#include <iostream>

int main()
{
	int v;
	int sum = 0;
	while (std::cin >> v) {
		sum += v;
	}
	std::cout << sum << std::endl;
}
~~~
###1.18
~~~c
#include <iostream>

int main()
{
	int currVal = 0;
	int val = 0;
	if (std::cin >> currVal) {
		int cnt = 1;
		while (std::cin >> val) {
			if (currVal == val)
				++cnt;
			else {
				std::cout << currVal << " occurs " << cnt << " times " << std::endl;
				currVal = val;
				cnt = 1;
			}
		}
		std::cout << currVal << " occurs " << cnt << " times " << std::endl;
	}
	
	return 0;
}
~~~
#include <iostream>

int main()
{
	int currVal = 0;
	int val = 0;
	if (std::cin >> currVal) {
		int cnt = 1;
		while (std::cin >> val) {
			if (currVal == val)
				++cnt;
			else {
				std::cout << currVal << " occurs " << cnt << " times " << std::endl;
				currVal = val;
				cnt = 1;
			}
		}
		std::cout << currVal << " occurs " << cnt << " times " << std::endl;
	}
	
	return 0;
}
