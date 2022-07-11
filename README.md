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
	<li>Productor-Consumidor C++ En Youtube, https://www.youtube.com/watch?v=sEZYHV0hPgg</li>
	<li>Cómo: Implementar varios modelos productor-consumidor de Microsoft, https://docs.microsoft.com/es-es/cpp/parallel/concrt/how-to-implement-various-producer-consumer-patterns?view=msvc-170</li>
	<li>Trabajo de Sistemas Operativos de Elena Cano Urdiales y Raquel Santos Rubio, https://www.infor.uva.es/~cllamas/concurr/pract97/rsantos/</li>    
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
            <li>Requisitos</li>
            <li>Solución paso a paso</li>
            <li>Solución paso a paso GUI</li>
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

## Solución paso a paso consola
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
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/e1.PNG" alt="JuveYell">
</p>
</div>
En el caso de mi linux, adjunto el sistema operativo en el que estoy trabajando
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/so.PNG" alt="JuveYell" >
</p>
</div>
Consola de Linux:
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/e2.PNG" alt="JuveYell" >
</p>
</div>
 Sin embargo, medinate el compilador online OnlineGDB en su Beta para c++, adjunto el link https://www.onlinegdb.com/online_c++_compiler#editor_1 no se me presentó los errores mencionados anteriormente, obteniendo como salida
 
```
p0: El Productor nmro 0 produce: 26
c1: L Consumidor nmro 1 consume:26
p2: El Productor nmro 2 produce: 26
p2: El Productor nmro 2 produce: 25
p2: El Productor nmro 2 produce: 24
p2: El Productor nmro 2 produce: 23
p2: El Productor nmro 2 produce: 22
p2: El Productor nmro 2 produce: 21
p2: El Productor nmro 2 produce: 20
p2: El Productor nmro 2 produce: 19
p2: El Productor nmro 2 produce: 18
c1: L Consumidor nmro 1 consume:18
p2: El Productor nmro 2 produce: 17
p2: El Productor nmro 2 produce: 16
c1: L Consumidor nmro 1 consume:16
c0: L Consumidor nmro 0 consume:17
p0: El Productor nmro 0 produce: 25
p0: El Productor nmro 0 produce: 24
c4: L Consumidor nmro 4 consume:24
c4: L Consumidor nmro 4 consume:25
p3: El Productor nmro 3 produce: 26
p3: El Productor nmro 3 produce: 25
c0: L Consumidor nmro 0 consume:25
c1: L Consumidor nmro 1 consume:26
c1: L Consumidor nmro 1 consume:19
c1: L Consumidor nmro 1 consume:20
c0: L Consumidor nmro 0 consume:21
c0: L Consumidor nmro 0 consume:22
c3: L Consumidor nmro 3 consume:23
p1: El Productor nmro 1 produce: 26
p3: El Productor nmro 3 produce: 24
p1: El Productor nmro 1 produce: 25
c2: L Consumidor nmro 2 consume:25
c2: L Consumidor nmro 2 consume:24
c2: L Consumidor nmro 2 consume:26
c2: L Consumidor nmro 2 consume:24
c2: L Consumidor nmro 2 consume:25
c2: L Consumidor nmro 2 consume:26
p4: El Productor nmro 4 produce: 26
p4: El Productor nmro 4 produce: 25
p4: El Productor nmro 4 produce: 24
p4: El Productor nmro 4 produce: 23
c3: L Consumidor nmro 3 consume:23
c3: L Consumidor nmro 3 consume:24
c3: L Consumidor nmro 3 consume:25
c3: L Consumidor nmro 3 consume:26
p2: El Productor nmro 2 produce: 15
p2: El Productor nmro 2 produce: 14
p0: El Productor nmro 0 produce: 23
p2: El Productor nmro 2 produce: 13
p2: El Productor nmro 2 produce: 12
p2: El Productor nmro 2 produce: 11
p2: El Productor nmro 2 produce: 10
p2: El Productor nmro 2 produce: 9
p3: El Productor nmro 3 produce: 23
p3: El Productor nmro 3 produce: 22
c2: L Consumidor nmro 2 consume:22
c1: L Consumidor nmro 1 consume:23
p2: El Productor nmro 2 produce: 8
c3: L Consumidor nmro 3 consume:8
c3: L Consumidor nmro 3 consume:9
c3: L Consumidor nmro 3 consume:10
c3: L Consumidor nmro 3 consume:11
c3: L Consumidor nmro 3 consume:12
c3: L Consumidor nmro 3 consume:13
c3: L Consumidor nmro 3 consume:23
c3: L Consumidor nmro 3 consume:14
c3: L Consumidor nmro 3 consume:15
p1: El Productor nmro 1 produce: 24
p2: El Productor nmro 2 produce: 7
c3: L Consumidor nmro 3 consume:7
c3: L Consumidor nmro 3 consume:24
p0: El Productor nmro 0 produce: 22
c2: L Consumidor nmro 2 consume:22
p3: El Productor nmro 3 produce: 21
p3: El Productor nmro 3 produce: 20
p3: El Productor nmro 3 produce: 19
p3: El Productor nmro 3 produce: 18
p3: El Productor nmro 3 produce: 17
p3: El Productor nmro 3 produce: 16
p3: El Productor nmro 3 produce: 15
p3: El Productor nmro 3 produce: 14
p3: El Productor nmro 3 produce: 13
p3: El Productor nmro 3 produce: 12
c1: L Consumidor nmro 1 consume:12
c0: L Consumidor nmro 0 consume:13
p0: El Productor nmro 0 produce: 21
c3: L Consumidor nmro 3 consume:21
c3: L Consumidor nmro 3 consume:14
p2: El Productor nmro 2 produce: 6
p2: El Productor nmro 2 produce: 5
p2: El Productor nmro 2 produce: 4
c0: L Consumidor nmro 0 consume:4
p1: El Productor nmro 1 produce: 23
c2: L Consumidor nmro 2 consume:23
c3: L Consumidor nmro 3 consume:5
c1: L Consumidor nmro 1 consume:6
p0: El Productor nmro 0 produce: 20
p2: El Productor nmro 2 produce: 3
p2: El Productor nmro 2 produce: 2
c4: L Consumidor nmro 4 consume:2
c2: L Consumidor nmro 2 consume:3
c2: L Consumidor nmro 2 consume:20
c2: L Consumidor nmro 2 consume:15
c2: L Consumidor nmro 2 consume:16
c2: L Consumidor nmro 2 consume:17
c2: L Consumidor nmro 2 consume:18
c2: L Consumidor nmro 2 consume:19
c2: L Consumidor nmro 2 consume:20
c2: L Consumidor nmro 2 consume:21
p2: El Productor nmro 2 produce: 1
c4: L Consumidor nmro 4 consume:1
p1: El Productor nmro 1 produce: 22
c3: L Consumidor nmro 3 consume:22
p3: El Productor nmro 3 produce: 11
c0: L Consumidor nmro 0 consume:11
p1: El Productor nmro 1 produce: 21
p1: El Productor nmro 1 produce: 20
p1: El Productor nmro 1 produce: 19
p1: El Productor nmro 1 produce: 18
p1: El Productor nmro 1 produce: 17
p1: El Productor nmro 1 produce: 16
p1: El Productor nmro 1 produce: 15
p1: El Productor nmro 1 produce: 14
p1: El Productor nmro 1 produce: 13
p1: El Productor nmro 1 produce: 12
c2: L Consumidor nmro 2 consume:12
p0: El Productor nmro 0 produce: 19
c4: L Consumidor nmro 4 consume:19
c4: L Consumidor nmro 4 consume:13
c4: L Consumidor nmro 4 consume:14
c4: L Consumidor nmro 4 consume:15
c4: L Consumidor nmro 4 consume:16
c4: L Consumidor nmro 4 consume:17
c4: L Consumidor nmro 4 consume:18
c4: L Consumidor nmro 4 consume:19
c4: L Consumidor nmro 4 consume:20
c4: L Consumidor nmro 4 consume:21
p3: El Productor nmro 3 produce: 10
p3: El Productor nmro 3 produce: 9
p3: El Productor nmro 3 produce: 8
p3: El Productor nmro 3 produce: 7
p3: El Productor nmro 3 produce: 6
p3: El Productor nmro 3 produce: 5
p3: El Productor nmro 3 produce: 4
p3: El Productor nmro 3 produce: 3
p3: El Productor nmro 3 produce: 2
p3: El Productor nmro 3 produce: 1
c0: L Consumidor nmro 0 consume:1
p4: El Productor nmro 4 produce: 22
c3: L Consumidor nmro 3 consume:22
c4: L Consumidor nmro 4 consume:2
c3: L Consumidor nmro 3 consume:3
c4: L Consumidor nmro 4 consume:4
p4: El Productor nmro 4 produce: 21
p4: El Productor nmro 4 produce: 20
p4: El Productor nmro 4 produce: 19
c3: L Consumidor nmro 3 consume:19
c3: L Consumidor nmro 3 consume:20
c3: L Consumidor nmro 3 consume:21
c3: L Consumidor nmro 3 consume:5
c3: L Consumidor nmro 3 consume:6
c3: L Consumidor nmro 3 consume:7
c3: L Consumidor nmro 3 consume:8
c3: L Consumidor nmro 3 consume:9
c3: L Consumidor nmro 3 consume:10
p1: El Productor nmro 1 produce: 11
c1: L Consumidor nmro 1 consume:11
p0: El Productor nmro 0 produce: 18
p1: El Productor nmro 1 produce: 10
p1: El Productor nmro 1 produce: 9
p1: El Productor nmro 1 produce: 8
c4: L Consumidor nmro 4 consume:8
c0: L Consumidor nmro 0 consume:9
c0: L Consumidor nmro 0 consume:10
c0: L Consumidor nmro 0 consume:18
p1: El Productor nmro 1 produce: 7
c3: L Consumidor nmro 3 consume:7
p0: El Productor nmro 0 produce: 17
p4: El Productor nmro 4 produce: 18
c2: L Consumidor nmro 2 consume:18
c2: L Consumidor nmro 2 consume:17
p1: El Productor nmro 1 produce: 6
c1: L Consumidor nmro 1 consume:6
p0: El Productor nmro 0 produce: 16
p4: El Productor nmro 4 produce: 17
p1: El Productor nmro 1 produce: 5
c2: L Consumidor nmro 2 consume:5
c2: L Consumidor nmro 2 consume:17
c2: L Consumidor nmro 2 consume:16
p4: El Productor nmro 4 produce: 16
p1: El Productor nmro 1 produce: 4
p1: El Productor nmro 1 produce: 3
c4: L Consumidor nmro 4 consume:3
c4: L Consumidor nmro 4 consume:4
c4: L Consumidor nmro 4 consume:16
p1: El Productor nmro 1 produce: 2
c0: L Consumidor nmro 0 consume:2
p0: El Productor nmro 0 produce: 15
p4: El Productor nmro 4 produce: 15
p1: El Productor nmro 1 produce: 1
c4: L Consumidor nmro 4 consume:1
c4: L Consumidor nmro 4 consume:15
c4: L Consumidor nmro 4 consume:15
p0: El Productor nmro 0 produce: 14
p4: El Productor nmro 4 produce: 14
c2: L Consumidor nmro 2 consume:14
c0: L Consumidor nmro 0 consume:14
p0: El Productor nmro 0 produce: 13
c1: L Consumidor nmro 1 consume:13
p0: El Productor nmro 0 produce: 12
c4: L Consumidor nmro 4 consume:12
p4: El Productor nmro 4 produce: 13
p0: El Productor nmro 0 produce: 11
p0: El Productor nmro 0 produce: 10
p0: El Productor nmro 0 produce: 9
p0: El Productor nmro 0 produce: 8
p0: El Productor nmro 0 produce: 7
p0: El Productor nmro 0 produce: 6
p0: El Productor nmro 0 produce: 5
p0: El Productor nmro 0 produce: 4
p0: El Productor nmro 0 produce: 3
c1: L Consumidor nmro 1 consume:3
c0: L Consumidor nmro 0 consume:4
c0: L Consumidor nmro 0 consume:5
c0: L Consumidor nmro 0 consume:6
c0: L Consumidor nmro 0 consume:7
c0: L Consumidor nmro 0 consume:8
c0: L Consumidor nmro 0 consume:9
c0: L Consumidor nmro 0 consume:10
c0: L Consumidor nmro 0 consume:11
c0: L Consumidor nmro 0 consume:13
p0: El Productor nmro 0 produce: 2
p4: El Productor nmro 4 produce: 12
c0: L Consumidor nmro 0 consume:12
c2: L Consumidor nmro 2 consume:2
p4: El Productor nmro 4 produce: 11
c4: L Consumidor nmro 4 consume:11
p0: El Productor nmro 0 produce: 1
p4: El Productor nmro 4 produce: 10
c0: L Consumidor nmro 0 consume:10
c4: L Consumidor nmro 4 consume:1
p4: El Productor nmro 4 produce: 9
c3: L Consumidor nmro 3 consume:9
p4: El Productor nmro 4 produce: 8
c3: L Consumidor nmro 3 consume:8
p4: El Productor nmro 4 produce: 7
c4: L Consumidor nmro 4 consume:7
p4: El Productor nmro 4 produce: 6
c4: L Consumidor nmro 4 consume:6
p4: El Productor nmro 4 produce: 5
c4: L Consumidor nmro 4 consume:5
p4: El Productor nmro 4 produce: 4
c3: L Consumidor nmro 3 consume:4
p4: El Productor nmro 4 produce: 3
c3: L Consumidor nmro 3 consume:3
p4: El Productor nmro 4 produce: 2
p4: El Productor nmro 4 produce: 1
c2: L Consumidor nmro 2 consume:1
c0: L Consumidor nmro 0 consume:2
```
## Solución paso a paso GUI
Para conectar el código fuente y la interfaz gráfica utilizaremos QT que es un framework poderoso para crear aplicaiones android en base a c++, entonces ejecutamos primero esto: 
```
sudo apt-get install build-essential libgl1-mesa-dev
```
Luego de ello, descargamos el archivo ```qt-unified-linux-x64-4.4.1-online.run``` de la misma pagina https://www.qt.io/download-qt-installer
Después ```chmod +x qt-unified-linux-x64-4.4.1-online.run``` y luego ```./qt-opensource-linux-x64-5.7.0.run``` para ejecutar el instalador.
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/qt1.PNG" alt="JuveYell">
</p>
</div>

Nos registramos
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/qt2.PNG" alt="JuveYell">
</p>
</div>

Y seguimos con la verificaion del correo
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/qt3.PNG" alt="JuveYell">
</p>
</div>

 Y esperamos a que se descargue e instale
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/qt4.PNG" alt="JuveYell">
</p>
</div>

Entonces después de instalar el QT5, creamos un proyeto de ```QT WINDOWS APPLICATION``` y le damos en next a todo.
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/qt5.PNG" alt="JuveYell">
</p>
</div>
Y en FORMS si le damos doble click al archivo que tiene nos manda a un generador de interfaces gráficas.
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/qt6.PNG" alt="JuveYell">
</p>
</div>
Entonces jugando con el programa generamos una ventana agradable y entendible para el usuario.
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/qt7.PNG" alt="JuveYell">
</p>
</div>
Al darle funcionalidad de click al boton, se abre un codigo entendible donde empezamos a programar.
<div style = 'align:center;'>
<p>
<img src="https://github.com/rinfasulasalle/productor_consumidor/blob/main/img/qt8.PNG" alt="JuveYell">
</p>
</div>

## Bibliografías y referencias
 <tr><td colspan="2">RECURSOS:
      <ul>
      <li>Problema productor-consumidor de Wikipedia, link https://es.wikipedia.org/wiki/Problema_productor-consumidor#:~:text=La%20tarea%20del%20productor%20es,simult%C3%A1neamente)%20productos%20uno%20a%20uno.</li>
        <li>Git del docente, link https://github.com/rescobedoulasalle/so</li>
	<li>Productor-Consumidor C++ En Youtube, https://www.youtube.com/watch?v=sEZYHV0hPgg</li>
	<li>Cómo: Implementar varios modelos productor-consumidor de Microsoft, https://docs.microsoft.com/es-es/cpp/parallel/concrt/how-to-implement-various-producer-consumer-patterns?view=msvc-170</li>
	<li>Trabajo de Sistemas Operativos de Elena Cano Urdiales y Raquel Santos Rubio, https://www.infor.uva.es/~cllamas/concurr/pract97/rsantos/</li>    
      </ul>
  </td>
  </<tr>
