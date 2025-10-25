let population = [];
const POP_SIZE = 50;
const DIM = 2;
const LOWER_BOUND = 0.0;
const UPPER_BOUND = 800.0;
let frame_count = 0;
let target = [400, 400];
let a = 2.0;
let best_whale = population[0];
const MAX_ITER = 100;

function setup() {
  createCanvas(800, 800);
  initialize_population(population);
  //   console.log(population);
}

function mousePressed() {
  drawWhales(mouseX, mouseY);
}

function draw() {
  background(0);
  //   ellipse(400, 400, 10, 10);

  frameRate(200);
  if (frame_count >= MAX_ITER) {
    noLoop();
    // ellipse(10, 10, 20, 20);
  }

  a = 2.0 - frame_count * (2.0 / MAX_ITER);
  best_whale = find_best_whale(population);

  for (let j = 0; j < POP_SIZE; j++) {
    let random_a = random(0, 1);
    // random_move(population, population[j]);
    // spiral_move(best_whale, population[j]);
    // encircle_prey(population[j], best_whale, a);
    if (random_a < 0.7) {
      let random_b = random(0, 1);
      if (random_b < 0.8) {
        encircle_prey(population[j], best_whale, a);
      } else {
        spiral_move(best_whale, population[j]);
      }
    } else {
      random_move(population, population[j]);
    }
    population[j].history.push([...population[j].position]);
    coloring(population[j], best_whale.fitness);
    stroke(population[j].color);
    // ellipse(population[j].position[0], population[j].position[1], 3, 3);
    ellipse(best_whale.position[0], best_whale.position[1], 10, 10);
    for (let k = 0; k < population[j].history.length - 1; k++) {
      stroke(
        population[j].color[0],
        population[j].color[1],
        population[j].color[2],
        30
      );
      line(
        population[j].history[k][0],
        population[j].history[k][1],
        population[j].history[k + 1][0],
        population[j].history[k + 1][1]
      );
    }
  }
  frame_count++;
}
