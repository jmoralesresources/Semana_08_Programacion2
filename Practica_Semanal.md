| <div align="right"><img src="../../Logo-UNA-Rojo_FondoTransparente%20(2).png" width="120" alt="Logo UNA" /></div> | | <p align="right"><img src="../../images.jpeg" width="120" alt="Logo EscINF" /></p> |
|:----------------------------------------------------|:-------------------------------------------------------------:|------------------------------------------------------------:|

**Programa de curso** · **Programación II**  
**Carrera:** Ingeniería de Sistemas de Información con grado en Bachillerato y salida lateral de Diplomado en Programación de Aplicaciones Informáticas.

---

# Semana 8 – Práctica semanal

**Contenidos:** Regla de tres/cinco, Sobrecarga de operadores, Patrón Singleton, Patrón Adapter.  
**Nota:** Primer examen parcial (domingo 19 de abril, 8:00 a.m., según cronograma).

---

## Actividad 1 (Regla de cinco)

- Implemente la clase `Buffer` con recurso dinámico (array de char). Incluya destructor, copia y asignación por copia, y por movimiento.
- Pruebe copia y movimiento; verifique que no hay fugas ni doble liberación. Documente en MD el estado del objeto fuente después de un movimiento.

---

## Actividad 2 (Sobrecarga y Singleton)

- Implemente `Complejo` con sobrecarga de `+`, `-` y `<<`. Use al menos un operador como función no miembro.
- Implemente Singleton "Configuracion" con `getInstance()` y métodos de lectura. En MD comente un riesgo en entorno multihilo.

---

## Actividad 3 (Adapter)

- Defina `CalculadoraLegacy` con `int calcular(int a, int b)`. Cree un adaptador que ofrezca `double calcular(double a, double b)` delegando en la legacy. Muestre su uso en `main`.

---

**Formato de entrega:** Código y documentación en **archivo(s) MD (Markdown)**.
