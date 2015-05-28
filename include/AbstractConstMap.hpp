#ifndef _ABSTRACTCONSTMAP_HPP_
#define _ABSTRACTCONSTMAP_HPP_

class AbstractConstMap
{
protected:
    virtual void init() = 0;

public:
    AbstractConstMap( ) {}
    ~AbstractConstMap() {}
};


#endif // _ABSTRACTCONSTMAP_HPP_