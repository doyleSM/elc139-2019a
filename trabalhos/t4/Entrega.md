[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T3

# Geração de Fractais de Mandelbrot em OpenMP

Nome: Gabriel Doyle Balk

### Implementação 1

A paralelização foi feita no `for` das rows

```
  [...]
  #pragma omp parallel for shared(pic, frame, width) schedule(guided, 4)
  for (int row = 0; row < width; row++) {
    const double cy = yMin + row * dw;
    for (int col = 0; col < width; col++) {
      const double cx = xMin + col * dw;
  [...]
```

testes:

| Entrada | Schedule | Threads | Chunk | Tempo     | Speedup | Eficiência |
| ------- | -------- | ------- | ----- | --------- | ------- | ---------- |
| 512 32  |          |         |       |           |         |            |
|         | Serial   | 1       | -     | 9.6992 s  | -       | -          |
|         | static   | 2       | 1     | 5.0399 s  | 1.92    | 96%        |
|         | static   | 2       | 4     | 5.0689 s  | 1.91    | 95.5%      |
|         | static   | 4       | 1     | 3.6067 s  | 2.68    | 67%        |
|         | static   | 4       | 4     | 3.4849 s  | 2.78    | 69%        |
|         | static   | 8       | 1     | 3.5592 s  | 2.72    | 34%        |
|         | static   | 8       | 4     | 3.4840 s  | 2.78    | 34%        |
|         | dynamic  | 2       | 1     | 5.0224 s  | 1.93    | 96.5%      |
|         | dynamic  | 2       | 4     | 5.0022 s  | 1.93    | 96.5%      |
|         | dynamic  | 4       | 1     | 3.0740 s  | 3.15    | 78.7%      |
|         | dynamic  | 4       | 4     | 3.4525 s  | 2.80    | 70%        |
|         | dynamic  | 8       | 1     | 3.1042 s  | 3.12    | 39%        |
|         | dynamic  | 8       | 4     | 3.1713 s  | 3.05    | 38%        |
|         | guided   | 2       | 1     | 5.1049 s  | 1.89    | 94.5%      |
|         | guided   | 2       | 4     | 5.1040 s  | 1.90    | 95%        |
|         | guided   | 4       | 1     | 3.5228 s  | 2.75    | 68.7%      |
|         | guided   | 4       | 4     | 3.3287 s  | 2.91    | 72.7%      |
|         | guided   | 8       | 1     | 3.1734 s  | 3.05    | 38%        |
|         | guided   | 8       | 4     | 3.5474 s  | 2.73    | 34%        |
| 512 64  |          |         |       |           |         |            |
|         | Serial   | 1       | -     | 18.6922 s | -       | -          |
|         | static   | 2       | 1     | 9.5632 s  | 1.95    | 97.5%      |
|         | static   | 2       | 4     | 9.5658 s  | 1.95    | 97.5%      |
|         | static   | 4       | 1     | 6.6445 s  | 2.81    | 70%        |
|         | static   | 4       | 4     | 6.9141 s  | 2.70    | 67.5%      |
|         | static   | 8       | 1     | 7.0768 s  | 2.64    | 33%        |
|         | static   | 8       | 4     | 7.0485 s  | 2.65    | 33%        |
|         | dynamic  | 2       | 1     | 9.5650 s  | 1.95    | 97.5%      |
|         | dynamic  | 2       | 4     | 9.5711 s  | 1.95    | 97.5%      |
|         | dynamic  | 4       | 1     | 6.4418 s  | 2.90    | 72.5%      |
|         | dynamic  | 4       | 4     | 6.4480 s  | 2.89    | 72%        |
|         | dynamic  | 8       | 1     | 6.2299 s  | 3.00    | 37.5%      |
|         | dynamic  | 8       | 4     | 6.3888 s  | 2.92    | 36.5%      |
|         | guided   | 2       | 1     | 9.7953 s  | 1.90    | 95%        |
|         | guided   | 2       | 4     | 9.8084 s  | 1.90    | 95%        |
|         | guided   | 4       | 1     | 6.1861 s  | 3.02    | 75.5%      |
|         | guided   | 4       | 4     | 6.1746 s  | 3.02    | 75.5%      |
|         | guided   | 8       | 1     | 6.3755 s  | 2.93    | 36.6%      |
|         | guided   | 8       | 4     | 6.4783 s  | 2.88    | 36%        |
| 1024 32 |          |         |       |           |         |            |
|         | Serial   | 1       | -     | 38.8286 s | -       | -          |
|         | static   | 2       | 1     | 20.0668 s | 1.93    | 96.5%      |
|         | static   | 2       | 4     | 19.9790 s | 1.94    | 97%        |
|         | static   | 4       | 1     | 14.1861 s | 2.73    | 68%        |
|         | static   | 4       | 4     | 14.1200 s | 2.75    | 68.7%      |
|         | static   | 8       | 1     | 14.2806 s | 2.71    | 33.8%      |
|         | static   | 8       | 4     | 14.4311 s | 2.69    | 33.6%      |
|         | dynamic  | 2       | 1     | 19.9709 s | 1.94    | 97%        |
|         | dynamic  | 2       | 4     | 19.9893 s | 1.94    | 97%        |
|         | dynamic  | 4       | 1     | 13.3130 s | 2.91    | 72.7%      |
|         | dynamic  | 4       | 4     | 13.3504 s | 2.90    | 72.5%      |
|         | dynamic  | 8       | 1     | 13.4622 s | 2.88    | 36%        |
|         | dynamic  | 8       | 4     | 13.5444 s | 2.86    | 35.7%      |
|         | guided   | 2       | 1     | 20.4093 s | 1.90    | 95%        |
|         | guided   | 2       | 4     | 20.4029 s | 1.90    | 95%        |
|         | guided   | 4       | 1     | 13.2940 s | 2.92    | 73%        |
|         | guided   | 4       | 4     | 13.5672 s | 2.86    | 71.5%      |
|         | guided   | 8       | 1     | 13.5020 s | 2.87    | 35.8%      |
|         | guided   | 8       | 4     | 13.5793 s | 2.85    | 35.6%      |
