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

### Referências

- Jaka's Corner, [OpenMP: For & Scheduling](http://jakascorner.com/blog/2016/06/omp-for-scheduling.html)
- Fernando Silva - FCUP, [Introdução ao OpenMPM](https://www.dcc.fc.up.pt/~fds/aulas/PPD/0708/intro_openmp-1x2.pdf)
