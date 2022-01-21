# Carlos III Grado de Ingenieria Informática
## Sistemas operativos
Practica 3. Programación multi-hilo (Procesos y threads)

### Objetivo de la práctica
Esta práctica permite al alumnado familiarizarse con los servicios para la gestión de procesos que proporciona POSIX. <br />
Para la gestión de procesos ligeros (hilos), se utilizarán las llamadas al sistema pthread_create, pthread_join, pthread_exit y para la sincronización de estos, mutex y variables condicionales. <br/>
El alumno deberá diseñar y codificar, en el lenguaje C y sobre el sistema operativo UNIX/Linux, un programa que actúe como gestor de procesos de fabricación incluyendo varios procesos encargados de gestionar distintas fases de la fábrica y un proceso que realiza la planificación de las fases.

### Funcionamiento del programa
1. Descargar el repo <br/>
```git clone https://github.com/tiantianana/SSOO_p3.git```
2. cd al directorio raiz. <br/>
```
cd SSOO_p3
 make
```
3. Ejecutar el programa con el comando 
```
./calculator <filename> <num.Producers> <buff.Size>
```

### Más información en ssoo_p3_multithread_19-20.pdf
