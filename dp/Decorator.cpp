class Decorator
{
public:
    Decorator() {}
    virtual ~Decorator() {}

    virtual void dddd() {}
};

class Search : public Decorator
{
public:
    Search() {}
    ~Search() {}

    void dddd() override {}
};

class File : public Decorator
{
public:
    File(Decorator* d) : m_d(d) {}
    ~File() {}

    void dddd() override
    {
        // read();
        m_d->dddd();
    }

private:
    Decorator* m_d;
};
