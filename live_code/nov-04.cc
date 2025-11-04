
struct NodeInt {
    int data_;
    NodeInt * next_;
};



template<typename T>
struct Node {
    T data_;
    Node<T> * next_;
};


#include <vector>
#include <iterator>
#include <string>
#include <unordered_map>

int main(int, char**) {
    NodeInt first;
    Node<float> firstfloat;


    // PRIMER CONTENEDOR: STD::VECTOR

    float arrf[20];
    std::vector<float> vf;


    // El array no tiene reserva dinamica
    vf.push_back(1.0f);
    vf.push_back(2.0f);
    vf.push_back(3.0f);
    vf.push_back(4.0f);
    vf.push_back(5.0f);
    vf.pop_back();
    vf.pop_back();

    // {1.0f,2.0f,3.0f} 4 y 5 los hemos eliminado

    float* itf = arrf;
    float* endf = arrf+20;
    for(;itf != endf ; itf++) {
        float value = *itf;
        *itf = 30.0f;
    }

    std::vector<float>::iterator it = vf.begin();
    std::vector<float>::iterator end = vf.end();
    for(; it != end ; it++) {
        float value = *it;
        *it = 30.0f;
    }

    // { 30.0f,30.0f,30.0f}

    // lo mismo que el anterior
    for(float& value : vf) {
        value = 3.f;
    }
    // { 3.0f,3.0f,3.0f}

    for(float& value : arrf) {
        value = 3.f;
    }

    float* itbegin2 = std::begin(arrf);
    std::vector<float>::iterator itbegin3 = std::begin(vf);
    float* itbend2 = std::end(arrf);
    std::vector<float>::iterator itend3 = std::end(vf);

    auto variable = vf.begin();

    auto& referencia_variable = *vf.begin();

    vf[2] = 4.0f;

    //MAL MAL
    bool insert = true;
    for(float& value : vf) {
        if(insert) {
            insert = false;
            vf.push_back(3);
        } else {
            insert = true;
        }
    }

    // MEJOR
    bool insert2 = true;
    std::vector<float> elementos_nuevos;
    for(float& value : vf) {
        if(insert2) {
            insert2 = false;
            elementos_nuevos.push_back(3);
        } else {
            insert2 = true;
        }
    }
    // SOBREESCRIBE LOS ELEMENTOS DESTINO, EN ESTE CASO DESDE EL INICION DE VF
    std::copy(elementos_nuevos.begin(),elementos_nuevos.end(),vf.begin());


    // adaptador: es un iterador "virtual", en este caso inserta los elementos asignados en vf
    auto adapter = std::back_inserter(vf);
    // AÑADE ELEMENTOS AL FINAL DE VF
    std::copy(elementos_nuevos.begin(),elementos_nuevos.end(),adapter);



    // CADENAS: STD::STRING

    std::string str = "Hola mundo";
    str.append(", y hola valencia");
    int position = str.find("Valencia",0);
    str.replace(position,8, "Madrid");





    // MAPAS: unordered_map

    struct Date {
        int month;
        int day;
    };


    std::unordered_map<std::string,Date> birthdays;

    birthdays["Carlos"] = {9,15};
    birthdays["Raquel"] = {9,15};
    birthdays["Carlos"] = {9,10}; // BORRA EL ANTERIOR

    auto it = birthdays.find("Arnau");
    
    const Date& raquel_bd = birthdays["Raquel"];
    if(raquel_bd.day == 14) {

    }

    birthdays.erase("Raquel");

    // Version opuesta
    std::unordered_multimap<Date,std::string> names;




    return 0;
}
