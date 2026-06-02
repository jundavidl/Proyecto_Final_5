# 💰 Gestor de Gastos Mensuales

Aplicación de consola en **C++** para que familias y usuarios individuales lleven un control claro y organizado de sus finanzas. Todos los datos se guardan automáticamente en el archivo `Gastos.txt`, por lo que la información persiste entre sesiones.

Desarrollada como proyecto final para la asignatura de Programación Básica — Universidad Distrital Francisco José de Caldas.

---

## 👥 Desarrolladores

| Nombre |
|--------|
| Juan Pablo Melo González |
| Juan David López Rincón |
| Juan Felipe Fuentes Jiménez |

---

## 📋 Características

- Registrar gastos con descripción, categoría, método de pago, monto, fecha y esencialidad
- Ver todos los gastos en tabla ordenada de mayor a menor monto
- Buscar gastos por categoría
- Buscar gastos por rango de fechas
- Estadísticas y gráficos ASCII (por categoría, método de pago, semana del mes, esencial vs no esencial)
- Ver el gasto más alto del mes
- Editar cualquier campo de un gasto existente
- Eliminar gastos con confirmación
- Exportar reporte mensual en `.txt`
- Reiniciar / recargar datos desde archivo

---

## ⚙️ Requisitos del sistema

| Requisito | Detalle |
|-----------|---------|
| Sistema Operativo | Windows |
| Compilador | C++11 o superior |
| Librerías especiales | `windows.h`, `conio.h` |
| Permisos | Lectura y escritura en la carpeta del ejecutable |

> ⚠️ El programa usa librerías exclusivas de Windows y **no es compatible con Linux o macOS** sin modificaciones.

---

## 🚀 Instalación y ejecución

1. Descarga o copia el archivo `Proyecto-Final-v1.cpp` en tu equipo.
2. Compílalo con tu compilador C++ preferido (Dev C++, Visual Studio, MinGW, etc.).
3. Ejecuta el binario resultante **desde una terminal de Windows** (CMD o PowerShell).
4. Al iniciar por primera vez, se creará automáticamente el archivo `Gastos.txt` en la misma carpeta.

```bash
# Ejemplo con g++ (MinGW)
g++ -o GestorGastos Proyecto-Final-v1.cpp -std=c++11
./GestorGastos.exe
```

> 💡 Ejecuta siempre desde la consola (no con doble clic) para poder ver mensajes de error si algo falla.

---

## 🧭 Navegación del menú principal

Navega con las flechas `▲ / ▼` y confirma con `ENTER`. Presionar `ENTER` en un campo vacío cancela la entrada actual.

```
 1. Registrar gasto
 2. Ver todos los gastos (tabla)
 3. Buscar por categoría
 4. Buscar por rango de fechas
 5. Estadísticas y gráficos ASCII
 6. Ver gasto más alto del mes
 7. Editar un gasto existente
 8. Eliminar un gasto
 9. Exportar reporte mensual (.txt)
10. Reiniciar programa
 0. Salir
```

---

## 📖 Guía detallada de funciones

### 1. Registrar un nuevo gasto

Permite ingresar un gasto con todos sus detalles. El proceso sigue estos pasos:

1. Ingresa una **descripción** del gasto (ej: `Compra de alimentos`). No puede estar vacía.
2. Selecciona una **categoría**:

| Opción | Categoría |
|--------|-----------|
| 1 | Hogar |
| 2 | Comida |
| 3 | Transporte |
| 4 | Educación |
| 5 | Salud |
| 6 | Ocio |
| 7 | Ahorro |
| 8 | Otra |

3. Selecciona el **método de pago**:

| Opción | Método |
|--------|--------|
| 1 | Efectivo |
| 2 | Tarjeta |
| 3 | Transferencia |
| 4 | Otro |

4. Ingresa el **monto** (debe ser un número mayor que 0).
5. Ingresa la **fecha** en formato `dd/mm/aaaa` (ej: `15/06/2026`). El programa valida la fecha y considera años bisiestos.
6. Indica si es un **gasto esencial** (`1` = Sí / `0` = No).

> ⚠️ **Gastos esenciales** son aquellos indispensables (alimentación, servicios, transporte obligatorio). Los **no esenciales** incluyen entretenimiento, lujos y caprichos.

---

### 2. Ver todos los gastos

Muestra una tabla completa con todos los gastos registrados, ordenados de **mayor a menor monto**. Al final aparece el total acumulado.

Columnas de la tabla:

| Columna | Descripción |
|---------|-------------|
| ID | Identificador único del gasto |
| Descripción | Texto descriptivo ingresado al registrar |
| Categoría | Clasificación del gasto |
| Método de pago | Forma en que se realizó el pago |
| Monto | Cantidad de dinero |
| Fecha | Cuándo ocurrió el gasto |
| Esencial | **SI** (verde) / **NO** (rojo) |

---

### 3. Buscar por categoría

Filtra y muestra únicamente los gastos que pertenezcan a la categoría seleccionada (1–8). Los resultados se ordenan por monto descendente y se muestra el **subtotal de la categoría**.

> ℹ️ Si no hay gastos registrados en la categoría elegida, el programa lo indicará con un mensaje informativo.

---

### 4. Buscar por rango de fechas

Permite filtrar gastos dentro de un período específico. Pasos:

1. Ingresa la **fecha de inicio** en formato `dd/mm/aaaa`.
2. Ingresa la **fecha de fin** en formato `dd/mm/aaaa`.
3. El programa mostrará todos los gastos comprendidos en ese rango y el **total parcial**.

---

### 5. Estadísticas y gráficos ASCII

Genera un análisis visual completo con gráficos ASCII. Incluye las siguientes secciones:

- **Resumen general:** total mensual, promedio diario, cantidad de registros.
- **Total por categoría:** gráfico de barras, porcentaje del total y categoría con mayor gasto.
- **Método de pago más utilizado:** cantidad de usos por método y porcentaje.
- **Esenciales vs No esenciales:** barra bicolor (verde / rojo) con porcentajes.
- **Gasto por semana del mes:** desglose por semanas:
  - Semana 1: días 1–7
  - Semana 2: días 8–14
  - Semana 3: días 15–21
  - Semana 4: días 22–28
  - Semana 5: días 29–31

---

### 6. Ver gasto más alto

Muestra en detalle el registro de mayor monto: ID, descripción, categoría, método de pago, monto exacto, fecha, esencialidad, y un **gráfico visual** que indica qué porcentaje representa del total acumulado.

---

### 7. Editar un gasto existente

Permite modificar cualquier campo de un gasto ya registrado. Pasos:

1. Ingresa el **ID** del gasto a editar (consultable en la Opción 2).
2. El programa muestra los datos actuales del gasto.
3. Selecciona el campo que deseas modificar:

| Opción | Campo editable |
|--------|----------------|
| 1 | Descripción |
| 2 | Categoría |
| 3 | Método de pago |
| 4 | Monto |
| 5 | Fecha |
| 6 | Esencial |
| 0 | Cancelar |

4. Ingresa el nuevo valor. Los cambios se guardan automáticamente.

> ℹ️ El campo **ID** no puede editarse porque es el identificador único del registro.

---

### 8. Eliminar un gasto

Elimina permanentemente un gasto del sistema. Pasos:

1. Ingresa el **ID** del gasto a eliminar.
2. El programa muestra el gasto para que lo confirmes.
3. Confirma con `1` = Sí o cancela con `0` = No.
4. Si confirmas, el gasto se elimina y los cambios se guardan de inmediato.

> ⚠️ **La eliminación es permanente. No existe función de deshacer.**

---

### 9. Exportar reporte mensual

Genera el archivo `reporte_mensual.txt` en la misma carpeta del programa. El reporte incluye:

- Resumen general (total mensual, promedio diario)
- Gasto más alto del mes
- Gráfico ASCII de gastos por categoría
- Método de pago más utilizado
- Desglose esencial / no esencial
- Tabla completa de todos los gastos ordenados por monto

El archivo puede abrirse con cualquier editor de texto y compartirse fácilmente.

---

### 10. Reiniciar programa

Recarga los datos desde `Gastos.txt` sin eliminar ningún registro. Útil cuando otro usuario ha agregado datos desde la misma carpeta. Limpia la pantalla y regresa al menú principal.

---

## 🗂️ Archivos del sistema

| Archivo | Descripción | Generado por |
|---------|-------------|--------------|
| `Gastos.txt` | Almacena todos los registros separados por pipes (`\|`). **No editar manualmente.** | Automático al registrar / editar |
| `reporte_mensual.txt` | Reporte completo del mes en texto plano legible. | Opción 9 — Exportar reporte |

> ⚠️ No edites manualmente el archivo `Gastos.txt`. Podría corromper los datos y hacer que el programa falle al cargar.

---

## ✅ Validaciones y restricciones

| Campo | Validación |
|-------|------------|
| Descripción | No puede estar vacía |
| Categoría | Número entre 1 y 8 |
| Método de pago | Número entre 1 y 4 |
| Monto | Número mayor que 0 |
| Fecha | Formato `dd/mm/aaaa` y que la fecha exista (considera años bisiestos) |
| Esencial | Solo `0` (No) o `1` (Sí) |
| ID (edición/eliminación) | Debe corresponder a un registro existente |
| Rango de fechas | Ambas fechas deben ser válidas y en formato correcto |

---


## 📌 Buenas prácticas

- ✅ Registra los gastos con frecuencia — no esperes a fin de mes.
- ✅ Sé específico en las descripciones para facilitar búsquedas futuras.
- ✅ Clasifica correctamente cada gasto — las estadísticas dependen de ello.
- ✅ Marca la esencialidad — ayuda a distinguir lujos de necesidades.
- ✅ Haz copias de seguridad periódicas del archivo `Gastos.txt`.
- ✅ Exporta y revisa el reporte mensual para identificar patrones de gasto.

---

## ❗ Solución de problemas

**`No se puede abrir Gastos.txt para escritura`**
> Causa: Permisos insuficientes o archivo corrupto.
> Solución: Ejecuta el programa como administrador, o elimina `Gastos.txt` y deja que el programa cree uno nuevo.

**`Fecha inválida`**
> Causa: Formato incorrecto o fecha que no existe (ej: `31/02/2026`).
> Solución: Verifica que el formato sea exactamente `dd/mm/aaaa` y que la fecha sea real.

**`Error: opción inválida`**
> Causa: Ingresaste un valor fuera del rango permitido.
> Solución: Elige solo dentro del rango indicado en pantalla (ej: 1–8 para categorías).

**`No se encontró un gasto con ID #X`**
> Causa: El ID no existe en el sistema.
> Solución: Consulta los IDs válidos usando la Opción 2 — Ver todos los gastos.

**Los datos no se guardan**
> Causa: El programa fue cerrado de forma forzada sin pasar por la Opción 0 — Salir.
> Solución: Siempre usa la opción `0` para cerrar correctamente y asegurarte de que los datos queden guardados.

---

## 🔧 Detalles técnicos

| Aspecto | Detalle |
|---------|---------|
| Lenguaje | C++ (estándar C++11 o superior) |
| Versión | 1.0 |
| Máx. registros | 500 (configurable modificando `MAX_GASTOS` en el código) |
| Librerías usadas | `iostream`, `fstream`, `sstream`, `string`, `vector`, `algorithm`, `iomanip`, `limits`, `windows.h`, `conio.h` |
| Plataforma | Windows |
| Persistencia | Archivo de texto plano (`Gastos.txt`) con campos separados por pipe (`\|`) |

---

*Universidad Distrital Francisco José de Caldas · Programación Básica · 2026*
