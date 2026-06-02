# 💰 Gestor de Gastos Mensuales

Aplicación de consola en **C++** para llevar un registro organizado de gastos personales o familiares. Desarrollada como proyecto final para la asignatura de Programación Básica — Universidad Distrital Francisco José de Caldas.

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

> ⚠️ El programa usa librerías exclusivas de Windows (`windows.h`, `conio.h`) y **no es compatible con Linux o macOS** sin modificaciones.

---

## 🚀 Instalación y ejecución

1. Descarga o clona el repositorio.
2. Compila `Proyecto-Final-v1.cpp` con tu compilador preferido (Dev C++, Visual Studio, MinGW, etc.).
3. Ejecuta el binario resultante **desde una terminal de Windows** (CMD o PowerShell).
4. Al iniciar por primera vez, se creará automáticamente el archivo `Gastos.txt` en la misma carpeta.

```bash
# Ejemplo con g++ (MinGW)
g++ -o GestorGastos Proyecto-Final-v1.cpp -std=c++11
./GestorGastos.exe
```

> 💡 Ejecuta siempre desde la consola (no con doble clic) para poder ver mensajes de error si algo falla.

---

## 🗂️ Archivos del sistema

| Archivo | Descripción |
|---------|-------------|
| `Gastos.txt` | Base de datos del programa. Campos separados por `\|`. **No editar manualmente.** |
| `reporte_mensual.txt` | Reporte exportable en texto plano. Generado con la Opción 9. |

---

## 🧭 Menú principal

Navega con las flechas `▲ / ▼` y confirma con `ENTER`.

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

## 📝 Categorías disponibles

| # | Categoría |
|---|-----------|
| 1 | Hogar |
| 2 | Comida |
| 3 | Transporte |
| 4 | Educación |
| 5 | Salud |
| 6 | Ocio |
| 7 | Ahorro |
| 8 | Otra |

---

## 💳 Métodos de pago

| # | Método |
|---|--------|
| 1 | Efectivo |
| 2 | Tarjeta |
| 3 | Transferencia |
| 4 | Otro |

---

## 📤 Exportar reporte mensual (Opción 9)

Genera el archivo `reporte_mensual.txt` en la misma carpeta del ejecutable. Incluye:

- Resumen general (total mensual y promedio diario)
- Gasto más alto del mes
- Gráfico ASCII de gastos por categoría
- Método de pago más utilizado
- Desglose esencial / no esencial
- Tabla completa de todos los gastos ordenados por monto

El archivo puede abrirse con cualquier editor de texto y compartirse fácilmente.

---

## 🔄 Reiniciar programa (Opción 10)

Recarga los datos desde `Gastos.txt` sin eliminar ningún registro. Útil cuando otro usuario ha agregado datos desde la misma carpeta. Limpia la pantalla y regresa al menú principal.

---

## ✅ Validaciones

| Campo | Regla |
|-------|-------|
| Descripción | No puede estar vacía |
| Categoría | Número entre 1 y 8 |
| Método de pago | Número entre 1 y 4 |
| Monto | Número mayor que 0 |
| Fecha | Formato `dd/mm/aaaa`, fecha real (considera años bisiestos) |
| Esencial | Solo `0` (No) o `1` (Sí) |
| ID (editar/eliminar) | Debe corresponder a un registro existente |

---

## 🔧 Detalles técnicos

| Aspecto | Detalle |
|---------|---------|
| Lenguaje | C++ (estándar C++11 o superior) |
| Versión | 1.0 |
| Máx. registros | 500 (modificable en `MAX_GASTOS`) |
| Persistencia | Archivo de texto plano con campos separados por `\|` |
| Plataforma | Windows |

---

## ❗ Solución de problemas

**`No se puede abrir Gastos.txt para escritura`**
→ Ejecuta el programa como administrador, o elimina `Gastos.txt` para que se cree uno nuevo.

**`Fecha inválida`**
→ Verifica que el formato sea exactamente `dd/mm/aaaa` y que la fecha exista.

**`No se encontró un gasto con ID #X`**
→ Consulta los IDs válidos con la Opción 2 — Ver todos los gastos.

**Los datos no se guardan**
→ Siempre cierra el programa usando la Opción 0 — Salir, no cerrando la consola a la fuerza.

---

## 📌 Buenas prácticas

- Registra gastos con frecuencia, no esperes a fin de mes.
- Sé específico en las descripciones para facilitar búsquedas.
- Clasifica correctamente cada gasto; las estadísticas dependen de ello.
- Marca la esencialidad para distinguir necesidades de lujos.
- Haz copias periódicas de `Gastos.txt`.
- Exporta y revisa el reporte mensual para identificar patrones de gasto.

---

*Universidad Distrital Francisco José de Caldas · Programación Básica · 2026*
