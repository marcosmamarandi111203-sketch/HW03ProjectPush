#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

// PROTOTIPOS DE FUNCIONES
bool esNombreValido(string);
string convertirMayusculas(string);

void jugarAhorcado(string);
void mostrarAhorcado(int);
void mostrarPalabra(string, bool[]);
void mostrarLetrasUsadas(char[], int);

bool letraRepetida(char, char[], int);
bool palabraAdivinada(bool[], int);
char pedirLetra(char[], int);

void guardarResultado(string, string, int, int,
                      char[], int, string);

int main() {
    string nombreJugador;
    char volverJugar;

    cout << "========================================\n";
    cout << "          JUEGO DEL AHORCADO\n";
    cout << "========================================\n\n";

    // VALIDACIÓN DEL NOMBRE
    do {
        cout << "Ingrese el nombre del jugador: ";
        getline(cin, nombreJugador);

        if (!esNombreValido(nombreJugador)) {
            cout << "ERROR: El nombre solamente puede contener "
                 << "letras y espacios.\n\n";
        }

    } while (!esNombreValido(nombreJugador));

    nombreJugador = convertirMayusculas(nombreJugador);

    cout << "\nBienvenido, " << nombreJugador << ".\n";

    // PERMITE VOLVER A JUGAR
    do {
        jugarAhorcado(nombreJugador);

        cout << "\nDesea volver a jugar? S/N: ";
        cin >> volverJugar;
        cin.ignore();

        volverJugar = toupper(volverJugar);

        while (volverJugar != 'S' && volverJugar != 'N') {
            cout << "ERROR: Ingrese solamente S o N: ";
            cin >> volverJugar;
            cin.ignore();

            volverJugar = toupper(volverJugar);
        }

    } while (volverJugar == 'S');

    cout << "\nGracias por jugar, "
         << nombreJugador << ".\n";

    return 0;
}

// VALIDA QUE EL NOMBRE TENGA LETRAS Y ESPACIOS
bool esNombreValido(string nombre) {
    int i = 0;

    bool valido = true;
    bool tieneLetra = false;

    if (nombre.length() == 0) {
        valido = false;
    }

    while (valido && i < nombre.length()) {
        if (isalpha(nombre.at(i))) {
            tieneLetra = true;
        }
        else if (nombre.at(i) != ' ') {
            valido = false;
        }

        i++;
    }

    if (!tieneLetra) {
        valido = false;
    }

    return valido;
}

// CONVIERTE UNA CADENA COMPLETA A MAYÚSCULAS
string convertirMayusculas(string texto) {
    int i;

    for (i = 0; i < texto.length(); i++) {
        texto.at(i) = toupper(texto.at(i));
    }

    return texto;
}

// FUNCIÓN PRINCIPAL DEL JUEGO
void jugarAhorcado(string nombreJugador) {
    const int MAX_ERRORES = 6;
    const int MAX_LETRAS = 30;

    // PALABRA SECRETA
    string palabraSecreta = "PROGRAMACION";

    // INDICA QUÉ POSICIONES FUERON ADIVINADAS
    bool posicionesAdivinadas[MAX_LETRAS] = {false};

    // GUARDA TODAS LAS LETRAS INGRESADAS
    char letrasUsadas[MAX_LETRAS];

    // GUARDA ÚNICAMENTE LAS LETRAS INCORRECTAS
    char letrasIncorrectas[MAX_ERRORES];

    int cantidadUsadas = 0;
    int cantidadIncorrectas = 0;

    int errores = 0;
    int intentosRealizados = 0;
    int letrasAcertadas = 0;

    int i;

    char letra;

    bool encontrada;

    string resultado;

    cout << "\n========================================\n";
    cout << "          COMIENZA EL AHORCADO\n";
    cout << "========================================\n";

    cout << "Jugador: " << nombreJugador << "\n";
    cout << "Adivine la palabra letra por letra.\n";
    cout << "Tiene un maximo de 6 errores.\n";

    while (
        errores < MAX_ERRORES &&
        !palabraAdivinada(
            posicionesAdivinadas,
            palabraSecreta.length()
        )
    ) {
        cout << "\n----------------------------------------\n";

        mostrarAhorcado(errores);

        cout << "\nPalabra secreta: ";

        mostrarPalabra(
            palabraSecreta,
            posicionesAdivinadas
        );

        cout << "\nLetras utilizadas: ";

        mostrarLetrasUsadas(
            letrasUsadas,
            cantidadUsadas
        );

        cout << "\nErrores: "
             << errores
             << " de "
             << MAX_ERRORES
             << "\n";

        cout << "Intentos restantes: "
             << MAX_ERRORES - errores
             << "\n";

        letra = pedirLetra(
            letrasUsadas,
            cantidadUsadas
        );

        // REGISTRA LA LETRA
        letrasUsadas[cantidadUsadas] = letra;
        cantidadUsadas++;

        intentosRealizados++;

        encontrada = false;

        // BUSCA LA LETRA EN TODA LA PALABRA
        for (i = 0; i < palabraSecreta.length(); i++) {
            if (
                palabraSecreta.at(i) == letra &&
                posicionesAdivinadas[i] == false
            ) {
                posicionesAdivinadas[i] = true;

                encontrada = true;
                letrasAcertadas++;
            }
        }

        if (encontrada) {
            cout << "\nCORRECTO: La letra "
                 << letra
                 << " esta en la palabra.\n";
        }
        else {
            letrasIncorrectas[cantidadIncorrectas] = letra;

            cantidadIncorrectas++;
            errores++;

            cout << "\nINCORRECTO: La letra "
                 << letra
                 << " no esta en la palabra.\n";
        }
    }

    cout << "\n========================================\n";

    mostrarAhorcado(errores);

    cout << "\nPalabra completa: "
         << palabraSecreta
         << "\n";

    if (
        palabraAdivinada(
            posicionesAdivinadas,
            palabraSecreta.length()
        )
    ) {
        resultado = "VICTORIA";

        cout << "\nFELICIDADES, "
             << nombreJugador
             << ".\n";

        cout << "Ha adivinado correctamente la palabra.\n";
    }
    else {
        resultado = "DERROTA";

        cout << "\nHA PERDIDO.\n";
        cout << "Alcanzo el maximo de 6 errores.\n";
    }

    cout << "\nResultado: "
         << resultado
         << "\n";

    cout << "Intentos realizados: "
         << intentosRealizados
         << "\n";

    cout << "Letras acertadas: "
         << letrasAcertadas
         << "\n";

    cout << "Letras incorrectas: ";

    mostrarLetrasUsadas(
        letrasIncorrectas,
        cantidadIncorrectas
    );

    // GUARDA LOS DATOS EN UN ARCHIVO
    guardarResultado(
        nombreJugador,
        palabraSecreta,
        intentosRealizados,
        letrasAcertadas,
        letrasIncorrectas,
        cantidadIncorrectas,
        resultado
    );
}

// MUESTRA EL DIBUJO SEGÚN EL NÚMERO DE ERRORES
void mostrarAhorcado(int errores) {
    switch (errores) {
        case 0:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;

        case 1:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;

        case 2:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << "  |   |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;

        case 3:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << " /|   |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;

        case 4:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << " /|\\  |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;

        case 5:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << " /|\\  |\n";
            cout << " /    |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;

        case 6:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << " /|\\  |\n";
            cout << " / \\  |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;
    }
}

// MUESTRA LAS LETRAS ADIVINADAS Y LOS GUIONES
void mostrarPalabra(
    string palabra,
    bool posicionesAdivinadas[]
) {
    int i;

    for (i = 0; i < palabra.length(); i++) {
        if (posicionesAdivinadas[i]) {
            cout << palabra.at(i) << " ";
        }
        else {
            cout << "_ ";
        }
    }

    cout << "\n";
}

// MUESTRA LAS LETRAS GUARDADAS EN UN ARREGLO
void mostrarLetrasUsadas(
    char letras[],
    int cantidad
) {
    int i;

    if (cantidad == 0) {
        cout << "NINGUNA";
    }
    else {
        for (i = 0; i < cantidad; i++) {
            cout << letras[i];

            if (i < cantidad - 1) {
                cout << ", ";
            }
        }
    }

    cout << "\n";
}

// REVISA SI UNA LETRA YA FUE INGRESADA
bool letraRepetida(
    char letra,
    char letrasUsadas[],
    int cantidadUsadas
) {
    int i = 0;

    bool repetida = false;

    while (!repetida && i < cantidadUsadas) {
        if (letrasUsadas[i] == letra) {
            repetida = true;
        }

        i++;
    }

    return repetida;
}

// REVISA SI TODAS LAS POSICIONES FUERON ADIVINADAS
bool palabraAdivinada(
    bool posicionesAdivinadas[],
    int tamanio
) {
    int i = 0;

    bool completa = true;

    while (completa && i < tamanio) {
        if (posicionesAdivinadas[i] == false) {
            completa = false;
        }

        i++;
    }

    return completa;
}

// SOLICITA Y VALIDA UNA LETRA
char pedirLetra(
    char letrasUsadas[],
    int cantidadUsadas
) {
    string entrada;

    char letra;

    bool valida;

    do {
        valida = true;

        cout << "\nIngrese una letra: ";
        getline(cin, entrada);

        // DEBE INGRESAR SOLAMENTE UN CARÁCTER
        if (entrada.length() != 1) {
            valida = false;

            cout << "ERROR: Debe ingresar solamente una letra.\n";
        }
        else if (!isalpha(entrada.at(0))) {
            valida = false;

            cout << "ERROR: No puede ingresar numeros, "
                 << "espacios ni simbolos.\n";
        }
        else {
            letra = toupper(entrada.at(0));

            if (
                letraRepetida(
                    letra,
                    letrasUsadas,
                    cantidadUsadas
                )
            ) {
                valida = false;

                cout << "ERROR: La letra "
                     << letra
                     << " ya fue utilizada.\n";
            }
        }

    } while (!valida);

    return letra;
}

// GUARDA EL RESULTADO EN UN ARCHIVO TXT
void guardarResultado(
    string nombreJugador,
    string palabra,
    int intentosRealizados,
    int letrasAcertadas,
    char letrasIncorrectas[],
    int cantidadIncorrectas,
    string resultado
) {
    ofstream archivoSalida;

    string nombreArchivo;

    int i;

    // REEMPLAZA ESPACIOS POR GUIONES BAJOS
    for (i = 0; i < nombreJugador.length(); i++) {
        if (nombreJugador.at(i) == ' ') {
            nombreJugador.at(i) = '_';
        }
    }

    nombreArchivo =
        nombreJugador +
        "_AHORCADO.txt";

    archivoSalida.open(
        nombreArchivo.c_str()
    );

    if (archivoSalida.fail()) {
        cout << "\nERROR: No se pudo crear el archivo.\n";
    }
    else {
        archivoSalida << "========================================\n";
        archivoSalida << "       RESULTADO DEL AHORCADO\n";
        archivoSalida << "========================================\n";

        archivoSalida << "Nombre del jugador: "
                      << nombreJugador
                      << "\n";

        archivoSalida << "Nombre del juego: AHORCADO\n";

        archivoSalida << "Palabra secreta: "
                      << palabra
                      << "\n";

        archivoSalida << "Puntaje obtenido: "
                      << letrasAcertadas
                      << "\n";

        archivoSalida << "Intentos realizados: "
                      << intentosRealizados
                      << "\n";

        archivoSalida << "Letras acertadas: "
                      << letrasAcertadas
                      << "\n";

        archivoSalida << "Letras incorrectas: ";

        if (cantidadIncorrectas == 0) {
            archivoSalida << "NINGUNA";
        }
        else {
            for (i = 0; i < cantidadIncorrectas; i++) {
                archivoSalida << letrasIncorrectas[i];

                if (i < cantidadIncorrectas - 1) {
                    archivoSalida << ", ";
                }
            }
        }

        archivoSalida << "\nResultado de la partida: "
                      << resultado
                      << "\n";

        archivoSalida << "========================================\n";

        archivoSalida.close();

        cout << "\nEl resultado se guardo en el archivo: "
             << nombreArchivo
             << "\n";
    }
}