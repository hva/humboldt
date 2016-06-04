## Running

`$ gcc -std=c89 main.c && ./a.out examples/graph7.txt`

## Leaks Checking

`$ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./a.out examples/graph7.txt`

## Algorithm

[Eulerian Path and Circuit](http://www.graph-magics.com/articles/euler.php)
