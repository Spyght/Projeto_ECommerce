#ifndef TRANSFORMARDADOS_H
#define TRANSFORMARDADOS_H
#include<QString>

namespace mrjp {

class TransformarDados
{
public:
   virtual TransformarDados* montar(std::string) = 0;
   virtual std::string desmontar(QString) = 0;
};

}

#endif // TRANSFORMARDADOS_H
