# Curso Programación en Sistemas Embebidos

**Materia** Programación de Microcontroladores

**Autor:** Luis Alberto Gómez Parada

**Placa:** STM32F429ZI


## Objetivo General:

desarrollo de prácticas del curso de programación   en sistemas embebidos de la especialidad en sistemas embebidos. Este archivo ayuda a entender la estructura de archivos que contiene los ejercicios realizados durante la especialización. Las prácticas se organizan en los siguientes archivos:


**1.2) Practica01_p1:** Familiarizarse con el entorno de trabajo STM32CubeIDE + NUCLEO-F429ZI + firmware. Implementar un programa que genere una secuencia periódica con los leds de la placa NUCLEO-F429ZI. La secuencia debe seguir el orden: LED1, LED2, LED3, LED1,... etc.
Cada led debe permanecer encendido 200 ms. y 200 ms apagado.  No debe encenderse más de un led simultáneamente. 

**1.2) Practica01_p2:** Punto 2: Utilizar el pulsador azul (USER_BUTTON) para controlar cómo se recorre la secuencia de leds.  Cada vez que se presiona el pulsador se debe alternar el orden de la secuencia entre:

- LED1, LED2, LED3, LED1,... etc.
- LED1, LED3, LED2, LED1,... etc.


**2.1) Practica02_p1:** Implementar un módulo de software para trabajar con retardos no bloqueantes. 
Implementar las funciones auxiliares necesarias para usar retardos no bloqueantes en un archivo fuente main.c con su correspondiente archivo de cabecera main.h.

Implementar un programa que utilice retardos no bloqueantes y  haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F429ZI de la siguiente manera:

- LED1: 100 ms. 
- LED2: 500 ms.
- LED3: 1000 ms.


**3.1) Practica03_p1:** Corresponde a la práctica 3 en la parte 1 donde se copió el código desarrollado en la Práctica 2 y se generó una API para la misma implementación en la carpeta. Las carpetas generadas fueron `API/scr` (.c) y `API/inc` (.h)


**3.2) Practica03_p2:** Genera una primera solución al problema planteado de, pero si bien cumple con lo solicitado a veces se demora un poco mas en la pausa. Particularmente cuando los tiempos detenidos se incrementan.


**3.3) Practica03_p3:** Este cumple con lo solicitado para la parte 2 de la práctica 3 

**4.1) Practica04_p1:** Implementar un **MEF** para trabajar con **anti-rebotes** por software.

**4.2) Practica04_p2:** Implementar un programa que cambie la frecuencia de toggleo del LED2 entre 100 ms y 500 ms cada vez que se presione la tecla.  El programa debe usar las funciones anti-rebote del módulo `API_debounce` y los retardos no bloqueantes del módulo `API_delay`. 


**5.1) Practica05_p1:** Implementar un módulo de software sencillo para trabajar con la **UART**. 

**5.1) Practica05_p2:** Sobre el ejercicio de la práctica 4, implementar un programa que utilice el **módulo de uart** para informar al usuario cuando se producen los flancos ascendente y descendente. 


