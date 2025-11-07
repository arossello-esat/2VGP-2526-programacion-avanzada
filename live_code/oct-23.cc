#include <memory>

int globala = 0;

class Unit {
  float x, y, rotation;
  Matrix transform;
  mutable bool dirty;
  public:

  void ChangeDirection(float d) {
    rotation = d;
    dirty = true;
  }

  Matrix& GetMatrix();
  const Matrix& GetMatrix() const;
 
// 1 Afecta al tipo apuntado(Matrix)
// 2 Afecta al puntero(Matrix *)
// 3 Cambia this a const this

//  1             2                    3
  const Matrix* const GetTransform() const {
    int a = 1;
    int aa =13;
    const int &b = a;
    int* const c= &a;
    const int* d = &a;
    const int* const e = &a;
    c = &aa;
    *c = 3;

    const Unit p;

    p.ChangeDirection();
    p.GetMatrix()

    globala = 1;
    a++;
    if(dirty) {
      dirty = false;
      this->transform.Multiply(rotation);
    }
    return &(this->transform);
  }

  void ApplyTransformToVec(const vec3& v) const;

};

// VALOR DE RETORNO
Tipo f();      // Se Pasa la propiedad
const Tipo f();// Se Pasa la propiedad NO ES COMUN
   

Tipo& f(); // NO se Pasa la propiedad

  // Te doy acceso para que cambies lo que quieras
const Tipo& f(); // NO se Pasa la propiedad
  // Puedes mirar, pero no tocar

std::shared_ptr<Tipo> f();
std::shared_ptr<Tipo> a = obj.f();

  
Tipo* f(); // MAL NO se Pasa la propiedad, pero es ambiguo. Este interfaz es ambiguo y comunica mal
Tipo* a = f();
delete a;

struct patata {
  patata(int a);
  int a;
};

{
  patata* a = new patata{1};
  patata* b = a;
  patata* c = b;
  patata* d = a;
  delete a;
}

{
  std::shared_ptr<patata> sa = std::make_shared<patata>(1);
  std::shared_ptr<patata> sb = sa;
  std::shared_ptr<patata> sc = sb;
  std::shared_ptr<patata> sd = sa;
}

const Tipo* f(); // MAL NO se Pasa la propiedad, menos ambiguo. Este interfaz es ambiguo y comunica mal
Tipo* const f(); // MAL NO se Pasa la propiedad, pero es ambiguo. Este interfaz es ambiguo y comunica mal. MUY inusual
const Tipo* const f(); // MAL NO se Pasa la propiedad, pero es ambiguo. Este interfaz es ambiguo y comunica mal. MUY inusual

// PASO DE PARAMETROS

void f(Tipo t); // Se comparte copia OJO puede tener problemas de performance si Tipo es muy grande
void f(const Tipo t); // RARO, funcionalmente como el anterior
void f(Tipo& t); // No cedemos la propiedad, pero la funcion va a cambiar cosas en t. Posible valor de retorno extra
void f(const Tipo& t); // Optimizacion para grandes tamaños, funcionalmente igual a void f(Tipo t);
void f(const Tipo* t); // RARO, funcionalmente void f(const Tipo& t);
void f(Tipo* t); // CODIGO ANTIGUO C, funcionalmente void f(Tipo& t) O BIEN, el valor que pasamos es opcional, y puede ser nulo
void f(const Tipo* const t); // RARO, Funcionalmente igual que const Tipo* t
void f(Tipo* const t);// RARO, Funcionalmente igual que Tipo* t

// VARIABLES LOCALES
Tipo t; // TIPICO
const Tipo t; // PREFERIBLE AL ANTERIOR SI PODEMOS
Tipo& t; // ALIAS CORTOS, O MANTENER REFERENCIAS
const Tipo& t; // PREFERIBLE AL ANTERIOR SI PODEMOS
Tipo* t; // IGUAL A LA REFERENCIA, USAR SOLO EN CASO OPCIONAL O QUE HAYA QUE CAMBIAR A QUE APUNTA
const Tipo* t; // PREFERIBLE AL ANTERIOR
Tipo* const t; // USAR SOLO PARA VALORES OPCIONALES, SI NO ES PREFERIBLE REFERENCIA, ALGO RAROS
const Tipo* const t; // USAR SOLO PARA VALORES OPCIONALES, SI NO ES PREFERIBLE REFERENCIA, ALGO RAROS
static -> Aplicable a todas las anteriores, tiene el efecto especial de que la variable mantiene su valor entre llamadas

// VARIABLES GLOBALES
Tipo t; // TIPICO. DESACONSEJADO FUERTEMENTE
const Tipo t; // INOFENSIVO Y COMUN, USADLO TANTO COMO QUERAIS
Tipo& t; // MUY RARO
const Tipo& t; // RARO. INOFENSIVO, ACCESO A DATOS DE LIBRERIAS DE SOLO LECTURA
Tipo* t; // NECESITAMOS APUNTAR A UN VALOR ESPECIFICO GLOBAL.TIPICO. DESACONSEJADO FUERTEMENTE
const Tipo* t; // NECESITAMOS APUNTAR A UN VALOR ESPECIFICO GLOBAL.INOFENSIVO Y COMUN, USADLO TANTO COMO QUERAIS
Tipo* const t; // RARO. CASOS OPCIONALES O REFERENCIAS ESACONSEJADO FUERTEMENTE
const Tipo* const t; // RARO. INOFENSIVO

static global // DI NO

// ATRIBUTOS DE CLASE
Tipo t; // TIPICO.
static Tipo t; // VARIABLE GLOBAL, PERO DENTRO DEL ESPACIO DE NOMBRES DE UN STRUCT/CLASS, SI ES PRIVADA ES INOFENSIVA SE INICIALIZA EN EL CPP.

// CABECERA
class myclass {
  static int a;
}

// CPP

int myclass::a = 3;

const Tipo t; // INOFENSIVO Y COMUN, USADLO TANTO COMO QUERAIS
static const Tipo t; // SE USA PARA VALORES NECESARIOS EN TIEMPO DE COMPILACION, SE LE ASIGNA VALOR TANTO EN LA DEFINICION DE CLASE COMO EN EL CPP.

// CABECERA
class myclass {
  static const int a = 3;
  int myarray[a];

  const int &f() {
    return a;
  }
}

// CPP
const int myclass::a = 3;

Tipo& t; // MUY RARO
const Tipo& t; // RARO. INOFENSIVO, ACCESO A DATOS DE LIBRERIAS DE SOLO LECTURA
Tipo* t; // NECESITAMOS APUNTAR A UN VALOR ESPECIFICO GLOBAL.TIPICO. DESACONSEJADO FUERTEMENTE
const Tipo* t; // NECESITAMOS APUNTAR A UN VALOR ESPECIFICO GLOBAL.INOFENSIVO Y COMUN, USADLO TANTO COMO QUERAIS
Tipo* const t; // RARO. CASOS OPCIONALES O REFERENCIAS ESACONSEJADO FUERTEMENTE
const Tipo* const t; // RARO. INOFENSIVO

static global // DI NO




int bla() {
  const Unit u;
  Matrix transformn = u.GetTransform();
}

