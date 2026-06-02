// ============================================================
//  PROYECTO FINAL - PROGRAMACION BASICA
//  Sistema de Seguimiento de Gastos Mensuales

//  JUAN PABLO MELO GONZALEZ    - 20261020136
//  JUAN DAVID LOPEZ RINCON     - 20261020152
//  JUAN FELIPE FUENTES JIMENEZ - 20261020157
// ============================================================

//ANTES DE COMENZAR
//Vamos a definir las clasificaciones de las notas al margen, esto servira para hacer una barrida mas rapida de información
//Estos tipos son:
//UTILIDADES
//DEFINICION
//DECLARACION
//COMPARADOR
//FUNCION
//PRESENTACION
//VALIDACION

#include <iostream>
#include <fstream> //Libreria que controla la creacion, lectura y escritura de datos en archivos
#include <sstream> //Libreria utilisima para manejar strings, funciones de manipulacion de textos
#include <string>
#include <vector>
#include <algorithm> //Libreria con funciones utiles (principalmente optimizacion de codigos evitando algunos bucles for, if, etc)
#include <iomanip> //Libreria que sirve para darle formato visual al texto y a los número, una herramienta de diseño
#include <limits> //Libreria unicamente usada para ignorar el buffer de un cin hasta el limite de este
#include <windows.h> //Libreria para controlar el formato de la consola (Solo windows)
#include <conio.h> //Libreria Necesaria para _getch() y kbhit()

using namespace std;

#define RESET       "\033[0m" //DEFINICION: Definimos los colores ANSI previamente que vamos a usar
#define BOLD        "\033[1m"
#define ROJO        "\033[31m"
#define VERDE       "\033[32m"
#define AMARILLO    "\033[33m"
#define AZUL        "\033[34m"
#define MAGENTA     "\033[35m"
#define CIAN        "\033[36m"
#define BLANCO      "\033[37m"
#define FONDO_AZUL  "\033[44m"
#define FONDO_VERDE "\033[42m"

const string ARCHIVO = "Gastos.txt"; //DEFINICION: Definimos constantes
const int MAX_GASTOS = 500;

struct Gasto { //DECLARACION: Struct principal de GASTOS
    int id;
    string descripcion;
    string categoria;
    string metodoPago;
    double monto;
    string fecha;
    bool esencial;
};

string intToString(int n) { //UTILIDADES: Funcion ss para convertir un entero a string
    ostringstream oss;
    oss << n;
    return oss.str();
}

bool compararMontoDesc(const Gasto& a, const Gasto& b) { //UTILIDADES: Funcion unica para ordenar gastos de mayor a menor en funciones q lo requieran
    return a.monto > b.monto;
}

//  DECLARACION DE FUNCIONES (PROTOTIPOS)

void mostrarBanner();
int seleccionarOpcionMenu();
void mostrarMenu(int seleccionada);
void limpiarPantalla();                                 //FUNCIONES DE PRESENTACION
void pausar();
void imprimirTitulo(const string& titulo);

bool validarFecha(const string& fecha);
long fechaADias(const string& fecha);
bool fechaEnRango(const string& fecha, const string& inicio, const string& fin);      //FUNCIONES DE VALIDACION
int obtenerSemana(const string& fecha);
double leerMonto();
int leerEntero(const string& mensaje, int minimo, int maximo);
string leerLinea(const string& mensaje);

void registrarGasto(vector<Gasto>& gastos);
void verTodosLosGastos(const vector<Gasto>& gastos);
void buscarPorCategoria(const vector<Gasto>& gastos);     //FUNCIONES CON GASTOS
void buscarPorFecha(const vector<Gasto>& gastos);
void editarGasto(vector<Gasto>& gastos);
void eliminarGasto(vector<Gasto>& gastos);

void verEstadisticas(const vector<Gasto>& gastos);
void mostrarGraficoBarras(const string& etiqueta, double valor, double maximo, int anchoMax);     //FUNCIONES DE GRAFICAS
void verGastoMasAlto(const vector<Gasto>& gastos);

void guardarGastos(const vector<Gasto>& gastos);
void cargarGastos(vector<Gasto>& gastos);                          //FUNCIONES DE ARCHIVO
void exportarReporte(const vector<Gasto>& gastos);


//  FUNCION PRINCIPAL


int main() {
    setlocale(LC_ALL, "es_ES.UTF-8"); 
    SetConsoleOutputCP(65001); //PRESENTACION: Lineas de <windows.h>, necesarias para los simbolos UNICODE
    SetConsoleCP(65001);

    vector<Gasto> gastos; //DEFINICION: Definimos nombre con el que trabajaremos el vector + llamarlo "gastos"
    int opcion = 0;

    cargarGastos(gastos);
    mostrarBanner();
    pausar();

    while (kbhit()) { _getch(); } // UTILIDADES: Limpia cualquier residuo o pulsación fantasma en el búfer antes de habilitar el teclado

    do {
        opcion = seleccionarOpcionMenu();

            switch (opcion) {
                case 1:  registrarGasto(gastos);       break;
                case 2:  verTodosLosGastos(gastos);    break;
                case 3:  buscarPorCategoria(gastos);   break;
                case 4:  buscarPorFecha(gastos);       break;
                case 5:  verEstadisticas(gastos);      break;
                case 6:  verGastoMasAlto(gastos);      break;
                case 7:  editarGasto(gastos);        break;
                case 8:  eliminarGasto(gastos);      break;
                case 9:  exportarReporte(gastos);    break;
                case 10: cargarGastos(gastos);
                        limpiarPantalla();
                        cout << VERDE << "\n  [OK] Datos recargados desde " << ARCHIVO << "\n" << RESET;
                        pausar();
                        break;
                case 0: limpiarPantalla();
                        cout << "\n\n";
                        cout << AMARILLO << BOLD << "  Guardando y saliendo..." << RESET << "\n";
                        cout << AMARILLO << "  ¡Hasta pronto usuario, tenga un gran día!\n\n" << RESET;
                        guardarGastos(gastos);
                        break;
        }

    } while (opcion != 0);

    return 0;
}


//  PRESENTACION Y MENU


void mostrarBanner() {
    limpiarPantalla();
    cout << CIAN << BOLD;
    cout << "  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                                                      ║\n";
    cout << "  ║         💰  GESTOR DE GASTOS MENSUALES  💰           ║\n";
    cout << "  ║            Sistema Familiar de Finanzas              ║\n";
    cout << "  ║                                                      ║\n";
    cout << "  ╚══════════════════════════════════════════════════════╝\n";
    cout << RESET;
    cout << AMARILLO;
    cout << "\n  Bienvenido al sistema de seguimiento de gastos.\n";
    cout << "  Los datos se guardan automaticamente en: " << "ARCHIVO" << "\n"; //Quitar comillas al momento de crear el archivo para q funcione
    cout << RESET;
}

int seleccionarOpcionMenu() {
    int opcionSeleccionada = 1; // DEFINICION: Se empieza apuntando a la opcion 1
    int tecla;

    while (true) {
        limpiarPantalla();
        mostrarMenu(opcionSeleccionada);

        tecla = _getch(); // UTILIDADES: El programa se detiene esperando interaccion

        if (tecla == 224 || tecla == 0 || tecla == -32) { // VALIDACION: Detecta prefijos de las flechas del teclado
            tecla = _getch(); // FUNCION: Captura el codigo real de direccion
            
            if (tecla == 72) { // COMPARADOR: Tecla flecha ARRIBA
                opcionSeleccionada--;
                if (opcionSeleccionada < 0) opcionSeleccionada = 10; 
            } 
            else if (tecla == 80) { // COMPARADOR: Tecla flecha ABAJO
                opcionSeleccionada++;
                if (opcionSeleccionada > 10) opcionSeleccionada = 0; 
            }
        } 
        else if (tecla == 13) { // VALIDACION: Codigo ASCII para la tecla ENTER
            return opcionSeleccionada; 
        }
    }
}

void mostrarMenu(int seleccionada) {
    cout << CIAN << BOLD;
    cout << "\n  ╔══════════════════════════════════════════════╗\n"; 
    cout << "  ║                MENU PRINCIPAL                ║\n"; 
    cout << "  ╠══════════════════════════════════════════════╣\n"; 
    cout << RESET;

    // OPCIÓN 1
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 1) cout << BOLD << VERDE << " > 1.  Registrar gasto                       " << RESET;
    else                   cout << VERDE << "   1." << RESET << "  Registrar gasto                       ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 2
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 2) cout << BOLD << VERDE << " > 2.  Ver todos los gastos (tabla)          " << RESET;
    else                   cout << VERDE << "   2." << RESET << "  Ver todos los gastos (tabla)          ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 3
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 3) cout << BOLD << AZUL << " > 3.  Buscar por categoria                  " << RESET;
    else                   cout << AZUL << "   3." << RESET << "  Buscar por categoria                  ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 4
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 4) cout << BOLD << AZUL << " > 4.  Buscar por rango de fechas            " << RESET;
    else                   cout << AZUL << "   4." << RESET << "  Buscar por rango de fechas            ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 5
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 5) cout << BOLD << MAGENTA << " > 5.  Estadisticas y graficos ASCII         " << RESET;
    else                   cout << MAGENTA << "   5." << RESET << "  Estadisticas y graficos ASCII         ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 6
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 6) cout << BOLD << MAGENTA << " > 6.  Ver gasto mas alto del mes            " << RESET;
    else                   cout << MAGENTA << "   6." << RESET << "  Ver gasto mas alto del mes            ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 7
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 7) cout << BOLD << AMARILLO << " > 7.  Editar un gasto existente             " << RESET;
    else                   cout << AMARILLO << "   7." << RESET << "  Editar un gasto existente             ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 8
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 8) cout << BOLD << AMARILLO << " > 8.  Eliminar un gasto existente           " << RESET;
    else                   cout << AMARILLO << "   8." << RESET << "  Eliminar un gasto existente           ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 9
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 9) cout << BOLD << BLANCO << " > 9.  Exportar reporte mensual (.txt)       " << RESET;
    else                   cout << BLANCO << "   9." << RESET << "  Exportar reporte mensual (.txt)       ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 10
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 10) cout << BOLD << BLANCO << "> 10.  Reiniciar programa                    " << RESET;
    else                    cout << BLANCO << "  10." << RESET << "  Reiniciar programa                    ";
    cout << CIAN << "║\n" << RESET;

    // OPCIÓN 0
    cout << CIAN << "  ║ " << RESET;
    if (seleccionada == 0) cout << BOLD << ROJO << " > 0.  Salir                                 " << RESET;
    else                   cout << ROJO << "   0." << RESET << "  Salir                                 ";
    cout << CIAN << "║\n" << RESET;

    cout << CIAN << "  ╚══════════════════════════════════════════════╝\n" << RESET;
    cout << "  [Usa las flechas ▲/▼ para moverte y ENTER para seleccionar]\n";
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // FUNCION: Codigo universal que limpia pantalla sin importa sistema operativo
    #else
        system("clear");
    #endif
}

void pausar() {
    cout << AMARILLO << "\n  Presiona Enter para continuar..." << RESET;
    while (kbhit()) { _getch(); } // UTILIDADES: Limpiamos el bufer
    _getch();
    cout << endl;
}

void imprimirTitulo(const string& titulo) { // FUNCION: Funcion ULTRA practica que da formatos a los titulos definiendo un ancho
    limpiarPantalla();                      // y en base a ese ancho, ajustar el texto a la mitad, con sus respectivas margenes
    int ancho = 52;
    
    cout << CIAN << BOLD;
    
    cout << "\n  ╔";
    for (int i = 0; i < ancho; i++) cout << "═";
    cout << "╗\n";
    
    int espaciosIzq = (ancho - (int)titulo.size()) / 2;
    int espaciosDer = ancho - espaciosIzq - (int)titulo.size();
    
    cout << "  ║" << string(espaciosIzq, ' ') << titulo
         << string(espaciosDer, ' ') << "║\n";

    cout << "  ╚";
    for (int i = 0; i < ancho; i++) cout << "═";
    cout << "╝\n" << RESET;
}


//  VALIDACIONES


bool validarFecha(const string& fecha) {
    stringstream ss(fecha); // UTILIDADES: Convierte el string en un flujo de datos
    int dia, mes, anio;
    char barra1, barra2; // DEFINICION: Contenedores basura para atrapar los '/'

    if (!(ss >> dia >> barra1 >> mes >> barra2 >> anio)) return false; // VALIDACION: Revisa que se puedan extraer los 3 numeros
    
    if (barra1 != '/' || barra2 != '/') return false; // VALIDACION: Comprueba que los separadores sean barritas

    if (mes < 1 || mes > 12) return false;
    if (anio < 2000 || anio > 2100) return false;

    int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0); // VALIDACION: Validaciones y comprobaciones varias
    if (bisiesto) diasMes[2] = 29;

    return (dia >= 1 && dia <= diasMes[mes]);  
}

long fechaADias(const string& fecha) {
    stringstream ss(fecha);
    int dia, mes, anio;
    char barra1, barra2; // DEFINICION: Contenedores temporales para absorber los '/'
    ss >> dia >> barra1 >> mes >> barra2 >> anio; // FUNCION: Desarma el texto y reparte los numeros limpios
    return (anio * 365) + (mes * 30) + dia;
}

bool fechaEnRango(const string& fecha, const string& inicio, const string& fin) {
    long f  = fechaADias(fecha);  // FUNCION: Convierte la fecha del gasto actual a numero
    long i  = fechaADias(inicio); // FUNCION: Convierte la fecha limite de inicio a numero
    long fn = fechaADias(fin);    // FUNCION: Convierte la fecha limite de fin a numero
    return (f >= i && f <= fn); 
}

int obtenerSemana(const string& fecha) {
    stringstream ss(fecha); // UTILIDADES: Convierte el texto de la fecha en flujo de datos
    int dia;
    ss >> dia; // FUNCION: Extrae unicamente el numero del dia al principio del texto

    if (dia <= 7)  return 1;
    if (dia <= 14) return 2;
    if (dia <= 21) return 3;
    if (dia <= 28) return 4;
    return 5;
}

double leerMonto() {
    while (true) {
        string entrada = leerLinea("Monto"); // FUNCION: Captura la entrada de forma segura
        stringstream ss(entrada);
        double monto;
        if (ss >> monto && monto > 0) return monto;
        cout << ROJO << "  Error: ingresa un monto valido (mayor que 0).\n" << RESET;
    }
}

int leerEntero(const string& mensaje, int minimo, int maximo) {
    while (true) {
        string entrada = leerLinea(mensaje + " [" + intToString(minimo) + "-" + intToString(maximo) + "]");
        stringstream ss(entrada);
        int valor;
        if (ss >> valor && valor >= minimo && valor <= maximo) { // VALIDACION: Revisa que sea numero y este en el rango permitido
            return valor; // FUNCION: Retorna el numero entero validado de forma exitosa
        }
        cout << ROJO << "  Error: opcion invalida. Intenta de nuevo.\n" << RESET;
    }
}

string leerLinea(const string& mensaje) {
    string texto;
    while (true) {
        cout << "  " << mensaje << ": "; // UTILIDADES: Forma base para cualquier ingreso de datos
        getline(cin, texto);
        if (texto.empty()) {
            cout << "\033[A\033[K"; // UTILIDADES: Sube una linea y borra si presionan ENTER vacio
            continue;
        }
        return texto;
    }
}


//  OPERACIONES CON GASTOS


void registrarGasto(vector<Gasto>& gastos) {
    imprimirTitulo("REGISTRAR NUEVO GASTO");

    Gasto g;
    g.id = gastos.empty() ? 1 : gastos.back().id + 1; //COMPARADOR: "Auto-incrementa" el ID basandose en el ultimo gasto

    g.descripcion = leerLinea("Descripcion del gasto");
    if (g.descripcion.empty()) {
        cout << ROJO << "  La descripcion no puede estar vacia.\n" << RESET;
        pausar();
        return;
    }

    cout << "\n  Categorias disponibles:\n";
    cout << "  1-Hogar  2-Comida  3-Transporte  4-Educacion\n";
    cout << "  5-Salud  6-Ocio  7-Ahorro  8-Otra\n";
    int categoriaOp = leerEntero("Categoria", 1, 8);
    string categorias[] = {"Hogar","Comida","Transporte","Educacion","Salud","Ocio","Ahorro","Otra"};
    g.categoria = categorias[categoriaOp - 1]; // FUNCION: Mapea el número del menu con el texto del arreglo

    cout << "\n  Metodos de pago:\n";
    cout << "  1-Efectivo  2-Tarjeta  3-Transferencia  4-Otro\n";
    int metodoOp = leerEntero("Metodo de pago", 1, 4);
    string metodos[] = {"Efectivo","Tarjeta","Transferencia","Otro"};
    g.metodoPago = metodos[metodoOp - 1]; // FUNCION: Mapea el numero elegido con el metodo de pago real

    g.monto = leerMonto();

    while (true) {
        g.fecha = leerLinea("Fecha (dd/mm/aaaa)");
        if (validarFecha(g.fecha)) break;
        cout << ROJO << "  Fecha invalida. Usa el formato dd/mm/aaaa.\n" << RESET;
    }

    int esOpcional = leerEntero("Es un gasto esencial? (1=Si / 0=No)", 0, 1);
    g.esencial = (esOpcional == 1); // COMPARADOR: Convierte el 1 o 0 ingresado a un valor booleano

    gastos.push_back(g); // UTILIDADES: Inserta el nuevo registro al final del vector
    guardarGastos(gastos);

    cout << VERDE << "\n  [OK] Gasto registrado exitosamente con ID #" << g.id << "\n" << RESET;
    pausar();
}

void verTodosLosGastos(const vector<Gasto>& gastos) {
    imprimirTitulo("TODOS LOS GASTOS");

    if (gastos.empty()) {
        cout << AMARILLO << "  No hay gastos registrados aun.\n" << RESET;
        pausar();
        return;
    }

    vector<Gasto> ordenados = gastos; // DEFINICION: Duplica el vector para poder ordenar sin alterar el original
    sort(ordenados.begin(), ordenados.end(), compararMontoDesc); // FUNCION: Clasifica los registros de mayor a menor monto en la tabla

    cout << CIAN;
    cout << "  ┌────┬────────────────────────┬──────────────┬──────────────┬──────────┬────────────┬─────────┐\n";
    cout << "  │ ID │ Descripcion            │ Categoria    │ Metodo Pago  │  Monto   │   Fecha    │Esencial │\n";
    cout << "  ├────┼────────────────────────┼──────────────┼──────────────┼──────────┼────────────┼─────────┤\n";
    cout << RESET;

    for (int i = 0; i < (int)ordenados.size(); i++) {
        const Gasto& g = ordenados[i];
        string esen = g.esencial ? "  SI  " : "  NO  ";
        string colorEsen = g.esencial ? VERDE : ROJO; // COMPARADOR: Asigna verde a lo esencial y rojo a lo opcional

        cout << CIAN << "  │" << RESET;
        cout << setw(3) << g.id << " ";
        cout << CIAN << "│" << RESET;
        cout << " " << left << setw(23) << g.descripcion.substr(0, 22); // UTILIDADES: Corta el texto si supera el ancho maximo de celda
        cout << CIAN << "│" << RESET;
        cout << " " << left << setw(13) << g.categoria.substr(0, 12); // UTILIDADES: Asegura que la categoria encaje simetricamente
        cout << CIAN << "│" << RESET;
        cout << " " << left << setw(13) << g.metodoPago.substr(0, 12); // UTILIDADES: Recorta el texto del metodo de pago si es muy largo
        cout << CIAN << "│" << RESET;
        cout << right << setw(9) << fixed << setprecision(2) << g.monto << " "; // PRESENTACION: Formatea el decimal alineado a la derecha
        cout << CIAN << "│" << RESET;
        cout << " " << g.fecha << " ";
        cout << CIAN << "│" << RESET;
        cout << colorEsen << esen << RESET;
        cout << CIAN << "   │\n" << RESET;
    }

    cout << CIAN;
    cout << "  └────┴────────────────────────┴──────────────┴──────────────┴──────────┴────────────┴─────────┘\n";
    cout << RESET;

    double total = 0;
    for (int i = 0; i < (int)gastos.size(); i++) total += gastos[i].monto; // FUNCION: Suma acumulativa de toda la columna de costos
    cout << AMARILLO << BOLD << "  Total de " << gastos.size() << " gastos: $" << fixed << setprecision(2) << total << "\n" << RESET;

    pausar();
}

void buscarPorCategoria(const vector<Gasto>& gastos) {
    imprimirTitulo("BUSCAR POR CATEGORIA");

    cout << "  Categorias: 1-Hogar  2-Comida  3-Transporte  4-Educacion\n";
    cout << "              5-Salud  6-Ocio  7-Ahorro  8-Otra\n";
    int categoriaOp = leerEntero("Selecciona categoria", 1, 8);
    string categorias[] = {"Hogar","Comida","Transporte","Educacion","Salud","Ocio","Ahorro","Otra"};
    string catBuscar = categorias[categoriaOp - 1]; // FUNCION: Traduce el numero del menu al string correspondiente

    vector<Gasto> resultado;
    for (int i = 0; i < (int)gastos.size(); i++) {
        if (gastos[i].categoria == catBuscar) resultado.push_back(gastos[i]); // FUNCION: Filtra y extrae las coincidencias al nuevo vector
    }

    if (resultado.empty()) {
        cout << AMARILLO << "\n  No se encontraron gastos en la categoria '" << catBuscar << "'.\n" << RESET;
        pausar();
        return;
    }

    sort(resultado.begin(), resultado.end(), compararMontoDesc); // FUNCION: Clasifica los resultados filtrados de mayor a menor costo

    cout << VERDE << "\n  Gastos en categoria: " << BOLD << catBuscar << RESET << "\n";
    cout << CIAN;
    cout << "  ┌────┬────────────────────────┬──────────────┬──────────────┬────────────┐\n";
    cout << "  │ ID │ Descripcion            │ Metodo Pago  │  Monto       │   Fecha    │\n";
    cout << "  ├────┼────────────────────────┼──────────────┼──────────────┼────────────┤\n";
    cout << RESET;

    double subtotal = 0;
    for (int i = 0; i < (int)resultado.size(); i++) {
        const Gasto& g = resultado[i];
        subtotal += g.monto; // FUNCION: Acumula el dinero gastado unicamente en esta categoria
        cout << CIAN << "  │" << RESET;
        cout << setw(3) << g.id << " ";
        cout << CIAN << "│" << RESET;
        cout << " " << left << setw(23) << g.descripcion.substr(0, 22); // UTILIDADES: Corta la descripcion para no deformar la celda
        cout << CIAN << "│" << RESET;
        cout << " " << left << setw(13) << g.metodoPago.substr(0, 12);
        cout << CIAN << "│" << RESET;
        cout << right << setw(13) << fixed << setprecision(2) << g.monto << " "; // PRESENTACION: Formatea los costos alineados a la derecha
        cout << CIAN << "│" << RESET;
        cout << " " << g.fecha << " ";
        cout << CIAN << "│\n" << RESET;
    }
    cout << CIAN << "  └────┴────────────────────────┴──────────────┴──────────────┴────────────┘\n" << RESET;
    cout << AMARILLO << "  Subtotal categoria '" << catBuscar << "': $" << fixed << setprecision(2) << subtotal << "\n" << RESET;

    pausar();
}

void buscarPorFecha(const vector<Gasto>& gastos) {
    imprimirTitulo("BUSCAR POR RANGO DE FECHAS");

    string inicio, fin;
    while (true) {
        inicio = leerLinea("Fecha inicio (dd/mm/aaaa)");
        if (validarFecha(inicio)) break;
        cout << ROJO << "  Fecha invalida.\n" << RESET;
    }
    while (true) {
        fin = leerLinea("Fecha fin   (dd/mm/aaaa)");
        if (validarFecha(fin)) break;
        cout << ROJO << "  Fecha invalida.\n" << RESET;
    }

    vector<Gasto> resultado;
    for (int i = 0; i < (int)gastos.size(); i++) {
        if (fechaEnRango(gastos[i].fecha, inicio, fin)) resultado.push_back(gastos[i]);
    }

    if (resultado.empty()) {
        cout << AMARILLO << "\n  No se encontraron gastos en ese rango.\n" << RESET;
        pausar();
        return;
    }

    sort(resultado.begin(), resultado.end(), compararMontoDesc);

    cout << VERDE << "\n  Gastos del " << inicio << " al " << fin << ":\n" << RESET;
    cout << CIAN;
    cout << "  ┌────┬────────────────────────┬──────────────┬──────────────┬────────────┐\n";
    cout << "  │ ID │ Descripcion            │ Categoria    │  Monto       │   Fecha    │\n";
    cout << "  ├────┼────────────────────────┼──────────────┼──────────────┼────────────┤\n";
    cout << RESET;

    double subtotal = 0;
    for (int i = 0; i < (int)resultado.size(); i++) {
        const Gasto& g = resultado[i];
        subtotal += g.monto;
        cout << CIAN << "  │" << RESET << setw(3) << g.id << " ";
        cout << CIAN << "│" << RESET << " " << left << setw(23) << g.descripcion.substr(0, 22);
        cout << CIAN << "│" << RESET << " " << left << setw(13) << g.categoria.substr(0, 12);
        cout << CIAN << "│" << RESET << right << setw(13) << fixed << setprecision(2) << g.monto << " ";
        cout << CIAN << "│" << RESET << " " << g.fecha << " ";
        cout << CIAN << "│\n" << RESET;
    }
    cout << CIAN << "  └────┴────────────────────────┴──────────────┴──────────────┴────────────┘\n" << RESET;
    cout << AMARILLO << "  Total del rango: $" << fixed << setprecision(2) << subtotal << "\n" << RESET;

    pausar();
}

void editarGasto(vector<Gasto>& gastos) {
    imprimirTitulo("EDITAR GASTO");

    if (gastos.empty()) {
        cout << AMARILLO << "  No hay gastos para editar.\n" << RESET;
        pausar();
        return;
    }

    int id = leerEntero("Ingresa el ID del gasto a editar", 1, 99999);

    Gasto* encontrado = NULL; // DEFINICION: Inicializa un puntero vacio listo para almacenar una direccion
    for (int i = 0; i < (int)gastos.size(); i++) {
        if (gastos[i].id == id) { encontrado = &gastos[i]; break; } // FUNCION: Asigna la ubicación exacta en memoria del gasto hallado
    }

    if (!encontrado) {
        cout << ROJO << "  No se encontro un gasto con ID #" << id << ".\n" << RESET;
        pausar();
        return;
    }

    cout << AMARILLO << "\n  Datos actuales del gasto #" << id << ":\n" << RESET;
    cout << "  Descripcion : " << encontrado->descripcion << "\n"; // FUNCION: El operador '->' lee los atributos directo desde la memoria original
    cout << "  Categoria   : " << encontrado->categoria << "\n";
    cout << "  Metodo Pago : " << encontrado->metodoPago << "\n";
    cout << "  Monto       : $" << fixed << setprecision(2) << encontrado->monto << "\n";
    cout << "  Fecha       : " << encontrado->fecha << "\n";
    cout << "  Esencial    : " << (encontrado->esencial ? "Si" : "No") << "\n";

    cout << "\n  Que deseas editar?\n";
    cout << "  1-Descripcion  2-Categoria  3-Metodo Pago\n";
    cout << "  4-Monto  5-Fecha  6-Esencialidad  0-Cancelar\n";
    int campo = leerEntero("Campo a editar", 0, 6);

    if (campo == 0) { pausar(); return; }

    switch (campo) {
        case 1:
            encontrado->descripcion = leerLinea("Nueva descripcion");
            break;
        case 2: {
            cout << "  1-Hogar  2-Comida  3-Transporte  4-Educacion\n";
            cout << "  5-Salud  6-Ocio  7-Ahorro  8-Otra\n";
            int nuevaCat = leerEntero("Nueva categoria", 1, 8);
            string cats[] = {"Hogar","Comida","Transporte","Educacion","Salud","Ocio","ahorro","Otra"};
            encontrado->categoria = cats[nuevaCat - 1]; // FUNCION: Sobreescribe el texto usando la posicion relativa o que se supone deberia tener el arreglo
            break;
        }
        case 3: {
            cout << "  1-Efectivo  2-Tarjeta  3-Transferencia  4-Otro\n";
            int m = leerEntero("Nuevo metodo", 1, 4);
            string mets[] = {"Efectivo","Tarjeta","Transferencia","Otro"};
            encontrado->metodoPago = mets[m - 1]; // FUNCION: Modifica el metodo de pago original apuntando al indice mapeado
            break;
        }
        case 4:
            encontrado->monto = leerMonto();
            break;
        case 5:
            while (true) {
                encontrado->fecha = leerLinea("Nueva fecha (dd/mm/aaaa)");
                if (validarFecha(encontrado->fecha)) break;
                cout << ROJO << "  Fecha invalida.\n" << RESET;
            }
            break;
        case 6: {
            int esOp = leerEntero("Es esencial? (1=Si / 0=No)", 0, 1);
            encontrado->esencial = (esOp == 1); // COMPARADOR: Evalua la entrada entera y la transforma en bandera booleana
            break;
        }
    }

    guardarGastos(gastos);
    cout << VERDE << "\n  [OK] Gasto #" << id << " actualizado correctamente.\n" << RESET;
    pausar();
}

void eliminarGasto(vector<Gasto>& gastos) {
    imprimirTitulo("ELIMINAR GASTO");

    if (gastos.empty()) {
        cout << AMARILLO << "  No hay gastos para eliminar.\n" << RESET;
        pausar();
        return;
    }

    int id = leerEntero("Ingresa el ID del gasto a eliminar", 1, 99999);

    for (int i = 0; i < (int)gastos.size(); i++) {
        if (gastos[i].id == id) {
            cout << AMARILLO << "\n  Gasto a eliminar: " << gastos[i].descripcion
                 << " | $" << fixed << setprecision(2) << gastos[i].monto << "\n" << RESET;

            int opcion = leerEntero("Confirmar eliminacion? (1=Si / 0=No)", 0, 1); // VALIDACION: Filtra estrictamente que solo entre un 0 o un 1

            if (opcion == 1) {
                gastos.erase(gastos.begin() + i); // UTILIDADES: Borra el elemento del vector desplazando la memoria
                guardarGastos(gastos);
                cout << VERDE << "  [OK] Gasto eliminado.\n" << RESET;
            } else {
                cout << AMARILLO << "  Eliminacion cancelada.\n" << RESET;
            }
            pausar();
            return; // FUNCION: Termina el flujo de golpe al procesar con exito el ID
        }
    }
    cout << ROJO << "  No se encontro un gasto con ID #" << id << ".\n" << RESET;
    pausar();
}


//  GRAFICAS Y ESTADISTICAS


void mostrarGraficoBarras(const string& etiqueta, double valor, double maximo, int anchoMax) {
    int bloques = (maximo > 0) ? (int)((valor / maximo) * anchoMax) : 0; // FUNCION: Calcula cuantos bloques proporcionales le corresponden al valor
    cout << "  " << left << setw(16) << etiqueta << " | ";
    cout << VERDE;
    for (int i = 0; i < bloques; i++)        cout << "|"; // PRESENTACION: Relleno proporcional con barra vertical
    cout << RESET;
    for (int i = bloques; i < anchoMax; i++) cout << "."; // PRESENTACION: Espacio vacio con punto
    cout << " $" << fixed << setprecision(2) << valor << "\n";
}

void verEstadisticas(const vector<Gasto>& gastos) {
    imprimirTitulo("ESTADISTICAS Y GRAFICOS");

    if (gastos.empty()) {
        cout << AMARILLO << "  No hay gastos para analizar.\n" << RESET;
        pausar();
        return;
    }

    // DEFINICION: Arreglos de nombres para categorias y metodos, identicos a los usados en registrarGasto
    string categorias[] = {"Hogar","Comida","Transporte","Educacion","Salud","Ocio","Ahorro","Otra"};
    string metodos[]    = {"Efectivo","Tarjeta","Transferencia","Otro"};

    double totalGeneral  = 0;
    double totalCat[8]   = {0}; // DEFINICION: Acumuladores por categoria, inicializados en cero
    int    conteoMet[4]  = {0}; // DEFINICION: Contadores de uso por metodo de pago
    double totalEsencial = 0, totalNoEsencial = 0;
    int    cntEsencial   = 0,  cntNoEsencial  = 0;
    double totalSem[6]   = {0}; // DEFINICION: Indice 1-5 para las semanas del mes

    // FUNCION: Recorre todos los gastos acumulando cada indicador en su contenedor
    for (int i = 0; i < (int)gastos.size(); i++) {
        totalGeneral += gastos[i].monto;

        for (int c = 0; c < 8; c++) // COMPARADOR: Identifica la categoria del gasto y acumula su monto
            if (gastos[i].categoria == categorias[c]) { totalCat[c] += gastos[i].monto; break; }

        for (int m = 0; m < 4; m++) // COMPARADOR: Identifica el metodo de pago y suma un uso
            if (gastos[i].metodoPago == metodos[m]) { conteoMet[m]++; break; }

        if (gastos[i].esencial) { totalEsencial    += gastos[i].monto; cntEsencial++;   }
        else                    { totalNoEsencial  += gastos[i].monto; cntNoEsencial++; }

        int sem = obtenerSemana(gastos[i].fecha); // FUNCION: Clasifica el gasto en su semana del mes
        totalSem[sem] += gastos[i].monto;
    }

    // COMPARADOR: Busca la categoria con mayor gasto total
    int catMayorIdx = 0;
    for (int c = 1; c < 8; c++)
        if (totalCat[c] > totalCat[catMayorIdx]) catMayorIdx = c;

    // COMPARADOR: Busca el metodo de pago mas utilizado por cantidad de transacciones
    int metMayorIdx = 0;
    for (int m = 1; m < 4; m++)
        if (conteoMet[m] > conteoMet[metMayorIdx]) metMayorIdx = m;

    // COMPARADOR: Encuentra el valor maximo semanal para escalar las barras
    double maxSem = 0;
    for (int s = 1; s <= 5; s++)
        if (totalSem[s] > maxSem) maxSem = totalSem[s];

    double pctEsencial   = (totalGeneral > 0) ? (totalEsencial   / totalGeneral * 100.0) : 0;
    double pctNoEsencial = (totalGeneral > 0) ? (totalNoEsencial / totalGeneral * 100.0) : 0;


    // ── RESUMEN GENERAL ─────────────────────────────────────
    cout << BOLD << AMARILLO << "\n  -- RESUMEN GENERAL ----------------------------------\n" << RESET;
    cout << "  Total mensual         : " << VERDE << BOLD << "$" << fixed << setprecision(2) << totalGeneral   << RESET << "\n";
    cout << "  Gasto promedio diario : " << VERDE << "$" << fixed << setprecision(2) << totalGeneral / 30.0   << RESET << "\n";
    cout << "  Total de registros    : " << gastos.size() << "\n";


    // ── % POR CATEGORIA ─────────────────────────────────────
    cout << BOLD << AMARILLO << "\n  -- TOTAL POR CATEGORIA (% y grafico) ---------------\n" << RESET;
    for (int c = 0; c < 8; c++) {
        if (totalCat[c] <= 0) continue; // COMPARADOR: Omite categorias sin ningun gasto registrado
        double pct     = totalCat[c] / totalGeneral * 100.0;
        int    bloques = (int)(pct / 100.0 * 25); // FUNCION: Escala el porcentaje a un maximo de 25 bloques
        cout << "  " << left << setw(13) << categorias[c] << " | ";
        cout << MAGENTA;
        for (int b = 0; b < bloques; b++)  cout << "█"; // PRESENTACION: Barra proporcional al porcentaje
        cout << RESET;
        for (int b = bloques; b < 25; b++) cout << ".";
        cout << " " << fixed << setprecision(1) << pct << "% ($" << fixed << setprecision(2) << totalCat[c] << ")\n";
    }
    cout << MAGENTA << "  Categoria lider: " << BOLD << categorias[catMayorIdx]
         << " ($" << fixed << setprecision(2) << totalCat[catMayorIdx] << ")\n" << RESET;


    // ── METODO DE PAGO ──────────────────────────────────────
    cout << BOLD << AMARILLO << "\n  -- METODO DE PAGO MAS UTILIZADO --------------------\n" << RESET;
    for (int m = 0; m < 4; m++) {
        if (conteoMet[m] <= 0) continue; // COMPARADOR: Omite metodos que no tienen ninguna transaccion
        int bloques = (int)((double)conteoMet[m] / (double)conteoMet[metMayorIdx] * 20); // FUNCION: Escala relativa al metodo mas usado
        cout << "  " << left << setw(13) << metodos[m] << " | ";
        cout << AZUL;
        for (int b = 0; b < bloques; b++)  cout << "█";
        cout << RESET;
        for (int b = bloques; b < 20; b++) cout << ".";
        double pctMet = (double)conteoMet[m] / (double)gastos.size() * 100.0; // FUNCION: Porcentaje de uso respecto al total de transacciones
        cout << " " << conteoMet[m] << " uso(s) (" << fixed << setprecision(1) << pctMet << "%)\n";
    }
    cout << AZUL << "  Metodo predominante: " << BOLD << metodos[metMayorIdx] << "\n" << RESET;


    // ── ESENCIALES vs NO ESENCIALES ─────────────────────────
    cout << BOLD << AMARILLO << "\n  -- ESENCIALES vs NO ESENCIALES ---------------------\n" << RESET;
    cout << "  Esenciales    : " << cntEsencial   << " gastos | $" << fixed << setprecision(2) << totalEsencial
         << " (" << fixed << setprecision(1) << pctEsencial   << "%)\n";
    cout << "  No Esenciales : " << cntNoEsencial << " gastos | $" << fixed << setprecision(2) << totalNoEsencial
         << " (" << fixed << setprecision(1) << pctNoEsencial << "%)\n";

    // PRESENTACION: Barra bicolor, verde para esencial y rojo para no esencial, sobre 30 bloques totales
    int blqEsen = (int)(pctEsencial / 100.0 * 30);
    cout << "  Distribucion  : |";
    cout << VERDE; for (int b = 0; b < blqEsen; b++)  cout << "█";
    cout << ROJO;  for (int b = blqEsen; b < 30; b++) cout << "█";
    cout << RESET << "|\n";
    cout << "                  Verde=Esencial  Rojo=No esencial\n";


    // ── GASTO POR SEMANA ────────────────────────────────────
    cout << BOLD << AMARILLO << "\n  -- GASTO POR SEMANA DEL MES ------------------------\n" << RESET;
    for (int s = 1; s <= 5; s++) {
        if (totalSem[s] <= 0) continue; // COMPARADOR: Omite semanas sin gastos registrados
        string etiq = "Semana " + intToString(s); // UTILIDADES: Reutiliza intToString ya definida en el codigo
        double pctSem = (totalGeneral > 0) ? (totalSem[s] / totalGeneral * 100.0) : 0; // FUNCION: Porcentaje que representa la semana sobre el total mensual
        int bloquesSem = (maxSem > 0) ? (int)((totalSem[s] / maxSem) * 25) : 0;
        cout << "  " << left << setw(16) << etiq << " | ";
        cout << VERDE;
        for (int b = 0; b < bloquesSem; b++)  cout << "█"; // PRESENTACION: Barra proporcional a la semana de mayor gasto
        cout << RESET;
        for (int b = bloquesSem; b < 25; b++) cout << ".";
        cout << " " << fixed << setprecision(1) << pctSem << "% ($" << fixed << setprecision(2) << totalSem[s] << ")\n";
    }

    pausar();
}

void verGastoMasAlto(const vector<Gasto>& gastos) {
    imprimirTitulo("GASTO MAS ALTO DEL MES");

    if (gastos.empty()) {
        cout << AMARILLO << "  No hay gastos registrados.\n" << RESET;
        pausar();
        return;
    }
    // COMPARADOR: Recorre el vector guardando el indice del mayor monto encontrado
    int idxMax = 0;
    for (int i = 1; i < (int)gastos.size(); i++)
        if (gastos[i].monto > gastos[idxMax].monto) idxMax = i;

    const Gasto& g = gastos[idxMax];

    double total = 0;
    for (int i = 0; i < (int)gastos.size(); i++) total += gastos[i].monto; // FUNCION: Suma total para calcular el porcentaje representado
    double pct = (total > 0) ? (g.monto / total * 100.0) : 0;
    int bloques = (int)(pct / 100.0 * 30); // FUNCION: Escala el porcentaje a 30 bloques para la barra

    cout << MAGENTA << BOLD << "\n  ╔══ DETALLE DEL GASTO MAS ALTO ══════════════╗\n" << RESET;
    cout << CIAN << "  ║ " << RESET << left << setw(14) << "ID" << ": " << BOLD << setw(26) << g.id << RESET << CIAN << " ║\n";
    cout << CIAN << "  ║ " << RESET << left << setw(14) << "Descripcion" << ": " << BOLD << setw(26) << g.descripcion.substr(0, 26) << RESET << CIAN << " ║\n";
    cout << CIAN << "  ║ " << RESET << left << setw(14) << "Categoria" << ": " << setw(26) << g.categoria.substr(0, 26) << CIAN << " ║\n";
    cout << CIAN << "  ║ " << RESET << left << setw(14) << "Metodo Pago" << ": " << setw(26) << g.metodoPago.substr(0, 26) << CIAN << " ║\n";
    cout << CIAN << "  ║ " << RESET << left << setw(14) << "Monto" << ": " << VERDE << BOLD << "$" << fixed << setprecision(2) << g.monto << RESET;
    cout << left << setw(17) << "" << CIAN << " ║\n";
    cout << CIAN << "  ║ " << RESET << left << setw(14) << "Fecha" << ": " << setw(26) << g.fecha << CIAN << " ║\n";
    string txtEsen = g.esencial ? "SI" : "NO";
    string colorEsen = g.esencial ? VERDE : ROJO;
    cout << CIAN << "  ║ " << RESET << left << setw(14) << "Esencial" << ": " << colorEsen << BOLD << txtEsen << RESET;
    cout << left << setw(24) << "" << CIAN << " ║\n"; // Relleno de espacios fijos exactos para el SI/NO
    cout << MAGENTA << BOLD << "  ╚════════════════════════════════════════════╝\n" << RESET;
    // PRESENTACION: Barra que muestra visualmente que fraccion del total representa este gasto
    cout << "\n  Representa el " << fixed << setprecision(1) << pct << "% del total mensual:\n";
    cout << "  |";
    cout << VERDE; for (int b = 0; b < bloques; b++)  cout << "█";
    cout << RESET; for (int b = bloques; b < 30; b++) cout << ".";
    cout << "| $" << fixed << setprecision(2) << total << " total\n";

    pausar();
}


//  FUNCIONES DE ARCHIVO


void guardarGastos(const vector<Gasto>& gastos) {
    ofstream archivo(ARCHIVO.c_str()); // FUNCION: Abre el archivo en modo escritura, sobreescribiendo el contenido anterior
    if (!archivo.is_open()) {
        cout << ROJO << "  [ERROR] No se pudo abrir " << ARCHIVO << " para escritura.\n" << RESET;
        return;
    }
    for (int i = 0; i < (int)gastos.size(); i++) {
        const Gasto& g = gastos[i];
        archivo << g.id          << "|"  // DEFINICION: Formato de linea: campo1|campo2|...|campo7
                << g.descripcion << "|"
                << g.categoria   << "|"
                << g.metodoPago  << "|"
                << fixed << setprecision(2) << g.monto << "|"
                << g.fecha       << "|"
                << (g.esencial ? "1" : "0") << "\n";
    }
    archivo.close();
}

void cargarGastos(vector<Gasto>& gastos) {
    gastos.clear();
    ifstream archivo(ARCHIVO.c_str()); // FUNCION: Intenta abrir el archivo, si no existe comienza con vector vacio
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string token;
        Gasto g;

        getline(ss, token, '|'); g.id          = atoi(token.c_str()); // FUNCION: Desempaqueta cada campo usando | como delimitador
        getline(ss, g.descripcion, '|');
        getline(ss, g.categoria,   '|');
        getline(ss, g.metodoPago,  '|');
        getline(ss, token, '|');         g.monto    = atof(token.c_str());
        getline(ss, g.fecha,       '|');
        getline(ss, token, '|');         g.esencial = (token == "1");

        if (!g.descripcion.empty()) gastos.push_back(g); // VALIDACION: Descarta lineas corruptas o incompletas
    }
    archivo.close();
}

void exportarReporte(const vector<Gasto>& gastos) {
    imprimirTitulo("EXPORTAR REPORTE MENSUAL");

    if (gastos.empty()) {
        cout << AMARILLO << "  No hay gastos para exportar.\n" << RESET;
        pausar(); return;
    }

    string nombreArchivo = "Reporte_mensual.txt";
    ofstream rep(nombreArchivo.c_str()); // FUNCION: Crea el archivo de reporte en la misma carpeta del programa
    if (!rep.is_open()) {
        cout << ROJO << "  [ERROR] No se pudo crear el archivo de reporte.\n" << RESET;
        pausar(); return;
    }

    // DEFINICION: Arreglos identicos a los usados en registrarGasto para mapear categorias y metodos
    string cats[] = {"Hogar","Comida","Transporte","Educacion","Salud","Ocio","Ahorro","Otra"};
    string mets[] = {"Efectivo","Tarjeta","Transferencia","Otro"};

    double totalGeneral = 0, totalEsencial = 0, totalNoEsencial = 0;
    double totCat[8]  = {0};
    int    cntMet[4]  = {0};
    int    idxMax     = 0;

    for (int i = 0; i < (int)gastos.size(); i++) {
        totalGeneral += gastos[i].monto;
        if (gastos[i].monto > gastos[idxMax].monto) idxMax = i; // COMPARADOR: Rastrea el indice del gasto mas alto
        if (gastos[i].esencial) totalEsencial   += gastos[i].monto;
        else                    totalNoEsencial += gastos[i].monto;
        for (int c = 0; c < 8; c++) if (gastos[i].categoria  == cats[c]) { totCat[c] += gastos[i].monto; break; }
        for (int m = 0; m < 4; m++) if (gastos[i].metodoPago == mets[m]) { cntMet[m]++; break; }
    }

    // COMPARADOR: Busca categoria y metodo lideres para destacarlos en el reporte
    int catMayorIdx = 0, metMayorIdx = 0;
    for (int c = 1; c < 8; c++) if (totCat[c] > totCat[catMayorIdx]) catMayorIdx = c;
    for (int m = 1; m < 4; m++) if (cntMet[m] > cntMet[metMayorIdx]) metMayorIdx = m;

    rep << "========================================================\n";
    rep << "         REPORTE MENSUAL DE GASTOS FAMILIARES\n";
    rep << "========================================================\n\n";

    rep << "--- RESUMEN GENERAL ---\n";
    rep << "Total mensual         : $" << fixed << setprecision(2) << totalGeneral << "\n";
    rep << "Gasto promedio diario : $" << fixed << setprecision(2) << totalGeneral / 30.0 << "\n";
    rep << "Numero de registros   : " << gastos.size() << "\n\n";

    rep << "--- GASTO MAS ALTO ---\n";
    rep << "  " << gastos[idxMax].descripcion << " | $"
        << fixed << setprecision(2) << gastos[idxMax].monto
        << " | " << gastos[idxMax].fecha << "\n\n";

    rep << "--- TOTAL POR CATEGORIA ---\n";
    for (int c = 0; c < 8; c++) {
        if (totCat[c] <= 0) continue;
        double pct    = totCat[c] / totalGeneral * 100.0;
        int    bloques = (int)(pct / 100.0 * 20);
        rep << "  " << left << setw(14) << cats[c] << " |"; // PRESENTACION: Barra ASCII de barras verticales en el reporte de texto plano
        for (int b = 0; b < bloques; b++) rep << "█";
        for (int b = bloques; b < 20; b++) rep << ".";
        rep << "| " << fixed << setprecision(1) << pct << "% ($" << fixed << setprecision(2) << totCat[c] << ")\n";
    }
    rep << "  Categoria mayor consumo: " << cats[catMayorIdx]
        << " ($" << fixed << setprecision(2) << totCat[catMayorIdx] << ")\n\n";

    rep << "--- METODO DE PAGO MAS UTILIZADO ---\n";
    rep << "  " << mets[metMayorIdx] << " (" << cntMet[metMayorIdx] << " transacciones)\n\n";

    rep << "--- ESENCIALES vs NO ESENCIALES ---\n";
    rep << "  Esenciales    : $" << fixed << setprecision(2) << totalEsencial
        << " (" << fixed << setprecision(1) << (totalGeneral > 0 ? totalEsencial / totalGeneral * 100.0 : 0) << "%)\n";
    rep << "  No Esenciales : $" << fixed << setprecision(2) << totalNoEsencial
        << " (" << fixed << setprecision(1) << (totalGeneral > 0 ? totalNoEsencial / totalGeneral * 100.0 : 0) << "%)\n\n";

    rep << "--- LISTADO COMPLETO DE GASTOS (ordenado por monto) ---\n";
    rep << left << setw(4) << "ID" << " | " << setw(24) << "Descripcion"
        << " | " << setw(13) << "Categoria" << " | " << setw(13) << "Metodo"
        << " | " << right << setw(9) << "Monto" << " | Fecha       | Esencial\n";
    rep << string(95, '-') << "\n";

    vector<Gasto> ordenados = gastos;
    sort(ordenados.begin(), ordenados.end(), compararMontoDesc); // FUNCION: Reutiliza el comparador global para ordenar de mayor a menor
    for (int i = 0; i < (int)ordenados.size(); i++) {
        const Gasto& g = ordenados[i];
        rep << left  << setw(4) << g.id << " | " << setw(24) << g.descripcion.substr(0, 23)
            << " | " << setw(13) << g.categoria.substr(0, 12)
            << " | " << setw(13) << g.metodoPago.substr(0, 12)
            << " | $" << right << setw(8) << fixed << setprecision(2) << g.monto
            << " | " << g.fecha
            << " | " << (g.esencial ? "SI" : "NO") << "\n";
    }

    rep << "\n========================================================\n";
    rep.close();

    cout << VERDE << BOLD << "\n  [OK] Reporte exportado exitosamente a: " << nombreArchivo << "\n" << RESET;
    pausar();
}