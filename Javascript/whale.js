class Whale {
  constructor() {
    this.position = [];
    this.fitness = Infinity;
    this.color = [255, 255, 255];
    this.history = [];
  }

  get_fitness() {
    let sum = 0.0;
    for (let i = 0; i < DIM; i++) {
      sum += (this.position[i] - 400) * (this.position[i] - 400);
    }
    return sum;
  }
}

function initialize_population(population) {
  for (let i = 0; i < POP_SIZE; i++) {
    let w = new Whale();
    for (let d = 0; d < DIM; d++) {
      let pos_d = random(LOWER_BOUND, UPPER_BOUND);
      w.position.push(pos_d);
    }
    w.fitness = w.get_fitness();
    console.log(w.position, w.fitness);
    population.push(w);
    console.log("position:", w.position, "fitness:", w.fitness);
  }
}

function find_best_whale(population) {
  let best_whale = population[0];
  for (let i = 1; i < POP_SIZE; i++) {
    if (population[i].fitness < best_whale.fitness) {
      best_whale = population[i];
    }
  }
  return best_whale;
}

function random_move(population, whale) {
  let random_index = Math.floor(random(0.0, POP_SIZE));
  let random_whale = population[random_index];

  for (let d = 0; d < DIM; d++) {
    let random_coeff = random(-0.1, 0.1);
    let D = Math.abs(random_whale.position[d] - whale.position[d]);
    whale.position[d] = random_whale.position[d] - random_coeff * D;
    if (whale.position[d] < 0) {
      whale.position[d] = 0;
    } else if (whale.position[d] > 800) {
      whale.position[d] = 800;
    }
  }
  whale.fitness = whale.get_fitness();
}

function spiral_move(best_whale, whale) {
  let b = 1.0;
  let l = random(-1.0, 1.0);

  for (let d = 0; d < DIM; d++) {
    let D = Math.abs(best_whale.position[d] - whale.position[d]);
    whale.position[d] =
      D * Math.exp(b * l) * Math.cos(2 * Math.PI * l) + best_whale.position[d];
  }
  whale.fitness = whale.get_fitness();
}

function encircle_prey(whale, best_whale, a) {
  for (let d = 0; d < DIM; d++) {
    let A = random(-a, a);
    let C = random(0, 2.0);
    let D = Math.abs(C * best_whale.position[d] - whale.position[d]);
    whale.position[d] = best_whale.position[d] - A * D;
  }
  whale.fitness = whale.get_fitness();
}

function coloring(whale, best_fitness) {
  let fitness_ratio = best_fitness / whale.fitness;
  let r = Math.floor(255 * fitness_ratio);
  let g = Math.floor(246 * fitness_ratio);
  let b = Math.floor(128 * fitness_ratio);
  whale.color = [r, g, b];
}
