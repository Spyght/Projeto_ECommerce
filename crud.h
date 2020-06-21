#ifndef MRJP_CRUD_H
#define MRJP_CRUD_H
#include<ldec.h>
#include<QStringList>


namespace mrjp {

class CRUD
{
public:
    CRUD();
    virtual void criarLista()=0;
    virtual int montarObjeto()=0;
};

} // namespace mrjp

#endif // MRJP_CRUD_H
