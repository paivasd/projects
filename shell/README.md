
# Interpretador de Comandos - Flex, Bison e C - UC Processamento de Linguagens

Foram desenvolvidos, na UC Sistemas Operativos e Sistemas Distribuidos (SOSD) vários comandos: mostra, conta, apaga, informa, acrescenta e lista. Pretende-se agora integrar estes comandos numa linguagem de *scripting* que permita fazer várias operações sobre ficheiros. Esta linguagem deverá permitir a execução direta dos comandos.

# Exemplos:
- apresenta no ecrã os dois ficheiros indicados
  ```sh
  mostra /etc/passwd /etc/group
  ```
- acrescenta em todos.txt os outros dois ficheiros  
  ```sh
  acrescenta todos.txt /etc/passwd /etc/group1
  ```
- apaga os ficheiros ficheiro1.txt ficheiro2.txt
  ```sh
  apaga ficheiro1.txt ficheiro2.txt
  ```
- Será possível definir variáveis com nomes de ficheiros:
  ```sh
  $texto = /etc/passwd
  ```
  Estas variáveis poderão posteriormente ser utilizadas em futuros comandos, como por exemplo:
   ```sh
  apaga $texto
  ```
  Ou ainda:
  ```sh
  $fich1 = ficheiro1.txt
  acrescenta $fich1 "ficheiro2"
  ```
 - O comando *print* imprime uma string, substituindo todas as variáveis pelo seu respetivo valor. No exemplo seguinte, a string
   === /etc/hosts seria impressa no ecrã:
   ```sh
   $hosts = /etc/hosts
   print "=== $hosts"
   ```
