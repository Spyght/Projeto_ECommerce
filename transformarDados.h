#ifndef TRANSFORMARDADOS_H
#define TRANSFORMARDADOS_H
#include<fstream>
namespace mrjp {
class transformarDados;
}

class transformarDados
{
public:
   transformarDados();
   virtual void montar() = 0;
   virtual void desmontar() = 0;
};

#endif // TRANSFORMARDADOS_H
