Autor: Luis Alberto Gómez Parada
Placa: STM32F429ZI


Objetivo: desarrollo de prácticas del curso de programación   en sistemas embebidos de la especialidad en sistemas embebidos. Este archivo ayuda a entender la estructura de archivos que contiene los ejercicios realizados durante la especialización. Las prácticas se organizan en los siguientes archivos:


1.2) Practica01_p1: Familiarizarse con el entorno de trabajo STM32CubeIDE + NUCLEO-F429ZI + firmware. Implementar un programa que genere una secuencia periódica con los leds de la placa NUCLEO-F429ZI. La secuencia debe seguir el orden: LED1, LED2, LED3, LED1,... etc.
Cada led debe permanecer encendido 200 ms. y 200 ms apagado.  No debe encenderse más de un led simultáneamente. 

1.2) Practica01_p2: Punto 2: Utilizar el pulsador azul (USER_BUTTON) para controlar cómo se recorre la secuencia de leds.  Cada vez que se presiona el pulsador se debe alternar el orden de la secuencia entre:
LED1, LED2, LED3, LED1,... etc.
LED1, LED3, LED2, LED1,... etc.
