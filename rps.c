#include "types.h"
#include "stat.h"
#include "user.h"

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

// Basic random number generator
static unsigned long seed = 12345;  // Initial seed value

unsigned int rand(void) {
  seed = (seed * 1103515245 + 12345) % (1 << 31);
  return (unsigned int)seed;
}

void print_choices() {
  printf(1, "Choices:\n");
  printf(1, "1. Rock\n");
  printf(1, "2. Paper\n");
  printf(1, "3. Scissors\n");
  printf(1, "Enter your choice (1, 2, or 3): ");
}

int get_choice() {
  char buf[10];
  int choice;
  memset(buf, 0, sizeof(buf));
  read(0, buf, sizeof(buf) - 1);
  choice = atoi(buf);
  return choice;
}

void play_rps() {
  int user_choice;
  int comp_choice;
  int result;

  // Print choices and get user's choice
  print_choices();
  user_choice = get_choice();

  // Check for invalid choice
  if (user_choice < ROCK || user_choice > SCISSORS) {
    printf(1, "Invalid choice!\n");
    exit();
  }

  // Generate computer's choice (1, 2, or 3)
  comp_choice = (rand() % 3) + 1;  // Random number between 1 and 3

  // Determine result
  if (user_choice == comp_choice) {
    result = 0;  // Tie
  } else if ((user_choice == ROCK && comp_choice == SCISSORS) ||
             (user_choice == PAPER && comp_choice == ROCK) ||
             (user_choice == SCISSORS && comp_choice == PAPER)) {
    result = 1;  // User wins
  } else {
    result = -1; // Computer wins
  }

  // Print results
  printf(1, "Computer chose: %d\n", comp_choice);
  if (result == 0) {
    printf(1, "It's a tie!\n");
  } else if (result == 1) {
    printf(1, "You win!\n");
  } else {
    printf(1, "You lose!\n");
  }
}

int main() {
  play_rps();
  exit();
}
