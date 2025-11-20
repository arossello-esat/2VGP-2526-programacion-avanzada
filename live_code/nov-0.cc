#include <vector>

class Naranja {
    public:
        Naranja() : semillas{0} {}

        int semillas;
};

int main(int,char**) {
    std::vector<Naranja> naranjas;// Tamaño 0

    std::vector<Naranja> naranjas2{3};// Tamaño 3

    naranjas.reserve(4); // Tamaño 0
    naranjas.resize(3); // Tamaño 3
    naranjas.resize(2); // Tamaño 2, el ultimo elemento se destruye
    naranjas.shrink_to_fit(); // el buffer interno se reduce de tamaño a 2

    for(int i=0; i != naranjas.size() ; i++) {
        naranjas[i].semillas = 0;
    }

    Naranja naranjas_old[3];
    for(int i=0; i != sizeof(naranjas_old)/sizeof(Naranja) ; i++) {
        naranjas[i].semillas = 0;
    }

    Naranja* end = naranjas_old + sizeof(naranjas_old)/sizeof(Naranja);
    for(Naranja* i=naranjas_old; i != end ; i++) {
        i->semillas = 0;
    }

    for(auto i = naranjas.begin(); i != naranjas.end() ; i++) {
        Naranja& value = *i;
        value.semillas = 0;
    }

    for(auto& value : naranjas) { // Exactamente equivalente a la anterior
        value.semillas = 0;
    }

    for(auto& value : naranjas_old) { // funciona con arrays de toda la vida
        value.semillas = 0;
    }

    return 0;
}