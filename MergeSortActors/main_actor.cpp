#include "merge_sort_actor.cpp"
#include <iostream>

int main() 
{
	int n;
	std::cin >> n;

	std::vector<int> data(n);
	for (int i = 0; i < n; ++i) 
	{
		std::cin >> data[i];
	}

	engine * e = new engine();

	sort_chan * sortChan = new sort_chan(&data, 0, n - 1, NULL);
	merge_sort_proc * mergeSortProc =  new merge_sort_proc(e);

	send(e, sortChan, mergeSortProc);

	run(e);

	for (int i = 0; i < n; ++i)
	{
		std::cout << data[i] << ' ';
	}

	std::cout << std::endl;

	char pause_char;
	std::cin >> pause_char;

	return 0;
}
