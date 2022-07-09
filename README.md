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

  <tr><td>EXAMEN FINAL:</td><td>Problema Productor Consumidor consola y GUI</td></tr>
  <tr><td colspan="2">RECURSOS:
      <ul>
      <li>Oscar J Blancarte Iturralde. Introducción a los patrones de diseño. Un enfoque práctico (Spanish Edition. CreateSpace Independent Publishing Platform (2016)</li>
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
