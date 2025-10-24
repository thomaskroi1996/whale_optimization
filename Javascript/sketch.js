let population = [];

function setup() {
  createCanvas(800, 800);
  initialize_population(population);
  //   console.log(population);
}

function mousePressed() {
  drawWhales(mouseX, mouseY);
}

let frame_count = 0;
let target = [400, 400];
let a = 2.0;
let best_whale = population[0];
const MAX_ITER = 1000;

function draw() {
  background(0);
  //   ellipse(400, 400, 10, 10);

  //   frameRate(10);
  if (frame_count >= MAX_ITER) {
    noLoop();
    ellipse(10, 10, 20, 20);
  }

  a = 2.0 - frame_count * (2.0 / MAX_ITER);
  best_whale = find_best_whale(population);

  //   console.log(
  //     "Best Whale Position:",
  //     best_whale.position,
  //     "Fitness:",
  //     best_whale.fitness
  //   );

  //   ellipse(best_whale.position[0], best_whale.position[1], 6, 6);

  let random_a = random(0, 1);
  let random_b = random(0, 1);

  for (let j = 0; j < POP_SIZE; j++) {
    // random_move(population, population[j]);
    // spiral_move(best_whale, population[j]);
    // encircle_prey(population[j], best_whale, a);
    if (random_a < 0.5) {
      encircle_prey(population[j], best_whale, a);
      if (random_b < 0.5) {
      } else {
        spiral_move(best_whale, population[j]);
      }
    } else {
      random_move(population, population[j]);
    }
    ellipse(population[j].position[0], population[j].position[1], 4, 4);
  }
  frame_count++;
}
