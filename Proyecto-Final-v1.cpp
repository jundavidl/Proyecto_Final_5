#include <iostream>
#include <sstream> //Libreria utilisima para manejar strings, funciones de manipulacion de textos
#include <string>
#include <vector>
#include <windows.h> //Libreria para controlar el formato de la consola (Solo windows)
#include <conio.h> //Libreria Necesaria para _getch() y kbhit()

using namespace std;

// DEFINICIÓN: Estructura base para el almacenamiento de los registros
struct Gasto {
    int id;
    string descripcion;
    string categoria;
    string metodoPago;
    double monto;
    string fecha;
    bool esencial;
};

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
void mostrarBanner();
void mostrarMenu(int seleccionada);
int seleccionarOpcionMenu();
string leerLinea(const string& mensaje);           // DECLARACIÓN: Prototipos de las funciones de presentación y navegación
int leerEntero(const string& mensaje, int minimo, int maximo);
double leerMonto();
bool validarFecha(const string& fecha);
void registrarGasto(vector<Gasto>& gastos);

void limpiarPantalla() { system("cls"); }
void pausar() { cout << "\n  Presiona una tecla para continuar..."; _getch(); cout << endl; }

void mostrarBanner() {
    limpiarPantalla();
    cout << CIAN << BOLD << "  ╔══════════════════════════════════════════════╗\n  ║       BIENVENIDO AL SISTEMA DE GASTOS        ║\n  ╚══════════════════════════════════════════════╝\n" << RESET;
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
    int opcionSeleccionada = 1; // DEFINICIÓN: Se empieza apuntando a la opción 1
    int tecla;

    while (true) {
        limpiarPantalla();
        mostrarMenu(opcionSeleccionada);

        tecla = _getch(); // UTILIDADES: El programa se detiene esperando interacción

        if (tecla == 224 || tecla == 0 || tecla == -32) { // VALIDACIÓN: Detecta prefijos de las flechas del teclado
            tecla = _getch(); // FUNCIÓN: Captura el código real de dirección
            
            if (tecla == 72) { // COMPARADOR: Tecla flecha ARRIBA
                opcionSeleccionada--;
                if (opcionSeleccionada < 0) opcionSeleccionada = 10; 
            } 
            else if (tecla == 80) { // COMPARADOR: Tecla flecha ABAJO
                opcionSeleccionada++;
                if (opcionSeleccionada > 10) opcionSeleccionada = 0; 
            }
        } 
        else if (tecla == 13) { // VALIDACIÓN: Código ASCII para la tecla ENTER
            return opcionSeleccionada; 
        }
    }
}

string leerLinea(const string& mensaje) {
    string texto;
    cout << "  " << mensaje << ": ";
    getline(cin, texto);
    return texto;
}

int leerEntero(const string& mensaje, int minimo, int maximo) {
    int valor;
    while (true) {
        cout << "  " << mensaje << " [" << minimo << "-" << maximo << "]: ";
        if (cin >> valor && valor >= minimo && valor <= maximo) { // VALIDACIÓN: Revisa rango permitido
            cin.ignore();
            return valor;
        }
        cin.clear();
        cin.ignore(10000, '\n');                             // UTILIDADES: Limpieza rápida manual sin limits
        cout << ROJO << "  Error: opcion invalida. Intenta de nuevo.\n" << RESET;
    }
}

double leerMonto() {
    double monto;
    while (true) {
        cout << "  Monto: ";
        if (cin >> monto && monto > 0) {                     // VALIDACIÓN: Revisa que el dinero sea mayor a 0
            cin.ignore();
            return monto;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << ROJO << "  Error: ingresa un monto valido (mayor que 0).\n" << RESET;
    }
}

bool validarFecha(const string& fecha) {
    stringstream ss(fecha);  // UTILIDADES: Convierte el string en flujo de datos
    int dia, mes, anio;
    char barra1, barra2;

    if (!(ss >> dia >> barra1 >> mes >> barra2 >> anio)) return false; 
    if (barra1 != '/' || barra2 != '/') return false;  // VALIDACIÓN: Comprueba que los separadores sean barritas

    if (mes < 1 || mes > 12) return false;                   
    if (anio < 2000 || anio > 2100) return false;             

    int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);  // VALIDACIÓN: Validaciones y comprobaciones varias
    if (bisiesto) diasMes[2] = 29;                           

    return (dia >= 1 && dia <= diasMes[mes]);
}

void registrarGasto(vector<Gasto>& gastos) {
    limpiarPantalla();
    cout << CIAN << BOLD << "  ╔══════════════════════════════════════════════╗\n  ║          REGISTRAR NUEVO GASTO               ║\n  ╚══════════════════════════════════════════════╝\n\n" << RESET;

    Gasto g;
    g.id = gastos.empty() ? 1 : gastos.back().id + 1;  // COMPARADOR: Auto-incrementa el ID único

    g.descripcion = leerLinea("Descripcion del gasto");
    if (g.descripcion.empty()) {
        cout << ROJO << "  La descripcion no puede estar vacia.\n" << RESET;
        pausar();
        return;
    }

    cout << "\n  Categorias disponibles:\n  1-Hogar  2-Comida  3-Transporte  4-Educacion\n  5-Salud  6-Ocio  7-Ahorro  8-Otra\n";
    int categoriaOp = leerEntero("Categoria", 1, 8);
    string categorias[] = {"Hogar","Comida","Transporte","Educacion","Salud","Ocio","Ahorro","Otra"};
    g.categoria = categorias[categoriaOp - 1];               

    cout << "\n  Metodos de pago:\n  1-Efectivo  2-Tarjeta  3-Transferencia  4-Otro\n";
    int metodoOp = leerEntero("Metodo de pago", 1, 4);
    string metodos[] = {"Efectivo","Tarjeta","Transferencia","Otro"};
    g.metodoPago = metodos[metodoOp - 1];                     

    g.monto = leerMonto();

    while (true) {
        g.fecha = leerLinea("Fecha (dd/mm/aaaa)");
        if (validarFecha(g.fecha)) break;
        cout << ROJO << "  Fecha invalida. Usa el formato dd/mm/aaaa.\n" << RESET;
    }

    int esOpcional = leerEntero("Es un gasto esencial? (1=Si / 0=No)", 0, 1);
    g.esencial = (esOpcional == 1);                           // COMPARADOR: Transforma el entero en booleano

    gastos.push_back(g);                                      // UTILIDADES: Inserta el registro al vector dinámico

    cout << VERDE << "\n  [OK] Gasto registrado exitosamente con ID #" << g.id << "\n" << RESET;
    pausar();
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8"); 
    SetConsoleOutputCP(65001); //PRESENTACIÓN: Lineas de <windows.h>, necesarias para los simbolos UNICODE
    SetConsoleCP(65001);

    vector<Gasto> gastos;    // DEFINICIÓN: El vector dinámico de base de datos se crea
    int opcion = 0; 

    mostrarBanner();
    pausar();

    while (kbhit()) { _getch(); }                            

    do {
        opcion = seleccionarOpcionMenu();                    
        switch (opcion) {
            case 1:  registrarGasto(gastos); break;    // Unica accion activa por ahora jakajaj
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                cout << AMARILLO << "\n  [Aviso] Modulo de consultas y reportes en desarrollo para la Entrega Final.\n" << RESET;
                pausar();
                break;
            case 0: 
                limpiarPantalla();
                cout << "\n\n" << AMARILLO << BOLD << "  Saliendo del sistema..." << RESET << "\n";
                cout << AMARILLO << "  ¡Hasta pronto usuario, tenga un gran dia!\n\n" << RESET;
                break;
        }

    } while (opcion != 0);                                   

    return 0;
}