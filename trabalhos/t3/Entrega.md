[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T3

# Scheduling com OpenMP

Nome: Gabriel Doyle Balk

1. Usando o programa [ThreadDemoABC.cpp](ThreadDemoABC.cpp) como inspiração, você deverá criar um novo programa chamado OpenMPDemoABC.cpp. Seu programa vai implementar vários casos com threads que atualizam o array compartilhado, usando OpenMP, ilustrando o efeito das opções de escalonamento disponíveis para a cláusula schedule:

Schedule `static`, com e sem especificação do chunk
Schedule `dynamic`, com e sem especificação do chunk
Schedule `guided`, com e sem especificação do chunk
Schedule `runtime`
Schedule `auto`
Um ou mais casos sem exclusão mútua, para apresentar saídas incorretas.
Note que, ao contrário do programa com POSIX Threads, você deixará o particionamento também a cargo do OpenMP (no programa original, isso é feito manualmente e cada thread faz exatamente 20 inserções).

Minha implementação do [OpenMPDemoABC](OpenMPDemoABC.cpp)

## exemplo de saída

`./OpenMPDemoABC 3 15 3` (3 threads, 15 escritas por thread, chunk de tamanho 3)
Cada Thread deve adicionar o seu char n vezes, n=15
Resultado correto deve totalizar nThreads x nTimes => 45
Caso 1: schedule static com chunk = 3
AAAAAAAAAAAAAAACCCCCCCCCCCCCCCBBBBBBBBBBBBBBB
A=15 B=15 C=15

O OpenMP divide as iterações em partes de tamanho 3 e distribui as partes aos segmentos em uma ordem circular.

Caso 2: schedule static sem chunk
BCCBCBBBBBBCBBBBAAABBABCCAAAAAACCAAAAACCCCCCC
A=15 B=15 C=15

Quando não especificamos o chunk, o OpenMP divide as iterações em partes que são aproximadamente iguais em tamanho e distribui no máximo um fragmento para cada thread.

Caso 3: schedule dynamic com chunk = 3
CAAACCBBBAAABBAABBBAACCCCCCCCBBBBBBBBBBBBBCAA
A=12 B=21 C=12
O OpenMP divide as iterações em partes de tamanho 3. Cada thread executa um bloco de iterações e, em seguida, solicita outro pedaço até que não haja mais blocos disponíveis.
Não há uma ordem específica em que os fragmentos sejam distribuídos para os encadeamentos

Caso 4: schedule dynamic sem chunk
BBAABAACABCCBCAAAACCBAACAABAAAACBBBBCCCCAAACB
A=20 B=12 C=13
Semelhante ao anterior porém o chunk vai ser 1

Caso 5: schedule guided com chunk = 3
BBBBBBBBBBBBCBBBCAAAACCCCCCCAACABBBBAABCCACBB
A=10 B=22 C=13
Semelhante ao dynamic porém o tamanho de um pedaço é proporcional ao número de iterações não atribuídas dividido pelo número de threads. Portanto, o tamanho dos pedaços diminui.

Caso 6: schedule guided sem chunk
BBBBBBBBCCABBBBBBBCBACCCCCCCBBCCBCAAAAACBCAAA
A=10 B=20 C=15

Mesma coisa que o anterior, porém o chunk padrão é um

Caso 7: schedule runtime
BCBBBBCCCBBBBBAABBBAAABBCCAAAAAAACCCACCAACCCC
A=15 B=15 C=15

Caso 8: schedule auto
BBCBBBBCAAACCABBBBBCCCBBBBCCCCCCACCAAAAAAAAAA
A=15 B=15 C=15
Auto, o agendamento é definido pelo SO, ficou parecido com o static sem chunk

Caso 9: schedule static sem chunk e sem exclusao mútua
BCBC-CCBBCCBCCBBBCBBAAAAAAAAAAAAAAA----------
A=15 B=10 C=9
Mostra que as threads provavelmente acessaram o array no mesmo index e sobrescreveram o mesmo valor.

OBS: Expliquei o funcionamento de cada schedule, mas de maneira geral eu fiquei na dúvida quanto a minha implementação. Eu achava que as escritas estavam sendo atrasadas/afetadas pela função spendSomeTime(), acontece que eu retirei ela pra efetuar os testes e mesmo assim as escritas saíram um pouco "atrasadas".(A ordem de escrita printada não é de acordo com o schedule)
E quando executo a atribuição diretamente no vetor `array[i] = 'A'+ omp_get_thread_num();`
a saída é exatamente a que eu esperaria de acordo com cada schedule.

### Referências

- Jaka's Corner, [OpenMP: For & Scheduling](http://jakascorner.com/blog/2016/06/omp-for-scheduling.html)
- Fernando Silva - FCUP, [Introdução ao OpenMPM](https://www.dcc.fc.up.pt/~fds/aulas/PPD/0708/intro_openmp-1x2.pdf)
