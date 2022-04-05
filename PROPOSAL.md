# Cellular automata based forest fire simulation project proposal

The final project is supposed to implement a forest fire simulator based on 2D cellular automata.

The motivation is based on the value of forest fire simulations and my understanding of cellular automata. Recently, more forest fires cause human and property damage and accurate fire simulation model can effectively help avoid losses. Cellular automata provide a scheme for simulating forest fire. It assumes that an 2D area consists of a lattice, and the state change of a cell in the lattice is determined by itself and its neighbors as described by the formula

$$
f_{t+1}(i,j) = \mathrm{T} (f_{t}(i,j), \{ f_t(k,w) | (k,w)\in \mathcal{N}_{i,j} \}).
$$

In the first week, I will implement a primitive two-dimensional square lattice cellular automata, which contains only two states. It also supports an interactive interface that can define initial state, operation pause and other functions. 

After the first week, the forest model and fire spread model will be designed and implemented based on the work in the first week. The state of lattice cells will expand to forest land, grassland, lake, river, burning, burnout and so on. The model of fire spread will be realized by designing state transition function. In the fire spread model, different types of areas have different properties, such as nonflammability, rapid burnup, slow combustion and so on.

If project is finished early, I will implement other functions for this project, such as the influence of wind on fire spread, and replacing square grid with regular hexagonal grid.
