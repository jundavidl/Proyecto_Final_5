#include <iostream>
#include <string>
#include <windows.h> //Libreria para controlar el formato de la consola (Solo windows)
#include <conio.h> //Libreria Necesaria para _getch() y kbhit()

using namespace std;

const string RESET   = "\033[0m"; //DEFINICION: Definimos los colores ANSI previamente que vamos a usar
const string BOLD    = "\033[1m";
const string ROJO    = "\033[31m";
const string VERDE   = "\033[32m";
const string AMARILLO = "\033[33m";
const string AZUL    = "\033[34m";
const string MAGENTA = "\033[35m";
const string CIAN    = "\033[36m";

void limpiarPantalla();
void pausar();
void mostrarBanner();                     // DECLARACIÓN: Prototipos de las funciones de presentación y navegación
void mostrarMenu(int seleccionada);
int seleccionarOpcionMenu();

void limpiarPantalla() {
    system("cls");
}

void pausar() {
    cout << "\n  Presiona una tecla para continuar...";
    _getch();
    cout << endl;
}

void mostrarBanner() {
    limpiarPantalla();
    cout << CIAN << BOLD;
    cout << "  ╔══════════════════════════════════════════════╗\n";
    cout << "  ║       BIENVENIDO AL SISTEMA DE GASTOS        ║\n";
    cout << "  ╚══════════════════════════════════════════════╝\n" << RESET;
    cout << "\n  Cargando la interfaz del usuario...\n";
}

void mostrarMenu(int seleccionada) {
    cout << CIAN << BOLD;
    cout << "\n  ╔══════════════════════════════════════════════╗\n"; 
    cout << "  ║          MENU PRINCIPAL                      ║\n"; 
    cout << "  ╠══════════════════════════════════════════════╣\n"; 
    cout << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 1) cout << BOLD << VERDE << " > 1.  Registrar gasto                       " << RESET;
    else                   cout << VERDE << "   1." << RESET << "  Registrar gasto                       ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 2) cout << BOLD << VERDE << " > 2.  Ver todos los gastos (tabla)          " << RESET;
    else                   cout << VERDE << "   2." << RESET << "  Ver todos los gastos (tabla)          ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 3) cout << BOLD << VERDE << " > 3.  Buscar por categoria                  " << RESET;
    else                   cout << VERDE << "   3." << RESET << "  Buscar por categoria                  ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 4) cout << BOLD << VERDE << " > 4.  Buscar por rango de fechas            " << RESET;
    else                   cout << VERDE << "   4." << RESET << "  Buscar por rango de fechas            ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 5) cout << BOLD << CIAN << " > 5.  Estadisticas y graficos ASCII         " << RESET;
    else                   cout << CIAN << "   5." << RESET << "  Estadisticas y graficos ASCII         ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 6) cout << BOLD << CIAN << " > 6.  Ver gasto mas alto del mes            " << RESET;
    else                   cout << CIAN << "   6." << RESET << "  Ver gasto mas alto del mes            ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 7) cout << BOLD << AMARILLO << " > 7.  Editar un gasto existente             " << RESET;
    else                   cout << AMARILLO << "   7." << RESET << "  Editar un gasto existente             ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 8) cout << BOLD << ROJO << " > 8.  Eliminar un gasto                     " << RESET;
    else                   cout << ROJO << "   8." << RESET << "  Eliminar un gasto                     ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 9) cout << BOLD << CIAN << " > 9.  Exportar reporte mensual (.txt)       " << RESET;
    else                   cout << CIAN << "   9." << RESET << "  Exportar reporte mensual (.txt)       ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 10) cout << BOLD << AMARILLO << "> 10.  Reiniciar programa                    " << RESET;
    else                    cout << AMARILLO << "  10." << RESET << "  Reiniciar programa                    ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 0) cout << BOLD << ROJO << " > 0.  Salir                                 " << RESET;
    else                   cout << ROJO << "   0." << RESET << "  Salir                                 ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ╚══════════════════════════════════════════════╝\n" << RESET;
    cout << "  [Usa las flechas ▲/▼ para moverte y ENTER para seleccionar]\n";
}

int seleccionarOpcionMenu() {
    int opcionSeleccionada = 1;                              // DEFINICIÓN: Empezamos apuntando a la opción 1
    int tecla;

    while (true) {
        limpiarPantalla();
        mostrarMenu(opcionSeleccionada);                     // PRESENTACIÓN: Dibuja el menú con los colores armónicos

        tecla = _getch();                                    // UTILIDADES: El programa se detiene esperando interacción

        if (tecla == 224 || tecla == 0 || tecla == -32) {    // VALIDACIÓN: Detecta prefijos de las flechas del teclado
            tecla = _getch();                                // FUNCIÓN: Captura el código real de dirección
            
            if (tecla == 72) {                               // COMPARADOR: Tecla flecha ARRIBA
                opcionSeleccionada--;
                if (opcionSeleccionada < 0) opcionSeleccionada = 10; 
            } 
            else if (tecla == 80) {                          // COMPARADOR: Tecla flecha ABAJO
                opcionSeleccionada++;
                if (opcionSeleccionada > 10) opcionSeleccionada = 0; 
            }
        } 
        else if (tecla == 13) {                              // VALIDACIÓN: Código ASCII para la tecla ENTER
            return opcionSeleccionada;                       // FUNCIÓN: Termina el bucle y escupe la opción elegida
        }
    }
}

int main() {
    // PRESENTACIÓN: Configuración básica para soportar caracteres UTF-8 en la consola
    setlocale(LC_ALL, "es_ES.UTF-8");
    SetConsoleOutputCP(65001); //PRESENTACIÓN: Lineas de <windows.h>, necesarias para los simbolos UNICODE
    SetConsoleCP(65001);

    int opcion = 0;                                          // DEFINICIÓN: Controla la navegación del switch

    mostrarBanner();
    pausar();

    while (kbhit()) { _getch(); }                            // UTILIDADES: Limpia residuos del teclado antes de iniciar

    do {
        opcion = seleccionarOpcionMenu();                    // FUNCIÓN: Obtiene la opción seleccionada con las flechas

        switch (opcion) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                cout << AMARILLO << "\n  [Aviso] Modulo en desarrollo para la Entrega 2.\n" << RESET;
                pausar();
                break;
            case 0: 
                limpiarPantalla();
                cout << "\n\n" << AMARILLO << BOLD << "  Saliendo del sistema..." << RESET << "\n";
                cout << AMARILLO << "  ¡Hasta pronto usuario, tenga un gran dia!\n\n" << RESET;
                break;
        }

    } while (opcion != 0);                                   // VALIDACIÓN: Mantiene el ciclo hasta presionar Enter en Salir

    return 0;
}
