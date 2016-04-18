#ifndef SORT_ACTOR_INCLUDED
	#include "sort_actor.h"
#endif // !SORT_ACTOR_INCLUDED

struct merge_chan : sort_chan
{
	int mid;

	merge_chan(std::vector<int> * data, int start, int mid, int end, sort_proc * source)
		: sort_chan(data, start, end, source)
		, mid(mid)
	{ }

	~merge_chan()
	{ }
};

struct merge_proc : sort_proc
{
	merge_proc(engine * e) 
		: sort_proc(e)
	{ }

	void sort(std::vector<int> * data, int start, int end, sort_chan * sortChan)
	{
		if (merge_chan * mergeChan = dynamic_cast<merge_chan*>(sortChan)) 
		{
			int mid = mergeChan -> mid;

			int left_length = mid - start + 1;
			std::vector<int> left_part(left_length);
			for (int i = 0; i < left_length; ++i)
			{
				left_part[i] = data -> operator[](start + i);
			}

			int right_length = end - mid;
			std::vector<int> right_part(right_length);
			for (int i = 0; i < right_length; ++i)
			{
				right_part[i] = data -> operator[](mid + i + 1);
			}

			for (int left_index = 0, right_index = 0, data_index = start; data_index <= end; ++data_index)
			{
				std::vector<int> * current_part = NULL;
				int * current_index = NULL;

				if (left_index == left_length)
				{
					current_part = &right_part;
					current_index = &right_index;
				}
				else if (right_index == right_length)
				{
					current_part = &left_part;
					current_index = &left_index;
				}
				else
				{
					int left_value = left_part[left_index];
					int right_value = right_part[right_index];

					if (left_value <= right_value)
					{
						current_part = &left_part;
						current_index = &left_index;
					}
					else 
					{
						current_part = &right_part;
						current_index = &right_index;
					}
				}

				data -> operator[](data_index) = current_part -> operator[](*current_index);
				(*current_index)++;
			}

			notify_about_sorted();
		}
	}
};