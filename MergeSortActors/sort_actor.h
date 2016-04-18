#include "engine.h"
#include <typeinfo>

#define SORT_ACTOR_INCLUDED

struct sort_chan;
struct sort_proc;

struct sort_chan : engine_chan 
{
	bool sorted;
	sort_proc * source;

	std::vector<int>* data;
	int start, end;

	sort_chan(std::vector<int> * data, int start, int end, sort_proc * source)
		: engine_chan()		
		, data(data)
		, start(start)
		, end(end)
		, sorted(false)
		, source(source)
	{ }

	void sort_completed() 
	{
		sorted = true;
	}

	~sort_chan() 
	{ }
};

struct sort_proc : engine_proc 
{
	sort_chan * source_chan;

	sort_proc(engine * e)
		: engine_proc(e)
	{ }

	void recv(chan * c, proc * p)
	{
		if (sort_chan * sortChan = dynamic_cast<sort_chan*>(c)) 
		{
			if (sortChan -> source != this)
			{
				source_chan = sortChan;
			}

			std::vector<int> * data = sortChan -> data;
			int start = sortChan -> start;
			int end = sortChan -> end;

			sort(data, start, end, sortChan);
		}
	}

	virtual void sort(std::vector<int> *, int, int, sort_chan *) = 0;

	void notify_about_sorted()
	{
		source_chan -> sort_completed();
		if (source_chan -> source != NULL) send(e, source_chan, source_chan -> source);
	}
};
