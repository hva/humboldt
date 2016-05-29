## Running

`$ gcc -std=c89 main.c && ./a.out examples/graph1.txt`

## Leaks Checking

`$ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./a.out examples/graph1.txt`

## Algorithm

[Eulerian Path and Circuit](http://www.graph-magics.com/articles/euler.php)
