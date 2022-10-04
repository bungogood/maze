# Maze

Inspired by a Computerphile [video](https://youtu.be/rop0W4QDOUI).

## Usage

### Generate
```
./maze gen <mazes/out.png> 1000
```

### Solve
```
./maze gen <mazes/in.png>
```

### Color
```
./maze gen <mazes/in.png> <mazes/out.png>
```

### Show
```
./maze show <mazes/in.png>
```

## Install

```
git clone git@github.com:Bungogood/maze.git
cd maze
mkdir mazes .obj
make
```

## Techniques

Solvers:

- Dijkstra
- A Star
- Breadth First Search
- Depth First Search
- Always Turn Left / Right (hand on wall)

Generators:

- Prim
- Kruskal
- Binary Tree

Data Structures:

- Stacks
- Queues
- Heaps
- Priority Queues
- Dynamic Arrays
- Linked Lists
- Hashtables

## Structure

```
├── .obj/
│   └── <objects.o>
├── include/
│   └── <headers.h>
├── mazes/
│   └── <mazes.png>
├── src/
│   ├── datastructs/
│   │   ├── stack.c
│   │   ├── queue.c
│   │   ├── heap.c
│   │   ├── pqueue.c
│   │   ├── earray.c
│   │   ├── llist.c
│   │   └── hashtable.c
│   ├── solvers/
│   │   ├── prim.c
│   │   ├── kruskal.c
│   │   └── btree.c
│   ├── generators/
│   │   ├── dijkstra.c
│   │   ├── astar.c
│   │   ├── bfs.c
│   │   ├── dfs.c
│   │   └── aturn.c
│   ├── parse.c
│   ├── generate.c
│   ├── solve.c
│   ├── color.c
│   ├── maze.c
│   └── main.c
├── .gitignore
├── makefile
├── maze
└── README.md
```

## To Do

- add path checker for filenames
- add integer checker for seed and width / height

## References

https://youtu.be/rop0W4QDOUI
https://github.com/mikepound/mazesolving
