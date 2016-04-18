struct proc;
struct chan;

struct proc 
{
	virtual void recv(chan *, proc *) = 0;
};

struct chan
{
	proc * p;
	bool sending;

	chan(proc * p, bool sending)
		: p(p)
		, sending(sending)
	{ }

	virtual ~chan()
	{ }
};

inline bool access(chan * c, proc * p)
{
	return c -> p == p && !(c -> sending);
}