<div align="center">
  <table>
      <theader>
          <tr>
              <th><img src="https://github.com/rescobedoulasalle/git_github/blob/main/ulasalle.png?raw=true" alt="EPIS" style="width:50%; height:auto"/></th>
              <th>
                  <span style="font-weight:bold;">UNIVERSIDAD LA SALLE</span><br />
                  <span style="font-weight:bold;">FACULTAD DE INGENIERÍAS</span><br />
                  <span style="font-weight:bold;">DEPARTAMENTO DE INGENIERÍA Y MATEMÁTICAS</span><br />
                  <span style="font-weight:bold;">CARRERA PROFESIONAL DE INGENIERÍA DE SOFTWARE</span>
              </th>            
          </tr>
      </theader>

  </table>
  </div>

  <table>
      <theader>
          <tr><th colspan="2">INFORMACIÓN BÁSICA</th></tr>
      </theader>
  <tbody>
<tr><td>ALUMNO:</td><td>Roger Infa Sanchez</td></tr>
  <tr><td>EXAMEN FINAL:</td><td>Problema Productor Consumidor consola y GUI</td></tr>
  <tr><td colspan="2">RECURSOS:
      <ul>
      <li>Problema productor-consumidor de Wikipedia, link https://es.wikipedia.org/wiki/Problema_productor-consumidor#:~:text=La%20tarea%20del%20productor%20es,simult%C3%A1neamente)%20productos%20uno%20a%20uno.</li>
        <li>Git del docente, link https://github.com/rescobedoulasalle/so</li>
      </ul>
  </td>
  </<tr>
  <tr><td colspan="2">DOCENTE:
      <ul>
          <li>Richart Smith Escobedo Quispe  - r.escobedo@ulasalle.edu.pe</li>
      </ul>
  </td>
  </<tr>
   <tr><td colspan="2">INDICE:
      <ul>
          <ol>
            <li>Introducción</li>
            <li>Explicación Patrón Mediator</li>
            <li>Ejemplos
              <ol>
                 <li>Ejemplo vida cotidiana</li>
                 <li>Ejemplo programación básico</li>
                 <li>Ejemplo programación avanzado</li>
              </ol>
            </li>
            <li>Uso del patrón en librerías, frameworks, programas,etc</li>
            <li>Bibliografías y referencias</li>
          </ol>
      </ul>
  </td>
  </<tr>
  </tdbody>
  </table>
  
# Problema productor_consumidor
## Requisitos
Primero debemos ver si nuestra máquina en la que trabajaremos puede compilar archivos C o C++, esto se hará con los siguientes comandos en la consola

```
gcc --version && g++ --version
```
Lo que deberia darnos este resultado, donde nos indica la version si lo tuviesemos isntalado de forma predeterminada.
```
gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

g++ (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
En el caso de que no nos salga ese mensaje ejecutamos
```
sudo apt-get install gcc && sudo apt-get install g++
```
Para que se instalen los repositorios necesarios para compilar archivos .c y .cpp

Luego de ello, para la solución por consola, uttilizarémos el editor de código Visual Studio Code que además des ser editor de texto, será  donde compilemos nuestro código.

## Solución paso a paso
El inicio basico sería el siguiente
```cpp
#include "iostream"
using namespace std;
int main(){
  // code
  return 0;
}
```
Sin embargo para la solucion de este trabajo necesitaremos más librerías,
```cpp
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
```
```#include <thread>``` para representar subprocesos individuales de ejecución.
  
```#include <mutex>``` para proteger los datos compartidos para que varios subprocesos no accedan simultáneamente a ellos.
  
```#include<deque>``` para permitir una rápida inserción y eliminación tanto al principio como al final.
  
```#include <condition_variable>``` es una primitiva de sincronización que se puede usar para bloquear un subproceso, o varios subprocesos al mismo tiempo, hasta que otro subproceso modifique una variable compartida (la condición ) y notifique al condition_variable.

Luego de ello, procederemos a definir las variables que usaremos  para esta primera implementación por consola.
 ```cpp
#define CANTIDAD_PRODUCTORES 10 /* CANTIDAD productores = CANTIDAD consumidores */
condition_variable condicion;
mutex _mutex;
deque<int> buffer;
const unsigned int tamanioMaxBuffer = 20;
 ```
 Entonces empezamos con la clase Productor, que tiene su constructor ```Productor()``` un metodo privado ```produce()``` y un método publico tipo void ```join_thread()```.
 
 El metodo privado ```produce()``` no tiene parámetros y  en esdte daremos un valor maximo que será el límite que producirám los productores, que poco a poco disminuye hasta llegar a 0. En el ciclo ```while```  creamos un locker de la libreía mutex y le mandamos el ```_mutex``` , actos seguido a la variable de condicion ```condicion``` le mandamos la isntruccion ```wait()```que hace que el subproceso actual se bloquee hasta que se notifique la variable. Luego con ```buffer.push_back(val);``` agregamos la produccion al buffer, posteriormente imprimimos que está haciendo el productor en ese instante, el val disminuye con ```val--;``` que e s como decir ```val = val - 1;```  y luego desbloqueamos elmutex en este caso locker con ```locker.unlock();``` y finalmente notificamos al otro hilo que puede continuar con ```condicion.notify_one();```
En ```Productor(int id)``` se construye el Productor con un id y un thread por referencia.

Finalmente en ```void join_thread()``` finaliza los threads.
 ```cpp
 class Productor{
	private:
		thread t;
		int k;
		void produce(){
			int val=100;
			while (val){
				unique_lock<mutex> locker(_mutex);
				condicion.wait(locker, [](){ return buffer.size() < tamanioMaxBuffer; });
				buffer.push_back(val);
				cout <<"p"<< k << ": El Productor nmro " << k <<" produce: "<< val << endl;
				val--;
				locker.unlock();
				condicion.notify_one();
			}
		}
	public:
		Productor(int id) {
			k = id;
			t = thread(&Productor::produce, this);
		}
		void join_thread(){
			t.join();
		}
};
 ```
 Luego de haber implementado la clase Productor, pasamos a la clase Consumidor que cointiene de manera similar a Productor, dos atributos(thread t, int k) y tres métodos(un privado y dos publicos).
En ```void consume()``` la variable de condicion ```condicion``` le mandamos la instruccion ```wait()```que hace que el subproceso actual se bloquee hasta que se notifique la variable, esto con un ```buffer.size() > 0``` luego ```val``` será el ultimo valor del buffer y con ```buffer.pop_back();``` el consumidor consume el ultimo elemento, es decir el ```val```, luego de ello se imprime lo que hace el consumidor en ese instante luego desbloqueamos elmutex en este caso ```locker``` con ```locker.unlock();``` y finalmente notificamos al otro hilo que puede continuar con ```condicion.notify_one();```

 En ```Consumidor(int id)``` se construye el Productor con un id y un thread por referencia.

Finalmente en ```void join_thread()``` finaliza los threads.
 
  ```cpp 
  class Consumidor {
	private:
		thread t;
		int k;
		void consume() {
			while (true){
				unique_lock<mutex> locker(_mutex);
				condicion.wait(locker, [](){ return buffer.size() > 0; });
				int val = buffer.back();
				buffer.pop_back();
				cout <<"c"<< k << ": L Consumidor nmro "<< k <<" consume:" << val << endl;
				locker.unlock();
				condicion.notify_one();
			}
		}
	public:
		Consumidor(int id) {
			k = id;
			t = thread(&Consumidor::consume, this);
		}
		void join_thread(){
			t.join();
		}
};
 ```
 Y para acabar la implementacion por consola definimos el  ```main() ``` donde se crean lista de consumidores y productores, estas son de tipo o Productor o Consumidor ambas punteros.
 Luego se inicializan los productores y consumidores con el primer ```for```. Luego en el segundo for es donde empezamos a producir y consumir. Y con buenas técnicas de programación el c++, al final del ```main()```  utilizamos el ```return 0;``` .
```cpp
 int main(){
	Productor* productores[CANTIDAD_PRODUCTORES];
	Consumidor* consumidores[CANTIDAD_PRODUCTORES];

	for (int i = 0; i < CANTIDAD_PRODUCTORES; i++)	{		
		productores[i] = new Productor(i);
		consumidores[i] = new Consumidor(i); 
	}

	for (int i=0; i < CANTIDAD_PRODUCTORES; i++)	{
		productores[i]->join_thread();
		consumidores[i]->join_thread();
	}
	cout<<"Fin"<<endl;
	return 0;
}
```
Al momento de ejcutar este .cpp por la consola de linux y compilador de Visual Studio Code me aparecíam los siguientes errores.

Cosola de Visual Studio Code:

Consola de Linux:

 
