tabela referente ao programa [fractalpar2](fractalpar2.cpp)

| Entrada | Schedule | Threads | Chunk | Tempo     | Speedup | Eficiência |
| ------- | -------- | ------- | ----- | --------- | ------- | ---------- |
| 1024 32 |          |         |       |           |         |            |
|         | Serial   | 1       | -     | 38.8286 s | -       | -          |
|         | static   | 2       | 1     | 20.0574 s | 1.93    | 96.5%      |
|         | static   | 2       | 4     | 20.1025 s | 1.93    | 96.5%      |
|         | static   | 4       | 1     | 14.0115 s | 2.77    | 69%        |
|         | static   | 4       | 4     | 14.5120 s | 2.67    | 66.7%      |
|         | static   | 8       | 1     | 16.4181 s | 2.36    | 29.5%      |
|         | static   | 8       | 4     | 16.4781 s | 2.35    | 29%        |
|         | dynamic  | 2       | 1     | 20.8821 s | 1.85    | 92.5%      |
|         | dynamic  | 2       | 4     | 20.2794 s | 1.91    | 95.5%      |
|         | dynamic  | 4       | 1     | 13.5719 s | 2.86    | 71.5%      |
|         | dynamic  | 4       | 4     | 13.7936 s | 2.81    | 70.3%      |
|         | dynamic  | 8       | 1     | 14.5595 s | 2.66    | 33.3%      |
|         | dynamic  | 8       | 4     | 14.0891 s | 2.75    | 34.4%      |
|         | guided   | 2       | 1     | 22.0801 s | 1.75    | 87.5%      |
|         | guided   | 2       | 4     | 22.0944 s | 1.75    | 87.5%      |
|         | guided   | 4       | 1     | 13.8331 s | 2.80    | 70%        |
|         | guided   | 4       | 4     | 14.5059 s | 2.67    | 66%        |
|         | guided   | 8       | 1     | 14.0851 s | 2.75    | 34.3%      |
|         | guided   | 8       | 4     | 13.9834 s | 2.77    | 34.6%      |
| 1024 64 |          |         |       |           |         |            |
|         | Serial   | 1       | -     | 74.4327 s | -       | -          |
|         | static   | 2       | 1     | 38.5618 s | 1.93    | 96.5%      |
|         | static   | 2       | 4     | 38.6355 s | 1.92    | 96%        |
|         | static   | 4       | 1     | 27.3451 s | 2.72    | 68%        |
|         | static   | 4       | 4     | 28.3196 s | 2.62    | 65.5%      |
|         | static   | 8       | 1     | 32.0058 s | 2.32    | 29%        |
|         | static   | 8       | 4     | 31.7219 s | 2.34    | 29.2%      |
|         | dynamic  | 2       | 1     | 40.0541 s | 1.85    | 92.5%      |
|         | dynamic  | 2       | 4     | 38.8343 s | 1.91    | 96%        |
|         | dynamic  | 4       | 1     | 26.8245 s | 2.77    | 69.2%      |
|         | dynamic  | 4       | 4     | 25.2812 s | 2.94    | 73.5%      |
|         | dynamic  | 8       | 1     | 28.4982 s | 2.61    | 32.6%      |
|         | dynamic  | 8       | 4     | 25.4934 s | 2.75    | 34.3%      |
|         | guided   | 2       | 1     | 44.9454 s | 1.65    | 82.5%      |
|         | guided   | 2       | 4     | 44.9461 s | 1.65    | 82.5%      |
|         | guided   | 4       | 1     | 27.8531 s | 2.67    | 66.7%      |
|         | guided   | 4       | 4     | 29.1013s  | 2.55    | 63.7%      |
|         | guided   | 8       | 1     | 27.0954 s | 2.74    | 34.2%      |
|         | guided   | 8       | 4     | 26.5010 s | 2.80    | 35%        |