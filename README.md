[Manual_Gestor_Gastos.md](https://github.com/user-attachments/files/28486624/Manual_Gestor_Gastos.md)
**UNIVERSIDAD DISTRITAL** 

**==> picture [612 x 50] intentionally omitted <==**

Francisco José de Caldas  ·  Programación Básica 

## **MANUAL DE USUARIO** 

## Gestor de Gastos Mensuales 

Versión 1.0  ·  C++ 

**==> picture [612 x 51] intentionally omitted <==**

## **Desarrolladores** 

Juan Pablo Melo González Juan David López Rincón Juan Felipe Fuentes Jiménez 

Manual de Usuario — Gestor de Gastos Mensuales   v1.0 

## **1.  INTRODUCCIÓN** 

El Gestor de Gastos Mensuales es un programa diseñado en C++ para que familias y usuarios individuales lleven un control claro y organizado de sus finanzas. Todos los datos se guardan automáticamente en el archivo Gastos.txt, por lo que la información persiste entre sesiones. 

El programa permite visualizar gastos en tablas, modificarlos, eliminarlos, filtrarlos por categoría o rango de fechas, y exportar reportes mensuales en texto plano. 

## **2.  REQUISITOS DEL SISTEMA** 

Para ejecutar correctamente el programa se necesita: 

- Sistema Operativo: Windows (el programa usa librerías específicas de Windows como windows.h y conio.h) 

- Compilador: C++ estándar con soporte C++11 o superior 

- Permisos de lectura/escritura en la carpeta donde se ubique el ejecutable 

## **3.  INSTALACIÓN Y EJECUCIÓN** 

1. Descarga o copia el archivo Proyecto-Final-v1.cpp en tu equipo. 

2. Compílalo con tu compilador C++ preferido (Dev C++, Visual Studio, etc) 

3. Ejecuta el programa resultante desde la consola de Windows. 

4. Al iniciar por primera vez se creará automáticamente el archivo Gastos.txt en la misma carpeta. 

💡  Si el programa no arranca, asegúrate de ejecutarlo desde una consola de Windows (CMD o PowerShell) y no con doble clic, para ver posibles mensajes de error. 

## **4.  NAVEGACIÓN DEL MENÚ PRINCIPAL** 

Al iniciar el programa verás el menú interactivo. Usa los siguientes controles para navegar: 

|||
|---|---|
|**Tecla / Acción**|**Función**|
|||
|||
|Flechas▲/▼|Desplazarse entre opciones del menú|
|||
|||
|ENTER|Seleccionar la opción resaltada|
|||
|||
|ENTER (campo vacío)|Cancelar la entrada actual|
|||



Universidad Distrital Francisco José de Caldas  ·  Programación Básica 

Página 2 

Manual de Usuario — Gestor de Gastos Mensuales   v1.0 

_Figura 1 — Menú principal del Gestor de Gastos_ 

## **5.  GUÍA DETALLADA DE FUNCIONES** 

## **5.1  Registrar un nuevo gasto (Opción 1)** 

Permite ingresar un gasto con todos sus detalles. El proceso sigue estos pasos: 

5. Ingresa una descripción del gasto (ej: "Compra de alimentos"). No puede estar vacía. 

6. Selecciona una categoría de la lista disponible: 

**==> picture [270 x 170] intentionally omitted <==**

**----- Start of picture text -----**<br>
Opción Categoría<br>1 Hogar<br>2 Comida<br>3 Transporte<br>4 Educación<br>5 Salud<br>6 Ocio<br>7 Ahorro<br>8 Otra<br>**----- End of picture text -----**<br>


7. Selecciona el método de pago: 

|**Opción**|**Método**|
|---|---|
|1|Efectivo|



Universidad Distrital Francisco José de Caldas  ·  Programación Básica 

Página 3 

Manual de Usuario — Gestor de Gastos Mensuales   v1.0 

|2|Tarjeta|
|---|---|
|3|Transferencia|
|4|Otro|



8. Ingresa el monto (debe ser un número mayor que 0). 

9. Ingresa la fecha en formato dd/mm/aaaa (ej: 15/06/2026). El programa valida la fecha y considera años bisiestos. 

- 10.Indica si es un gasto esencial (1 = Sí / 0 = No). 

_Figura 2 — Ejemplo de registro de un nuevo gasto_ 

⚠️  Advertencia: Gastos esenciales son aquellos indispensables (alimentación, servicios, transporte obligatorio). Los no esenciales incluyen entretenimiento, lujos y caprichos. 

## **5.2  Ver todos los gastos (Opción 2)** 

Muestra una tabla completa con todos los gastos registrados, ordenados de mayor a menor monto. Al final aparece el total acumulado. 

Columnas de la tabla: 

_Figura 3 — Cabecera de la tabla de gastos_ 

Universidad Distrital Francisco José de Caldas  ·  Programación Básica 

Página 4 

Manual de Usuario — Gestor de Gastos Mensuales   v1.0 

- ID: Identificador único del gasto 

- Descripción: Texto descriptivo ingresado al registrar 

- Categoría: Clasificación del gasto 

- Método de pago: Forma en que se realizó el pago 

- Monto: Cantidad de dinero 

- Fecha: Cuándo ocurrió el gasto 

- Esencial: SI (verde) / NO (rojo) 

## **5.3  Buscar por categoría (Opción 3)** 

Filtra y muestra únicamente los gastos que pertenezcan a la categoría seleccionada (1-8). Los resultados se ordenan por monto descendente y se muestra el subtotal de la categoría. 

ℹ️  Si no hay gastos registrados en la categoría elegida, el programa lo indicará con un mensaje informativo. 

## **5.4  Buscar por rango de fechas (Opción 4)** 

Permite filtrar gastos dentro de un período específico. Pasos: 

- 11.Ingresa la fecha de inicio en formato dd/mm/aaaa. 

- 12.Ingresa la fecha de fin en formato dd/mm/aaaa. 

- 13.El programa mostrará todos los gastos comprendidos en ese rango y el total parcial. 

_Figura 4 — Resultado de búsqueda por rango de fechas (junio 2026)_ 

## **5.5  Estadísticas y gráficos (Opción 5)** 

Genera un análisis visual completo con gráficos ASCII. Incluye las siguientes secciones: 

Universidad Distrital Francisco José de Caldas  ·  Programación Básica 

Página 5 

Manual de Usuario — Gestor de Gastos Mensuales   v1.0 

- Resumen General: total mensual, promedio diario, cantidad de registros 

- Total por Categoría: gráfico de barras, porcentaje del total y categoría con mayor gasto 

- Método de Pago Más Utilizado: cantidad de usos por método y porcentaje 

- Esenciales vs No Esenciales: barra bicolor (verde / rojo) con porcentajes 

- Gasto por Semana del Mes: desglose por semanas (sem. 1: días 1-7, sem. 2: 8-14, sem. 3: 15-21, sem. 4: 22-28, sem. 5: 29-31) 

## **5.6  Ver gasto más alto (Opción 6)** 

Muestra en detalle el registro de mayor monto: ID, descripción, categoría, método de pago, monto exacto, fecha, esencialidad, y un gráfico visual que indica qué porcentaje representa del total acumulado. 

## **5.7  Editar un gasto (Opción 7)** 

Permite modificar cualquier campo de un gasto ya registrado. Pasos: 

- 14.Ingresa el ID del gasto a editar (consultable en la Opción 2). 

- 15.El programa muestra los datos actuales del gasto. 

- 16.Selecciona el campo que deseas modificar: 

|||
|---|---|
|**Opción**|**Campo editable**|
|||
|||
|1|Descripción|
|||
|||
|2|Categoría|
|||
|||
|3|Método de pago|
|||
|||
|4|Monto|
|||
|5|Fecha|
|||
|6|Esencial|
|||
|0|Cancelar|
|||



- 17.Ingresa el nuevo valor. Los cambios se guardan automáticamente. 

Universidad Distrital Francisco José de Caldas  ·  Programación Básica 

Página 6 

Manual de Usuario — Gestor de Gastos Mensuales   v1.0 

_Figura 5 — Flujo de edición de un gasto existente_ 

ℹ️  Nota: El campo ID no puede editarse porque es el identificador único del registro. 

## **5.8  Eliminar un gasto (Opción 8)** 

Elimina permanentemente un gasto del sistema. Pasos: 

- 18.Ingresa el ID del gasto a eliminar. 

- 19.El programa muestra el gasto para que lo confirmes. 

- 20.Confirma con 1=Sí o cancela con 0=No. 

- 21.Si confirmas, el gasto se elimina y los cambios se guardan de inmediato. 

⚠️  Advertencia: La eliminación es permanente. No existe función de deshacer. 

## **5.9  Exportar reporte mensual (Opción 9)** 

Genera el archivo reporte_mensual.txt en la misma carpeta del programa. El reporte incluye: 

- Resumen general (total mensual, promedio diario) 

- Gasto más alto del mes 

- Gráfico ASCII de gastos por categoría 

Universidad Distrital Francisco José de Caldas  ·  Programación Básica 

Página 7 

Manual de Usuario — Gestor de Gastos Mensuales   v1.0 

- Método de pago más utilizado 

- Desglose esencial / no esencial 

- Tabla completa de todos los gastos ordenados por monto 

El archivo puede abrirse con cualquier editor de texto y compartirse fácilmente. 

## **5.10  Reiniciar programa (Opción 10)** 

Recarga los datos desde Gastos.txt sin eliminar ningún registro. Útil cuando otro usuario ha agregado datos desde la misma carpeta. Limpia la pantalla y regresa al menú principal. 

## **6.  ARCHIVOS DEL SISTEMA** 

||||
|---|---|---|
|**Archivo**|**Descripción**|**Generado por**|
||||
||||
|Gastos.txt|Almacena todos los registros separados por pipes<br>(|). No editar manualmente.|Automático al registrar /<br>editar|
||||
||||
|reporte_mensual.txt|Reporte completo del mes en texto plano legible.|Opción 9 — Exportar<br>reporte|
||||



⚠️  No edites manualmente el archivo Gastos.txt. Podría corromper los datos y hacer que el programa falle al cargar. 

## **7.  VALIDACIONES Y RESTRICCIONES** 

|||
|---|---|
|**CAMPO**|**VALIDACIÓN**|
|||
|||
|**Descripción**|No puede estar vacía|
|||
|||
|**Categoría**|Debe ser un número entre 1 y 8|
|||
|||
|**Método de pago**|Debe ser un número entre 1 y 4|
|||
|||
|**Monto**|Debe ser un número mayor que 0|
|||
|||
|**Fecha**|Formato dd/mm/aaaa y que la fecha exista (considera años bisiestos)|
|||
|||
|**Esencial**|Solo 0 (No) o 1 (Sí)|
|||
|||
|**ID (edición/eliminación)**|Debe corresponder a un registro existente|
|||
|||
|**Rango de fechas**|Ambas fechas deben ser válidas y en formato correcto|
|||



Universidad Distrital Francisco José de Caldas  ·  Programación Básica 

Página 8 

Manual de Usuario — Gestor de Gastos Mensuales   v1.0 

## **8.  CONSEJOS Y BUENAS PRÁCTICAS** 

- ✅  Registra los gastos con frecuencia — no esperes a fin de mes. 

- ✅  Sé específico en las descripciones para facilitar búsquedas futuras. 

- ✅  Clasifica correctamente cada gasto — las estadísticas dependen de ello. 

- ✅  Marca la esencialidad — ayuda a distinguir lujos de necesidades. 

- ✅  Haz copias de seguridad periódicas del archivo Gastos.txt. 

- ✅  Exporta y revisa el reporte mensual para identificar patrones de gasto. 

## **9.  SOLUCIÓN DE PROBLEMAS** 

## **"No se puede abrir Gastos.txt para escritura"** 

Causa: Permisos insuficientes o archivo corrupto. 

Solución: Ejecuta el programa como administrador, o elimina el archivo Gastos.txt y deja que el programa cree uno nuevo. 

## **"Fecha inválida"** 

Causa: Formato incorrecto o fecha que no existe (ej: 31/02/2026). 

Solución: Verifica que el formato sea exactamente dd/mm/aaaa y que la fecha sea real. 

## **"Error: opción inválida"** 

Causa: Ingresaste un valor fuera del rango permitido. 

Solución: Elige solo dentro del rango indicado en pantalla (ej: 1-8 para categorías). 

## **"No se encontró un gasto con ID #X"** 

Causa: El ID no existe en el sistema. 

Solución: Consulta los IDs válidos usando la Opción 2 — Ver todos los gastos. 

## **Los datos no se guardan** 

Causa: El programa fue cerrado de forma forzada sin pasar por la Opción 0 — Salir. 

Solución: Siempre usa la opción 0 para cerrar correctamente y asegurarte de que los datos queden guardados. 

## **10.  INFORMACIÓN TÉCNICA** 

Universidad Distrital Francisco José de Caldas  ·  Programación Básica 

Página 9 

Manual de Usuario — Gestor de Gastos Mensuales   v1.0 

|||
|---|---|
|**Aspecto**|**Detalle**|
|||
|||
|Lenguaje|C++ (estándar C++11 o superior)|
|||
|Versión|1.0|
|||
|Máx. registros|500 gastos (configurable modificando MAX_GASTOS en el código)|
|||
|||
|Librerías usadas|iostream, fstream, sstream, string, vector, algorithm, iomanip, limits,<br>windows.h, conio.h|
|||
|Plataforma|Windows|
|||
|Persistencia|Archivo de texto plano (Gastos.txt) con campos separados por pipe (|)|
|||



Desarrolladores: Juan Pablo Melo González · Juan David López Rincón · Juan Felipe Fuentes Jiménez 

Universidad Distrital Francisco José de Caldas  ·  Programación Básica 

Página 10 

