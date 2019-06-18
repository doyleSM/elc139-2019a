[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T8

# Geração de Imagem em Paralelo com CUDA

Nome: Gabriel Doyle Balk
</br>
[Configuração](config.txt) da maquina utilizada </br>
</br>

# Parte 1

[Implementação original](wave.cpp) do programa em c++
</br>
[Minha implementação](wavecuda1.cu) do programa em cuda1
</br>

Abaixo a tabela com os resultados obtidos:

| Entrada         | tempo .cpp | tempo .cu | speedup |
| --------------- | ---------- | --------- | ------- |
| ./wave 1024 100 | 5.2698 s   | 0.6173 s  | 8.53    |
| ./wave 1024 200 | 10.8669 s  | 0.6604 s  | 16.45   |
| ./wave 2048 100 | 21.4478 s  | 2.0035 s  | 10.70   |
| ./wave 2048 200 | 42.7675 s  | 2.1372 s  | 20.01   |

# Parte 2

[Implementação original](wave.cpp) do programa em c++
</br>
[Minha implementação](wavecuda2.cu) do programa em cuda2
</br>
Abaixo a tabela com os resultados obtidos:

| Entrada         | tempo .cpp | tempo .cu | speedup |
| --------------- | ---------- | --------- | ------- |
| ./wave 1024 100 | 5.2698 s   | 0.2228 s  | 22.55   |
| ./wave 1024 200 | 10.8669 s  | 0.3788 s  | 29.59   |
| ./wave 2048 100 | 21.4478 s  | 0.3543 s  | 58.37   |
| ./wave 2048 200 | 42.7675 s  | 0.5916 s  | 68.15   |

## Referências

- [CUDA C Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)  
  Guia da NVIDIA sobre programação em CUDA.

- [An Even Easier Introduction to CUDA](https://devblogs.nvidia.com/even-easier-introduction-cuda/)  
  introduction to CUDA by nvidia blog.
