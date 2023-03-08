# C-DFS-Maze-Solver
Maze solver using the a Depth First Search algorithm in C language

The size of the maze is calculated using the empty blocks in the rows and column.
So a maze of size 3 will expect a maze like this:
```
   1 2 3
  XXXXXXX
1 S X   X
  X X XXX
2 X     X
  X X X X
3 X X X F
  XXXXXXX
```

dfs-solver ask for 3 arguments : Maze file path, height of maze, width of maze
The minimum of size is 3 for height and width.

If the maze has several good paths, the algorithm won't find the best but the first good for it.

Also, there is a leak somewhere in the map. Will hunt it later.