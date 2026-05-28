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

    //cargarGastos(gastos); FUNCION: Persistencia fisica de datos en disco (Se habilitara al definirla)
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
                case 5: // verEstadisticas(gastos);
                        cout << AMARILLO << "\n  [Aviso] Funcion de reporte aun no definida.\n" << RESET;
                        pausar();
                        break; 
                case 6: // verGastoMasAlto(gastos);
                        cout << AMARILLO << "\n  [Aviso] Funcion de reporte aun no definida.\n" << RESET;
                        pausar();
                        break; 
                case 7: // editarGasto(gastos);
                        cout << AMARILLO << "\n  [Aviso] Funcion de reporte aun no definida.\n" << RESET;
                        pausar();
                        break;  
                case 8: // eliminarGasto(gastos); 
                        cout << AMARILLO << "\n  [Aviso] Funcion de reporte aun no definida.\n" << RESET;
                        pausar();
                        break; 
                case 9: // exportarReporte(gastos);  
                        cout << AMARILLO << "\n  [Aviso] Funcion de reporte aun no definida.\n" << RESET;
                        pausar();
                        break; 
                case 10:// cargarGastos(gastos); 
                        cout << AMARILLO << "\n  [Aviso] Funcion de reporte aun no definida.\n" << RESET;
                        pausar();
                        break; 
                case 0: // guardarGastos(gastos); 
                        limpiarPantalla();
                        cout << "\n\n";
                        cout << AMARILLO << BOLD << "  Guardando y saliendo..." << RESET << "\n";
                        cout << AMARILLO << "  ¡Hasta pronto usuario, tenga un gran día!\n\n" << RESET;
                        //guardarGastos(gastos); FUNCION: Persistencia fisica de datos en disco (Se habilitara al definirla)
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
    if (seleccionada == 8) cout << BOLD << AMARILLO << " > 8.  Eliminar un gasto                     " << RESET;
    else                   cout << AMARILLO << "   8." << RESET << "  Eliminar un gasto                     ";
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // FUNCION: Limpieza completa del bufer
    cin.get();
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
    double monto;
    while (true) {
        cout << "  Monto: ";
        if (cin >> monto && monto > 0) {
            cin.ignore();
            return monto;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ROJO << "  Error: ingresa un monto valido (mayor que 0).\n" << RESET;
    }
}

int leerEntero(const string& mensaje, int minimo, int maximo) {
    int valor;
    while (true) {
        cout << "  " << mensaje << " [" << minimo << "-" << maximo << "]: "; 
        if (cin >> valor && valor >= minimo && valor <= maximo) { // VALIDACION: Revisa que sea numero y este en el rango permitido
            cin.ignore();
            return valor; // FUNCION: Retorna el numero entero validado de forma exitosa
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ROJO << "  Error: opcion invalida. Intenta de nuevo.\n" << RESET;
    }
}

string leerLinea(const string& mensaje) {
    string texto;
    cout << "  " << mensaje << ": "; // UTILIDADES: FForma base para cualquier ingreso de datos
    getline(cin, texto);
    return texto;
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

    cout << "\n  Es un gasto esencial? (1=Si / 0=No): ";
    int esOpcional;
    cin >> esOpcional;
    cin.ignore();
    g.esencial = (esOpcional == 1); // COMPARADOR: Convierte el 1 o 0 ingresado a un valor booleano

    gastos.push_back(g); // UTILIDADES: Inserta el nuevo registro al final del vector
    //guardarGastos(gastos); FUNCION: Persistencia fisica de datos en disco (Se habilitara al definirla)

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
            cout << "  Es esencial? (1=Si / 0=No): ";
            int esOp; cin >> esOp; cin.ignore();
            encontrado->esencial = (esOp == 1); // COMPARADOR: Evalua la entrada entera y la transforma en bandera booleana
            break;
        }
    }

    //guardarGastos(gastos); FUNCION: Persistencia fisica de datos en disco (Se habilitara al definirla)
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
                //guardarGastos(gastos); FUNCION: Persistencia fisica de datos en disco (Se habilitara al definirla)
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
