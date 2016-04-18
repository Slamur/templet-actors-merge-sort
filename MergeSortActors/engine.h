#include <vector>
#include "proc_chan.h"

struct engine
{
	std::vector<chan *> ready;
};

struct engine_chan : chan
{
	engine_chan()
		: chan(NULL, false)
	{ }

	~engine_chan() 
	{ };
};

struct engine_proc : proc 
{
	engine * e;

	engine_proc(engine * e) 
		: e(e)
	{ }
};

inline void send(engine * e, chan * c, proc * p)
{
	if (c -> sending) return;
	c -> sending = true;
	c -> p = p;
	e -> ready.push_back(c);
}

inline void run(engine * e, int n = 1)
{
	size_t rsize;
	while (rsize = e -> ready.size()){
		int n = rand() % rsize; 
		auto it = e -> ready.begin() + n;

		chan * c = *it; 
		e -> ready.erase(it); 
		c -> sending = false;

		proc * p = c -> p;
		p -> recv(c, p);
	}
}